/**
 * @author: Corentin Asso
 * @date: 2023-02-10
 * @brief: C++ file for class 'zerogl.opengl.ShaderProgram'.
 */
 
// Import header file.
#include "zerogl/opengl/ShaderProgram.hpp"
#include <fstream>

namespace zgl
{
	GLuint ShaderProgram::m_handleBinded = 0;

	ShaderProgram::ShaderProgram ()
	: m_handle(0), m_status(DEFAULT)
	{
		for (size_t i = 0; i < MAX_SHADERS; ++i) m_shaders[i] = 0;
	}

	ShaderProgram::~ShaderProgram ()
	{
		zglCheckOpenGL();
		if (isBinded()) unbind();
		_freeShaders();
		zglCheckOpenGL();
		if (isInit()) glDeleteProgram(m_handle);
		zglCheckOpenGL();
	}

	void ShaderProgram::init ()
	{
		zglCheckOpenGL();
		m_handle = glCreateProgram();
		zglCheckOpenGL();
	}


	void ShaderProgram::_freeShaders ()
	{
		zglCheckOpenGL();
		for (size_t i = 0; i < MAX_SHADERS; ++i) {
			if (m_shaders[i] != 0) {
				glDetachShader(m_handle, m_shaders[i]);
				zglCheckOpenGL();
				glDeleteShader (m_shaders[i]);
				m_shaders[i] = 0;
			}
		}
	}


	bool ShaderProgram::compile ()
	{
		assert(m_status == DEFAULT);
		zglCheckOpenGL();
		int success;
		for (size_t i = 0; i < MAX_SHADERS; ++i) {
			auto handleShader = m_shaders[i];
			if (handleShader == 0) continue;
			glCompileShader(handleShader);
			zglCheckOpenGL();
			glGetShaderiv(handleShader, GL_COMPILE_STATUS, &success);
			zglCheckOpenGL();
			if (!success) {
				m_status = COMPILATION_FAILED;
				//_freeShaders ();
				return false;
			}
		}
		m_status = COMPILED;
		return true;
	}

	bool ShaderProgram::link ()
	{
		assert(m_status == COMPILED);
		assert(isInit());
		zglCheckOpenGL();
		int success;
		zglCheckOpenGL();
		glLinkProgram(m_handle);
		zglCheckOpenGL();
		m_status = LINKED;
		glGetProgramiv(m_handle, GL_LINK_STATUS, &success);
		zglCheckOpenGL();
		if (!success) {
			m_status = LINKAGE_FAILED;
			_freeShaders ();
			return false;
		}
		m_status = LINKED;
		// Now that we have made our program, we can free all shaders.
		_freeShaders();
		return true;
	}

	void ShaderProgram::showErrors (std::ostream& output)
	{
		assert(isInit());
		zglCheckOpenGL();
		switch (m_status) {
			case COMPILATION_FAILED: _showCompilationError(output); return;
			case LINKAGE_FAILED: _showLinkageError(output); return;
			default: output << "No errors found." << std::endl; return;
		}		
	}

	void ShaderProgram::_readFile(std::stringstream& ss, const std::string& filepath) {
		char buffer[256];
		std::ifstream ifs;
		ifs.open(filepath, std::ios::in);
		while (!ifs.eof()) {
			ifs.read(buffer, sizeof(buffer)-1);
			auto count =  ifs.gcount();
			buffer[count] = '\0';
			ss << buffer;
		}
		ifs.close();
	}


	void ShaderProgram::loadFromFile(const GLenum e, const std::string& filepath)
	{
		std::stringstream ss;
		_readFile(ss, filepath);
		attachShader(e, ss.str().c_str());
	}

	void ShaderProgram::attachShader (const GLenum e, const GLchar* p_src)
	{
		assert(isInit());
		zglCheckOpenGL();
		size_t indexHandleShader = _mapEnumToIndex(e);
		GLuint& shader = m_shaders[indexHandleShader];
		shader = glCreateShader(e);
		zglCheckOpenGL();
		assert(shader != 0);
		glShaderSource(shader, 1, &p_src, NULL);
		zglCheckOpenGL();
		glAttachShader(m_handle, shader);
		zglCheckOpenGL();
	}


	void ShaderProgram::bindAttribLocation (GLuint index, const GLchar* name)
	{
		zglCheckOpenGL();
		assert(isInit());
		assert(m_status == COMPILED);
		glBindAttribLocation(m_handle, index, name);
		zglCheckOpenGL();
	}


	GLuint ShaderProgram::getUniformLocation (const GLchar* name)
	{
		assert(isInit());
		assert(m_status == LINKED);
		zglCheckOpenGL();
		GLuint location = glGetUniformLocation(m_handle, name);
		zglCheckOpenGL();
		return location;
	}


	size_t ShaderProgram::_mapEnumToIndex (GLenum enumShader)
	{
		switch (enumShader) {
			case GL_VERTEX_SHADER: return 0;
			case GL_TESS_CONTROL_SHADER: return 1;
			case GL_TESS_EVALUATION_SHADER: return 2;
			case GL_GEOMETRY_SHADER: return 3;
			case GL_FRAGMENT_SHADER: return 4;
			case GL_COMPUTE_SHADER: return 5;
			default: throw std::invalid_argument("Unkown shader type. Fix your enums.");
		}
	}

	GLenum ShaderProgram::_mapIndexToEnum (size_t index)
	{
		switch (index) {
			case 0: return GL_VERTEX_SHADER;
			case 1: return GL_TESS_CONTROL_SHADER;
			case 2: return GL_TESS_EVALUATION_SHADER;
			case 3: return GL_GEOMETRY_SHADER;
			case 4: return GL_FRAGMENT_SHADER;
			case 5: return GL_COMPUTE_SHADER;
			default: throw std::invalid_argument("Out of map, no enum for such index.");
		}
	}

} // End namespace zgl
