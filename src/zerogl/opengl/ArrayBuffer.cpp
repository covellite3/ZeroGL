/**
 * @author: Corentin Asso
 * @date: 2023-02-10
 * @brief: C++ file for class 'zerogl.opengl.ArrayBuffer'.
 */
 
// Import header file.
#include "zerogl/opengl/ArrayBuffer.hpp"

namespace zgl
{
	GLuint ArrayBuffer::m_handleBinded = 0;
	size_t ArrayBuffer::m_count = 0;

	ArrayBuffer::ArrayBuffer () : m_handle(0), m_size(0)
	{
		
	}

	ArrayBuffer::~ArrayBuffer()
	{
		zglCheckOpenGL();
		if (isInit()) {
			--m_count;
			if (isBinded()) unbind();
			glDeleteBuffers(1, &m_handle);
		}
		zglCheckOpenGL();
	}
} // End namespace zgl
