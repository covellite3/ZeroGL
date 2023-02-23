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
		static inline const char* toStringEnum(GLenum e);

		/**
		 * Print out error(s) in the OpenGL's error queue.
		 * Fail if there is errors.
		 * Use macro zglCheckOpenGL, it is recommended to only use zglCheckOpenGL.
		 */
		static inline void checkError (const char* file, const char* func, int line);
	}; // End class OpenGL

} // End namespace zgl

// Import template file.
#include "zerogl/opengl/OpenGL.tcc"

// Import other headers in package
#include "zerogl/opengl/ShaderProgram.hpp"
#include "zerogl/opengl/ArrayBuffer.hpp"
#include "zerogl/opengl/VertexArray.hpp"

#endif // H_ZGL_ZEROGL_OPENGL_OPENGL
