/**
 * @author: Corentin Asso
 * @date: 2023-02-10
 * @brief: Template file for class 'zerogl.opengl.ArrayBuffer'.
 */
 
namespace zgl
{
	inline void ArrayBuffer::init ()
	{
		zglCheckOpenGL();
		++m_count;
		glGenBuffers(1, &m_handle);
		zglCheckOpenGL();
	}

	inline void ArrayBuffer::send (GLsizeiptr size, const void* data, GLenum usage)
	{
		zglCheckOpenGL();
		assert(isInit());
		bind(*this);
		m_usage = usage;
		m_size = size;
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
		zglCheckOpenGL();
	}

	inline const ArrayBuffer& ArrayBuffer::bind (const ArrayBuffer& buffer)
	{
		zglCheckOpenGL();
		assert(buffer.isInit());
		m_handleBinded = buffer.m_handle;
		glBindBuffer(GL_ARRAY_BUFFER, buffer.m_handle);
		zglCheckOpenGL();
		return buffer;
	}

	inline void ArrayBuffer::unbind ()
	{
		zglCheckOpenGL();
		m_handleBinded = 0;
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		zglCheckOpenGL();
	}

} // End namespace zgl
