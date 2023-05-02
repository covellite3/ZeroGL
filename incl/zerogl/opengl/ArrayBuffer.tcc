/**
 * @author: Corentin Asso
 * @date: 2023-02-10
 * @brief: Template file for class 'zerogl.opengl.ArrayBuffer'.
 */
 
namespace zgl
{
	inline void ArrayBuffer::init (GLenum target)
	{
		assert(isValidEnumTarget(target));
		m_target = target;
		zglCheckOpenGL();
		++m_count;
		glGenBuffers(1, &m_handle);
		zglCheckOpenGL();
	}

	inline bool ArrayBuffer::isValidEnumTarget(GLenum target)
	{
		switch(target) {
			case GL_ARRAY_BUFFER:
			case GL_ATOMIC_COUNTER_BUFFER: 
			case GL_COPY_READ_BUFFER: 
			case GL_COPY_WRITE_BUFFER: 
			case GL_DISPATCH_INDIRECT_BUFFER: 
			case GL_DRAW_INDIRECT_BUFFER: 
			case GL_ELEMENT_ARRAY_BUFFER: 
			case GL_PIXEL_PACK_BUFFER: 
			case GL_PIXEL_UNPACK_BUFFER: 
			case GL_QUERY_BUFFER: 
			case GL_SHADER_STORAGE_BUFFER: 
			case GL_TEXTURE_BUFFER: 
			case GL_TRANSFORM_FEEDBACK_BUFFER: 
			case GL_UNIFORM_BUFFER:
				return true;
			default:
				return false;
		}
	}

	inline size_t ArrayBuffer::mapTargetToIndexHandleBinded(GLenum target)
	{
		switch(target) {
			case GL_ARRAY_BUFFER:
				return 0;
			case GL_ATOMIC_COUNTER_BUFFER: 
				return 1;
			case GL_COPY_READ_BUFFER: 
				return 2;
			case GL_COPY_WRITE_BUFFER: 
				return 3;
			case GL_DISPATCH_INDIRECT_BUFFER: 
				return 4;
			case GL_DRAW_INDIRECT_BUFFER: 
				return 5;
			case GL_ELEMENT_ARRAY_BUFFER: 
				return 6;
			case GL_PIXEL_PACK_BUFFER: 
				return 7;
			case GL_PIXEL_UNPACK_BUFFER: 
				return 8;
			case GL_QUERY_BUFFER: 
				return 9;
			case GL_SHADER_STORAGE_BUFFER: 
				return 10;
			case GL_TEXTURE_BUFFER: 
				return 11;
			case GL_TRANSFORM_FEEDBACK_BUFFER: 
				return 12;
			case GL_UNIFORM_BUFFER:
				return 13;
			default:
				assert(false);
				return 0;
		}
	}

	inline void ArrayBuffer::send (GLsizeiptr size, const void* data, GLenum usage)
	{
		zglCheckOpenGL();
		assert(isInit());
		bind(*this);
		m_usage = usage;
		m_size = size;
		glBufferData(m_target, size, data, usage);
		zglCheckOpenGL();
	}

	inline const ArrayBuffer& ArrayBuffer::bind (const ArrayBuffer& buffer)
	{
		zglCheckOpenGL();
		assert(buffer.isInit());
		size_t index = mapTargetToIndexHandleBinded(buffer.m_target);
		s_handlesBinded[index] = buffer.m_handle;
		glBindBuffer(buffer.m_target, buffer.m_handle);
		zglCheckOpenGL();
		return buffer;
	}

	inline void ArrayBuffer::unbind (GLenum target)
	{
		zglCheckOpenGL();
		size_t index = mapTargetToIndexHandleBinded(target);
		s_handlesBinded[index] = 0;
		glBindBuffer(target, 0);
		zglCheckOpenGL();
	}

} // End namespace zgl
