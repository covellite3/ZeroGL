/**
 * @author: Corentin Asso
 * @date: 2023-02-10
 * @brief: C++ file for class 'zerogl.opengl.ArrayBuffer'.
 */
 
// Import header file.
#include "zerogl/opengl/ArrayBuffer.hpp"

namespace zgl
{
	std::array<GLuint, ArrayBuffer::s_numberMaxOfTargets> ArrayBuffer::s_handlesBinded {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	size_t ArrayBuffer::m_count = 0;

	ArrayBuffer::ArrayBuffer () : m_handle(0), m_target(0), m_size(0)
	{
		// Empty
	}

	ArrayBuffer::~ArrayBuffer()
	{
		zglCheckOpenGL();
		if (isInit()) {
			if (isBinded()) unbind(m_target);
			glDeleteBuffers(1, &m_handle);
			--m_count;
		}
		zglCheckOpenGL();
	}
} // End namespace zgl
