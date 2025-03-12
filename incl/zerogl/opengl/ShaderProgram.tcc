/**
 * @author: Corentin Asso
 * @date: 2023-02-10
 * @brief: Template file for class 'zerogl.opengl.ShaderProgram'.
 */
 
namespace zgl
{
	inline const ShaderProgram& ShaderProgram::bind(const ShaderProgram& shaderProgram)
	{
		assert(shaderProgram.m_handle != 0);
		assert(shaderProgram.isInit());
		zglCheckOpenGL();
		m_handleBinded = shaderProgram.m_handle;
		glUseProgram(shaderProgram.m_handle);
		zglCheckOpenGL();
		return shaderProgram;
	}

	inline void ShaderProgram::unbind()
	{
		zglCheckOpenGL();
		m_handleBinded = 0;
		glUseProgram(0);
		zglCheckOpenGL();
	}

	inline void ShaderProgram::_showCompilationError(std::ostream& output) const
	{
		int success;
		char infoLog[512];
		for (size_t i = 0; i < MAX_SHADERS; ++i) {
			if (m_shaders[i] == 0) continue;
			glGetShaderiv(m_shaders[i], GL_COMPILE_STATUS, &success);
			zglCheckOpenGL();
			if (!success) {
				glGetShaderInfoLog(m_shaders[i], sizeof(infoLog), NULL, infoLog);
				zglCheckOpenGL();
				output << "ERROR::SHADER::" << OpenGL::toStringEnum(_mapIndexToEnum(i)) << "::" << "COMPILATION_FAILED" << "\n" << infoLog << std::endl;
			}
		}
	}

	inline void ShaderProgram::_showLinkageError(std::ostream& output) const
	{
		int success;
		char infoLog[512];
		output << "ERROR::LINKAGE_FAILED" << std::endl;
		glGetProgramiv(m_handle, GL_LINK_STATUS, &success);
		zglCheckOpenGL();
		if (!success) {
			glGetProgramInfoLog(m_handle, sizeof(infoLog), NULL, infoLog);
			zglCheckOpenGL();
			output << infoLog << std::endl;
		}
		zglCheckOpenGL();
	}

	template<typename T>
	void ShaderProgram::setUniformMatrix(const GLuint location, const T& uniform, GLboolean transpose)
	{
		assert(m_status == LINKED);
		zglCheckOpenGL();
		bind(*this);
		if constexpr (std::is_same<T, glm::mat2>::value)
			glUniformMatrix2fv(location, 1, transpose, glm::value_ptr(uniform));
		else if constexpr (std::is_same<T, glm::mat3>::value)
			glUniformMatrix3fv(location, 1, transpose, glm::value_ptr(uniform));
		else if constexpr (std::is_same<T, glm::mat4>::value)
			glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(uniform));
		else if constexpr (std::is_same<T, glm::vec3>::value)
			glUniform3fv(location, 1, glm::value_ptr(uniform));
		else
			static_assert("Uniform type not supported by template.");
		zglCheckOpenGL();
	}

} // End namespace zgl
