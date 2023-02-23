/**
 * @author: Corentin Asso
 * @date: 2023-02-12
 * @brief: C++ file for class 'zerogl.opengl.VertexArray'.
 */
 
// Import header file.
#include "zerogl/opengl/VertexArray.hpp"

namespace zgl
{
		GLuint VertexArray::m_handleBinded = 0;

		const GLuint VertexArray::MAX_ATTRIBS = GL_MAX_VERTEX_ATTRIBS;

		VertexArray::VertexArray ()
		: m_handle(0)
		{}

		VertexArray::~VertexArray ()
		{
			zglCheckOpenGL();
			if (isBinded()) unbind();
			if (isInit()) glDeleteVertexArrays(1, &m_handle);
			zglCheckOpenGL();
		}
		
		void VertexArray::init ()
		{
			zglCheckOpenGL();
			glGenVertexArrays(1, &m_handle);
			zglCheckOpenGL();
		}

		void VertexArray::enableAttribPointer (const GLuint index)
		{
			assert(isInit());
			zglCheckOpenGL();
			bind(*this);
			glEnableVertexAttribArray(index);
			zglCheckOpenGL();
		}

		void VertexArray::disableAttribPointer (const GLuint index)
		{
			assert(isInit());
			zglCheckOpenGL();
			bind(*this);
			glDisableVertexAttribArray(index);
			zglCheckOpenGL();
		}

		void VertexArray::setAttribPointer (
				const GLuint index,
				const GLint size,
				const GLenum type,
				const GLboolean normalized,
				const GLsizei stride,
				const void* offset,
				const ArrayBuffer& vbo)
		{
			assert(index < GL_MAX_VERTEX_ATTRIBS);
			assert(index <= 4);
			assert(stride >= 0);
			assert(isInit());
			zglCheckOpenGL();
			ArrayBuffer::bind(vbo);
			glVertexAttribPointer(index, size, type, normalized, stride, offset);
			zglCheckOpenGL();
		}

		//void setElementArrayBuffer ();

		const VertexArray& VertexArray::bind (const VertexArray& vertexArray)
		{
			zglCheckOpenGL();
			m_handleBinded = vertexArray.m_handle;
			glBindVertexArray(vertexArray.m_handle);
			zglCheckOpenGL();
			return vertexArray;
		}

		void VertexArray::unbind ()
		{	
			zglCheckOpenGL();
			m_handleBinded = 0;
			glBindVertexArray(0);
			zglCheckOpenGL();
		}

} // End namespace zgl
