/**
 * @author: Corentin Asso
 * @date: 2023-02-12
 * @brief: Header for class 'zerogl.opengl.VertexArray'.
 */

#ifndef H_ZGL_ZEROGL_OPENGL_VERTEXARRAY
#define H_ZGL_ZEROGL_OPENGL_VERTEXARRAY

// Includes
#include "zerogl/opengl/OpenGL.hpp"
// End includes

namespace zgl
{
	class ArrayBuffer;

	/**
	 * @author: Corentin Asso
	 * @date: 2023-02-12
	 * @brief: OpenGL's VAO wrapper.
	 */
	class VertexArray
	{
	private:
		/** TODO comment */
		static GLuint m_handleBinded;

		/** TODO comment */
		GLuint m_handle;
	protected:
	public:
		/** TODO comment */
		static const GLuint MAX_ATTRIBS;

		/** TODO comment */
		VertexArray ();

		/** TODO comment */
		~VertexArray ();
		
		/** TODO comment */
		void init ();

		/** TODO comment */
		void enableAttribPointer (const GLuint index);

		/** TODO comment */
		void disableAttribPointer (const GLuint index);

		/** TODO comment */
		void setAttribPointer (
				const GLuint index,
				const GLint size,
				const GLenum type,
				const GLboolean normalized,
				const GLsizei stride,
				const void* offset,
				const ArrayBuffer& vbo);

		/** TODO comment */
		//void setElementArrayBuffer ();

		/** TODO comment */
		inline bool isInit () { return m_handle != 0; }

		/** TODO comment */
		inline bool isBinded () { return m_handleBinded == m_handle; }

		/** TODO comment */
		static const VertexArray& bind (const VertexArray& vertexArray);

		/** TODO comment */
		static void unbind ();

	}; // End class VertexArray

} // End namespace zgl

// Import template file.
#include "zerogl/opengl/VertexArray.tcc"

#endif // H_ZGL_ZEROGL_OPENGL_VERTEXARRAY
