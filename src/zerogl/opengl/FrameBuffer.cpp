/**
 * @author: Corentin Asso
 * @date: 2023-02-11
 * @brief: C++ file for class 'zerogl.opengl.FrameBuffer'.
 */
 
// Import header file.
#include "zerogl/opengl/FrameBuffer.hpp"

namespace zgl
{
	FrameBuffer::FrameBuffer()
		: m_fbo(0), m_texture(0), m_depthStencil(0), m_rbo(0)
	{
	}

	FrameBuffer::~FrameBuffer()
	{
		if(isInit())
		{
			glDeleteFramebuffers(1, &m_fbo);
			zglCheckOpenGL();
			if(hasTexture())
			{
				glDeleteTextures(1, &m_texture);
				zglCheckOpenGL();
			}
			if(hasDepthStencilBuffer())
			{
				glDeleteTextures(1, &m_depthStencil);
				zglCheckOpenGL();
			}
			assert(m_rbo == 0); // TODO delete rbo
			/*if(hasRenderBuffer())
			{
				glDelete(1, &m_rbo);
				zglCheckOpenGL();
			}*/
		}
		this->m_fbo = 0;
		this->m_texture = 0;
		this->m_depthStencil = 0;
		this->m_rbo = 0;
	}

	void FrameBuffer::init(GLsizei t_width, GLsizei t_height)
	{
		assert(!isInit());
		this->m_width = t_width;
		this->m_height = t_height;
		glGenFramebuffers(1, &m_fbo);
		zglCheckOpenGL();
		bind();
	}

	void FrameBuffer::attachTexture()
	{
		assert(isInit());
		assert(!hasTexture());
		bind();
		glGenTextures(1, &m_texture);	zglCheckOpenGL();
		glBindTexture(GL_TEXTURE_2D, m_texture);	zglCheckOpenGL();
		  
		glTexImage2D(	GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0,
				GL_RGB, GL_UNSIGNED_BYTE, NULL);
		zglCheckOpenGL();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	zglCheckOpenGL();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	zglCheckOpenGL();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);	zglCheckOpenGL(); 
	}

	void FrameBuffer::attachDepthStencil()
	{
		assert(isInit());
		assert(!hasDepthStencilBuffer());
		bind();
		glGenTextures(1, &m_depthStencil);	zglCheckOpenGL();
		glBindTexture(GL_TEXTURE_2D, m_depthStencil);	zglCheckOpenGL();
		  
		glTexImage2D(	GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_width, m_height, 0, 
				GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
		zglCheckOpenGL();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	zglCheckOpenGL();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	zglCheckOpenGL();

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthStencil, 0);  
		zglCheckOpenGL();
	}


	/*void FrameBuffer::attachRenderBuffer()
	{
		assert(isInit());
		assert(!hasRenderBuffer());
	}*/



} // End namespace zgl
