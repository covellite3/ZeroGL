/**
 * @author: Corentin Asso
 * @date: 2023-02-11
 * @brief: Header for class 'zerogl.opengl.FrameBuffer'.
 */

#ifndef H_ZGL_ZEROGL_OPENGL_FRAMEBUFFER
#define H_ZGL_ZEROGL_OPENGL_FRAMEBUFFER

// Includes
#include "zerogl/opengl/OpenGL.hpp"
// End includes

namespace zgl
{
	/**
	 * @author: Corentin Asso
	 * @date: 2023-02-11
	 * @brief: OpengGL's frame buffer wrapper.
	 */
	class FrameBuffer
	{
	private:
		/** OpenGL's handles */
		GLuint m_fbo, m_texture, m_depthStencil, m_rbo;

		/** FrameBuffer viewport parameters*/
		GLint m_viewportX, m_viewportY;
		GLsizei m_viewportWidth, m_viewportHeight;

		/** FrameBuffer default (0) viewport parameters*/
		static GLint s_defaultViewportX, s_defaultViewportY;
		static GLsizei s_defaultViewportWidth, s_defaultViewportHeight;
	protected:
	public:
		/** Constructor */
		FrameBuffer();

		/** Destructor */
		~FrameBuffer();

		/** Prevent copying */
		FrameBuffer(const FrameBuffer&) = delete;
		FrameBuffer& operator=(const FrameBuffer&) = delete;

		/** Allow moving */
		FrameBuffer(FrameBuffer&& other) noexcept;
		FrameBuffer& operator=(FrameBuffer&& other) noexcept;

		/**
		 * Set default window's framebufer (0) viewport parameters
		 * to be used when unbinding any framebuffer.
		 * It will also imediatly call glViewport if the current bound
		 * fbo is the default (0).
		 */ 
		static void setWindowViewport(const GLint x, const GLint y, const GLsizei width, const GLsizei height);

		/** Init framebuffer */
		void init(GLint x, GLuint y, GLsizei width, GLsizei height);

		inline static GLuint getBound()
		{
			GLint currentFBO;
			glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentFBO);
			zglCheckOpenGL();
			return (GLuint)currentFBO;
		}

		/** Bind the framebuffer */
		inline void bind() const
		{
			//std::cout << "[FrameBuffer<" << m_fbo << "> : ] Binding the framebuffer " << m_fbo << std::endl;
			assert(isInit());
			glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
			glViewport(m_viewportX, m_viewportY, m_viewportWidth, m_viewportHeight);
			zglCheckOpenGL();
		};

		/** Unbind the framebuffer */
		inline static void unbind()
		{
			/*GLint currentFBO;
			glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentFBO);
			zglCheckOpenGL();*/
			//std::cout << "[FrameBuffer<*> : ] Unbinding the framebuffer " << currentFBO << std::endl;
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(s_defaultViewportX, s_defaultViewportY, s_defaultViewportWidth, s_defaultViewportHeight);
			zglCheckOpenGL();
		};

		/** Check FrameBuffer status */
		inline bool isComplete()
		{
			assert(isInit());
			bind();
			bool complete = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
			zglCheckOpenGL();
			std::cout << "[FrameBuffer<" << m_fbo << "> ? ] Check if FBO is complete: " << (complete ? "yes":"no") << std::endl;
			return complete;
		}

		inline bool hasTexture() const { return m_texture != 0; }
		inline bool hasDepthStencilBuffer() const { return m_depthStencil != 0; }
		//inline bool hasRenderBuffer() const { return m_rbo != 0; }

		/** Attach a texture to the framebuffer */
		void attachTexture();

		/** Attach a depth/stencil buffer to the framebuffer */
		void attachDepthStencil();

		/** Attach a renderbuffer to the framebuffer */
		//void attachRenderBuffer();

		/** Check if framebuffer is initialized */
		inline bool isInit() const { return m_fbo != 0; }

		/** Get the framebuffer handle */
		inline auto getFBOHandle() const { return m_fbo; }

		/** Get the texture handle */
		inline auto getTextureHandle() const { return m_texture; }

		/** Get the depth/stencil handle */
		inline auto getDepthStencilHandle() const { return m_depthStencil; }

		/** Get the renderbuffer handle */
		//inline auto getRBOHandle() const { return m_rbo; };
	}; // End class FrameBuffer

} // End namespace zgl

// Import template file.
#include "zerogl/opengl/FrameBuffer.tcc"

#endif // H_ZGL_ZEROGL_OPENGL_FRAMEBUFFER
