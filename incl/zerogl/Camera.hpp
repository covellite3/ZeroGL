/**
 * @author: Corentin Asso
 * @date: 2025-02-24
 * @brief: Header for class 'zerogl.Camera'.
 */

#ifndef H_ZGL_ZEROGL_CAMERA
#define H_ZGL_ZEROGL_CAMERA

// Includes
#include "zerogl/Entity.hpp"
//#include "zerogl/Scene.hpp"
#include "zerogl/opengl/FrameBuffer.hpp"
// End includes

namespace zgl
{
	/**
	 * @author: Corentin Asso
	 * @date: 2025-02-24
	 * @brief: Camera in a scene.
	 */
	class Camera : public Entity
	{
	private:
		enum class ProjectionType { Perspective, Orthographic };
		ProjectionType m_projectionType;

		union ProjectionParams
		{
			struct PerspectiveParams
			{
				float fov;
				float aspect;
				float nearPlane;
				float farPlane;
			} perspective;

			struct OrthographicParams
			{
				float left;
				float right;
				float bottom;
				float top;
				float nearPlane;
				float farPlane;
			} orthographic;
		} m_projectionParams;

		std::shared_ptr<FrameBuffer> m_framebuffer;
		/**
		 * Frustrum
		 */
		//Frustrum frustrum;

	protected:
	public:
		inline Camera() : m_projectionType(ProjectionType::Perspective), m_framebuffer(nullptr) {
			m_projectionParams.perspective = { glm::radians(45.0f), 1.0f, 0.1f, 100.0f };
		}

		inline void setPerspective(float t_fov, float t_aspect, float t_nearPlane, float t_farPlane)
		{
			m_projectionType = ProjectionType::Perspective;
			m_projectionParams.perspective = { t_fov, t_aspect, t_nearPlane, t_farPlane };
		}

		inline void setOrthographic(float t_left, float t_right, float t_bottom, float t_top, float t_nearPlane, float t_farPlane)
		{
			m_projectionType = ProjectionType::Orthographic;
			m_projectionParams.orthographic = { t_left, t_right, t_bottom, t_top, t_nearPlane, t_farPlane };
		}

		inline auto getProjectionMatrix() const
		{
			if (m_projectionType == ProjectionType::Perspective)
			{
				const auto& p = m_projectionParams.perspective;
				return glm::perspective(p.fov, p.aspect, p.nearPlane, p.farPlane);
			}
			else
			{
				const auto& o = m_projectionParams.orthographic;
				return glm::ortho(o.left, o.right, o.bottom, o.top, o.nearPlane, o.farPlane);
			}
		}

		inline auto getViewMatrix() const {
			glm::mat4 rotationMatrix = glm::mat4_cast(glm::conjugate(this->getRotorOrientation()));
			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), -this->getPosition());
			return rotationMatrix * translationMatrix;
		}

		inline void setFramebuffer(std::shared_ptr<FrameBuffer> t_framebuffer)
		{
			m_framebuffer = t_framebuffer;
		}

		inline auto getFramebuffer() {
			return m_framebuffer;
		}
	
		inline auto getNearPlane() const {
			return m_projectionType == ProjectionType::Perspective ? m_projectionParams.perspective.nearPlane : m_projectionParams.orthographic.nearPlane;
		}

		inline auto getFarPlane() const {
			return m_projectionType == ProjectionType::Perspective ? m_projectionParams.perspective.farPlane : m_projectionParams.orthographic.farPlane;
		}
	}; // End class Camera

} // End namespace zgl


// Import template file.
#include "zerogl/Camera.tcc"

#endif // H_ZGL_ZEROGL_CAMERA
