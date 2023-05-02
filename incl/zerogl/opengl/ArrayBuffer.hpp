/**
 * @author: Corentin Asso
 * @date: 2023-02-10
 * @brief: Header for class 'zerogl.opengl.ArrayBuffer'.
 */

#ifndef H_ZGL_ZEROGL_OPENGL_ARRAYBUFFER
#define H_ZGL_ZEROGL_OPENGL_ARRAYBUFFER

// Includes
#include <array>
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
		/** Number of possibles targets for buffer in OpenGL. */
		static constexpr size_t s_numberMaxOfTargets = 14;

		/** List of handle of binded gl objects for each target. */
		static std::array<GLuint, s_numberMaxOfTargets> s_handlesBinded;

		/** Keep track of the number of opengl handles created. */
		static size_t m_count;	// TODO thread protection.

		/** Handle of the gl object. */
		GLuint m_handle;

		/**
		 * Type of buffer.
		 * @param target <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferData.xhtml">list of enums</a>
		 */
		GLenum m_target;

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

		/** Say if enum if a valide target. */
		static inline bool isValidEnumTarget(GLenum target);

		/** Give index in list of handles binded of enum target. */
		static inline size_t mapTargetToIndexHandleBinded(GLenum target);

		/** Init opengl handle. */
		inline void init (GLenum target);

		/** Send data to buffer in GPU. */
		inline void send(GLsizeiptr size, const void* data, GLenum usage);

		/** Each VBO is unique. */
		ArrayBuffer& operator= (const ArrayBuffer& buffer) = delete;

		/** Give target of buffer. */
		inline size_t getTarget() const { return m_target; }

		/** Get size in byte of the buffer. */
		inline GLsizeiptr getSize() const { return m_size; }

		/** Say if opengl handle is created or not. */
		inline bool isInit () const { return m_handle != 0; }

		/** Say if VBO is binded. */
		inline bool isBinded () const { return s_handlesBinded[mapTargetToIndexHandleBinded(m_target)] == m_handle; }

		/** Bind buffer. */
		static inline const ArrayBuffer& bind (const ArrayBuffer& buffer);

		/** Give count of ArrayBuffer created. */
		static inline size_t getCount() { return m_count; }

		/** Unbind current buffer */
		static inline void unbind (GLenum target);

	}; // End class ArrayBuffer

} // End namespace zgl

// Import template file.
#include "zerogl/opengl/ArrayBuffer.tcc"

#endif // H_ZGL_ZEROGL_OPENGL_ARRAYBUFFER
