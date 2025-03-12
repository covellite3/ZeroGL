/**
 * @author: Corentin Asso
 * @date: 2023-02-11
 * @brief: C++ file for class 'zerogl.opengl.FrameBuffer'.
 */
 
// Import header file.
#include "zerogl/opengl/FrameBuffer.hpp"

namespace zgl
{
	GLint FrameBuffer::s_defaultViewportX = 0;
	GLint FrameBuffer::s_defaultViewportY = 0;
	GLsizei FrameBuffer::s_defaultViewportWidth = 0;
	GLsizei FrameBuffer::s_defaultViewportHeight = 0;

	FrameBuffer::FrameBuffer()
		: m_fbo(0), m_texture(0), m_depthStencil(0), m_rbo(0)
	{
		std::cout << "[FrameBuffer<" << m_fbo << "> ! ] New empty framebuffer " << std::endl;
	}

	FrameBuffer::~FrameBuffer()
	{
		if(isInit())
		{
			std::cout << "[FrameBuffer<" << m_fbo << "> X ] Delete framebuffer " << m_fbo << std::endl;
			glDeleteFramebuffers(1, &m_fbo);
			zglCheckOpenGL();
			if(hasTexture())
			{
				std::cout << "[FrameBuffer<" << m_fbo << "> X ] Delete texture " << m_texture << std::endl;
				glDeleteTextures(1, &m_texture);
				zglCheckOpenGL();
			}
			if(hasDepthStencilBuffer())
			{
				std::cout << "[FrameBuffer<" << m_fbo << "> X ] Delete depth/stencil " << m_depthStencil << std::endl;
				glDeleteTextures(1, &m_depthStencil);
				zglCheckOpenGL();
			}
			assert(m_rbo == 0); // TODO delete rbo
			/*if(hasRenderBuffer())
			{
				glDelete(1, &m_rbo);
				zglCheckOpenGL();
			}*/
		} else {
			std::cout << "[FrameBuffer<" << m_fbo << "> X ] Delete uninitialized framebuffer " << m_fbo << std::endl;
			assert(!hasTexture());
			assert(!hasDepthStencilBuffer());
			//assert(!hasRenderBuffer));
		}
		this->m_fbo = 0;
		this->m_texture = 0;
		this->m_depthStencil = 0;
		this->m_rbo = 0;
	}

	void FrameBuffer::setWindowViewport(const GLint x, const GLint y, const GLsizei width, const GLsizei height)
	{
		GLint currentFBO;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentFBO);
		zglCheckOpenGL();
		if(currentFBO == 0)
			glViewport(x, y, width, height);
		s_defaultViewportX = x;
		s_defaultViewportY = y;
		s_defaultViewportWidth = width;
		s_defaultViewportHeight = height;

	}

	void FrameBuffer::init(GLint x, GLuint y, GLsizei width, GLsizei height)
	{
		assert(!isInit());
		this->m_viewportX = x;
		this->m_viewportY = y;
		this->m_viewportWidth = width;
		this->m_viewportHeight = height;
		glGenFramebuffers(1, &m_fbo);
		zglCheckOpenGL();

		std::cout << "[FrameBuffer<" << m_fbo << "> ! ] Initialization framebuffer with handle: " << m_fbo << std::endl;
	}

	void FrameBuffer::attachTexture()
	{
		std::cout << "[FrameBuffer<" << m_fbo << "> ! ] Starting process to attach texture " << std::endl;
		assert(isInit());
		assert(!hasTexture());
		bind();
		glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);	zglCheckOpenGL();
		  
		glTexImage2D(	GL_TEXTURE_2D, 0, GL_RGB, m_viewportWidth, m_viewportHeight, 0,
				GL_RGB, GL_UNSIGNED_BYTE, NULL);
		zglCheckOpenGL();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	zglCheckOpenGL();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	zglCheckOpenGL();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);	zglCheckOpenGL(); 
		assert(isComplete());
		unbind();

		std::cout << "[FrameBuffer<" << m_fbo << "> ! ] Attached texture " << m_texture << std::endl;
	}

	void FrameBuffer::attachDepthStencil()
	{
		std::cout << "[FrameBuffer<" << m_fbo << "> ! ] Starting process to attach depth/stencil " << std::endl;
		assert(isInit());
		assert(!hasDepthStencilBuffer());
		bind();
		glCreateTextures(GL_TEXTURE_2D, 1, &m_depthStencil);	zglCheckOpenGL();
		glBindTexture(GL_TEXTURE_2D, m_depthStencil);	zglCheckOpenGL();
		  
		zglCheckOpenGL();

		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_viewportWidth, m_viewportHeight);
		zglCheckOpenGL();

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthStencil, 0);  
		zglCheckOpenGL();
		assert(isComplete());
		unbind();


		std::cout << "[FrameBuffer<" << m_fbo << "> ! ] Attached depth stencil " << m_depthStencil << std::endl;
	}


	/*void FrameBuffer::attachRenderBuffer()
	{
		assert(isInit());
		assert(!hasRenderBuffer());
	}*/



} // End namespace zgl
