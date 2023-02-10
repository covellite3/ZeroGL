/**
 * @author: Corentin Asso
 * @date: 2023-02-10
 * @brief: Header for class 'zerogl.opengl.ArrayBuffer'.
 */

#ifndef H_ZGL_ZEROGL_OPENGL_ARRAYBUFFER
#define H_ZGL_ZEROGL_OPENGL_ARRAYBUFFER

// Includes
#include "zerogl/opengl/OpenGL.hpp"
// End includes

namespace zgl
{
	class OpenGL;

	/**
	 * @author: Corentin Asso
	 * @date: 2023-02-10
	 * @brief: OpenGL's array buffer wrapper.
	 */
	class ArrayBuffer
	{
	private:
		/** Handle of the binded gl object. */
		static GLuint m_handleBinded;

		/** Keep track of the number of opengl handles created. */
		static size_t m_count;	// TODO thread protection.

		/** Handle of the gl object. */
		GLuint m_handle;

		/** TODO comment. */
		GLenum m_usage;

		/** Size in byte of the buffer. */
		GLsizeiptr m_size;

	protected:
	public:
		/** Create an uninitialized VBO. */
		ArrayBuffer();

		/** Free allocated ressources. */
		~ArrayBuffer();

		/** Init opengl handle. */
		inline void init ();

		/** Send data to buffer in GPU. */
		inline void send(GLsizeiptr size, const void* data, GLenum usage);

		/** Each VBO is unique. */
		ArrayBuffer& operator= (const ArrayBuffer& buffer) = delete;

		/** Get size in byte of the buffer. */
		inline GLsizeiptr getSize() const { return m_size; }

		/** Say if opengl handle is created or not. */
		inline bool isInit () const { return m_handle != 0; }

		/** Say if VBO is binded. */
		inline bool isBinded () const { return m_handleBinded == m_handle; }

		/** Bind buffer. */
		static inline const ArrayBuffer& bind (const ArrayBuffer& buffer);

		/** Give count of ArrayBuffer created. */
		static inline size_t getCount() { return m_count; }

		/** Unbind current buffer */
		static inline void unbind ();

	}; // End class ArrayBuffer

} // End namespace zgl

// Import template file.
#include "zerogl/opengl/ArrayBuffer.tcc"

#endif // H_ZGL_ZEROGL_OPENGL_ARRAYBUFFER
