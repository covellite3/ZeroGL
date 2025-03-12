/**
 * @author: Corentin Asso
 * @date: 2023-02-10
 * @brief: Header for class 'zerogl.opengl.ShaderProgram'.
 */

#ifndef H_ZGL_ZEROGL_OPENGL_SHADERPROGRAM
#define H_ZGL_ZEROGL_OPENGL_SHADERPROGRAM

// Includes
#include "zerogl/ZeroGL.hpp"
//#include <SFML/Graphics/Texture.hpp>
#include "zerogl/opengl/Texture.hpp"
#include <string>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <algorithm>
// End includes

namespace zgl
{
	class VertexArray;

	/**
	 * @author: Corentin Asso
	 * @date: 2023-02-10
	 * @brief: OpengGL's shader program wrapper.
	 * TODO Hot reloading.
	 * TODO Preprocessor include.
	 */
	class ShaderProgram
	{
	public:
		/** TODO comment */
		enum Status { DEFAULT, COMPILED, LINKED, COMPILATION_FAILED, LINKAGE_FAILED };

	private:
		/** TODO comment */
		static const size_t MAX_SHADERS = 6;

		/** TODO comment */
		static GLuint m_handleBinded;

		/** TODO comment */
		GLuint m_shaders[MAX_SHADERS];

		/** Shader program opengl's handle. */
		GLuint m_handle;

		/** TODO comment */
		enum Status m_status;

		/** Read text file into a stringstream. */
		void _readFile(std::stringstream& ss, const std::string& filepath);
		/** TODO comment */
		static size_t _mapEnumToIndex (GLenum enumShader);

		/** TODO comment */
		static GLenum _mapIndexToEnum (size_t index);

		/** TODO comment */
		inline void _showCompilationError(std::ostream& output) const;

		/** TODO comment */
		inline void _showLinkageError(std::ostream& output) const;

		/** TODO comment */
		void _freeShaders ();

	protected:

	public:
		/** TODO comment */
		ShaderProgram();

		/** TODO comment */
		~ShaderProgram();

		/** TODO comment */
		void init();
	
		/** TODO comment */
		bool compile();

		/** TODO comment */
		bool link();

		/** TODO comment */
		void showErrors(std::ostream& output);

		/** TODO comment */
		void loadFromFile(const GLenum e, const std::string& filepath);

		/** Attach a shader of given GLenum to the program. */
		void attachShader(const GLenum e, const GLchar* p_src);

		/** TODO comment */
		inline void attachComputeShader(const GLchar* p_src) { attachShader(GL_COMPUTE_SHADER, p_src); }

		/** TODO comment */
		inline void attachVertexShader(const GLchar* p_src) { attachShader(GL_VERTEX_SHADER, p_src); }

		/** TODO comment */
		inline void attachTessControleShader(const GLchar* p_src) { attachShader(GL_TESS_CONTROL_SHADER, p_src); }

		/** TODO comment */
		inline void attachTessEvaluationShader(const GLchar* p_src) { attachShader(GL_TESS_EVALUATION_SHADER, p_src); }

		/** TODO comment */
		inline void attachGeometryShade(const GLchar* p_src) { attachShader(GL_GEOMETRY_SHADER, p_src); }

		/** TODO comment */
		inline void attachFragmentShader(const GLchar* p_src) { attachShader(GL_FRAGMENT_SHADER, p_src); }

		/**
		 * Before linking.
		 * TODO comment
		 */
		void bindAttribLocation(GLuint index, const GLchar* name);

		/**
		 * Before linking.
		 * TODO comment
		 */
		template<typename... Args>
		void setOutputFragment(Args... args);

		/**
		 * Before linking.
		 * TODO comment
		 */
		//void setTransformFeedbackOutputCapturing();

		/**
		 * Before linking.
		 * TODO comment
		 */
		//void programSeparation();

		/** TODO comment */
		GLuint getUniformLocation(const GLchar* name);

		/** TODO comment */
		template<typename T>
		void setUniformMatrix(const GLuint location, const T& uniform, GLboolean transpose=GL_FALSE);

		/** TODO comment */
		void setUniformTexture(const GLuint location, const GLuint handle, size_t unit);

		/** TODO comment */
		//template<typename T>
		//GLuint setUniform (GLuint location, GLsizei count, const T* uniform, GLboolean transpose=GL_FALSE);

		/** Attach a library GLSL to the program. */
		//void attachLibrary (const LibraryGLSL& lib);
		
		/** TODO comment */
		inline bool isInit() const { return m_handle != 0; };

		/** TODO comment */
		inline bool isBinded() const { return m_handleBinded == m_handle; };

		/** TODO comment */
		inline bool getHandle() { return m_handle; };

		/** TODO comment */
		static inline const ShaderProgram& bind(const ShaderProgram& shaderProgram);

		/** TODO comment */
		static inline void unbind();

	}; // End class ShaderProgram

} // End namespace zgl

// Import template file.
#include "zerogl/opengl/ShaderProgram.tcc"

#endif // H_ZGL_ZEROGL_OPENGL_SHADERPROGRAM
