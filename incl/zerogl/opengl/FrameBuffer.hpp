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

		/** FrameBuffer size */
		GLsizei m_width, m_height;
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

		/** Init framebuffer */
		void init(GLsizei t_width, GLsizei t_height);

		/** Bind the framebuffer */
		inline void bind() const
		{
			assert(isInit());
			glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
			zglCheckOpenGL();
		};

		/** Unbind the framebuffer */
		inline static void unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			zglCheckOpenGL();
		};

		/** Check FrameBuffer status */
		inline bool isComplete()
		{
			bind();
			bool complete = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
			zglCheckOpenGL();
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
		inline bool isInit() const { return m_fbo != 0; };

		/** Get the framebuffer handle */
		inline auto getFBOHandle() const { return m_fbo; };

		/** Get the texture handle */
		inline auto getTextureHandle() const { return m_fbo; };

		/** Get the depth/stencil handle */
		inline auto getDepthStencilHandle() const { return m_depthStencil; };

		/** Get the renderbuffer handle */
		//inline auto getRBOHandle() const { return m_rbo; };
	}; // End class FrameBuffer

} // End namespace zgl

// Import template file.
#include "zerogl/opengl/FrameBuffer.tcc"

#endif // H_ZGL_ZEROGL_OPENGL_FRAMEBUFFER
