/**
 * @author: Corentin Asso
 * @date: 2025-02-24
 * @brief: Header for class 'zerogl.Entity'.
 */

#ifndef H_ZGL_ZEROGL_ENTITY
#define H_ZGL_ZEROGL_ENTITY

// Includes
#include "zerogl/ZeroGL.hpp"
#include "zerogl/Component.hpp"
#include "zerogl/Model.hpp"
#include <unordered_map>
// End includes

namespace zgl
{
	/**
	 * @author: Corentin Asso
	 * @date: 2025-02-24
	 * @brief: Entity in a scene.
	 */
	class Entity : public Component
	{
	private:
		/** Attached component to this entity (can be another entity) */
		std::unordered_map<Component::Key, std::shared_ptr<Component>> m_attachments;
		// SQT
		glm::vec3 m_position;
		glm::vec3 m_scale;
		glm::quat m_orientation;
		//TODO BoundingBox<DIMENSION> m_boundingbox;
	protected:
	public:
		/** Default constructor */
		Entity()
			: m_position(0.0f), m_scale(1.0f), m_orientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)) {}

		/** Constructor with position, scale, and orientation */
		Entity(const glm::vec3& t_position, const glm::vec3& t_scale, const glm::quat& t_orientation)
			: m_position(t_position), m_scale(t_scale), m_orientation(t_orientation) {}

		/** Constructor with position only, scale default to 1 and orientation to identity */
		Entity(const glm::vec3& t_position)
			: m_position(t_position), m_scale(1.0f), m_orientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)) {}

		/** Constructor with position and scale only, orientation default to identity */
		Entity(const glm::vec3& t_position, const glm::vec3& t_scale)
			: m_position(t_position), m_scale(t_scale), m_orientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)) {}

		// TODO Why compilator refuse non-const references ?
		inline void attachComponent(const Component::Key& key, std::shared_ptr<Component> t_component) {
			if (m_attachments.find(key) != m_attachments.end()) {
				throw std::runtime_error("Component with this key already attached: " + std::to_string(static_cast<int>(key)));
			}
			m_attachments[key] = t_component;
		}

		template<typename T>
		inline T& getAttachment(const Component::Key& key);

		inline auto getNumberOfAttachements() const
		{
			return m_attachments.size();
		}


		inline auto getPosition() const
		{
			return m_position;
		}

		inline auto getScale() const
		{
			return m_scale;
		}

		inline auto getRotorOrientation() const
		{
			return m_orientation;
		}

		inline void setPosition(const auto &t_position)
		{
			m_position = t_position;
		}

		inline void setScale(const auto &t_scale)
		{
			m_scale = t_scale;
		}

		inline void setRotorOrientation(const auto &t_orientation)
		{
			m_orientation = t_orientation;
		}

		inline auto getModelMatrix() const
		{
			//assert(glm::abs(glm::length(m_orientation) - 1.0f) < 0.0001f);
			glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), m_scale);
			glm::mat4 rotateMat = glm::mat4_cast(m_orientation);
			glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), m_position);
			return translateMat * rotateMat * scaleMat;
		}

	}; // End class Entity

} // End namespace zgl

// Import template file.
#include "zerogl/Entity.tcc"

#endif // H_ZGL_ZEROGL_ENTITY
