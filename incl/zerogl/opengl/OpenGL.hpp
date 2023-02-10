/**
 * @author: Corentin Asso
 * @date: 2023-02-10
 * @brief: Header for class 'zerogl.opengl.OpenGL'.
 */

#ifndef H_ZGL_ZEROGL_OPENGL_OPENGL
#define H_ZGL_ZEROGL_OPENGL_OPENGL
// Includes
#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// End includes

/*
 * TODO comment
 */
#ifndef NDEBUG
	/** TODO comment */
	#define zglCheckOpenGL() zgl::OpenGL::checkError(__FILE__, __func__, __LINE__);
#else
	/** TODO comment */
	#define zglCheckOpenGL() {}
#endif



namespace zgl
{
	/**
	 * @author: Corentin Asso
	 * @date: 2023-02-10
	 * @brief: Package zerogl.OpenGL main header.
	 */
	class OpenGL
	{
	private:
	protected:
	public:
		/** Turn an GLenum into a string of the same name. */
		static const char* toStringEnum(GLenum e)
		{
			switch(e) {
				case GL_COMPUTE_SHADER: return "GL_COMPUTE_SHADER";
				case GL_VERTEX_SHADER: return "GL_VERTEX_SHADER";
				case GL_TESS_EVALUATION_SHADER: return "GL_TESS_EVALUATION_SHADER";
				case GL_GEOMETRY_SHADER: return "GL_GEOMETRY_SHADER";
				case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
				case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
				case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
				case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW";
				case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW";
				case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
				case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
				case GL_CONTEXT_LOST: return "GL_CONTEXT_LOST";
				case GL_TABLE_TOO_LARGE: return "GL_TABLE_TOO_LARGE";
				case GL_NO_ERROR: return "GL_NO_ERROR";
				default: return "UNKNOW_ENUM";
			}
		}

		/**
		 * Print out error(s) in the OpenGL's error queue.
		 * Fail if there is errors.
		 * Use macro zglCheckOpenGL, it is recommended to only use zglCheckOpenGL.
		 */
		static inline void checkError (const char* file, const char* func, int line) {
			GLenum err;
			while ((err = glGetError()) != GL_NO_ERROR) {
				std::cerr
					<< "\x1B[36m"
					<< "AT::"
					<< file
					<< "::"
					<< func
					<< "::"
					<< line
					<< "::\x1B[31m"
					<< "ERROR::"
					<< toStringEnum(err)
					<< "\033[0m"
					<< std::endl;
			}
			if (err == GL_NO_ERROR) return;
			exit(EXIT_FAILURE);
		}
	}; // End class OpenGL

} // End namespace zgl

// Import template file.
#include "zerogl/opengl/OpenGL.tcc"

// Import other headers in package
#include "zerogl/opengl/ShaderProgram.hpp"
#include "zerogl/opengl/ArrayBuffer.hpp"
#include "zerogl/opengl/VertexArray.hpp"

#endif // H_ZGL_ZEROGL_OPENGL_OPENGL
