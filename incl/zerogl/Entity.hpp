/**
 * @author: Corentin Asso
 * @date: 2025-02-24
 * @brief: Header for class 'zerogl.Entity'.
 */

#ifndef H_ZGL_ZEROGL_ENTITY
#define H_ZGL_ZEROGL_ENTITY

// Includes
#include "zerogl/ZeroGL.hpp"
#include "zerogl/Math.hpp"
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

		/**
		 * Vectors who are oriented with the camera.
		 */
		//glm::vec3 m_rightVector, m_upVector, m_backVector;
		
	protected:
	public:
		/** Default constructor */
		Entity()
			: m_position(0.0f), m_scale(1.0f)
		{
			setRotorOrientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
		}

		/** Constructor with position, scale, and orientation */
		Entity(const glm::vec3& t_position, const glm::vec3& t_scale, const glm::quat& t_orientation)
			: m_position(t_position), m_scale(t_scale)
		{
			setRotorOrientation(t_orientation);
		}

		// TODO Why compilator refuse non-const references ?
		inline void attachComponent(const Component::Key& key, std::shared_ptr<Component> t_component) {
			if (m_attachments.find(key) != m_attachments.end()) {
				throw std::runtime_error("Component with this key already attached: " + std::to_string(static_cast<int>(key)));
			}
			m_attachments[key] = t_component;
		}

		inline bool hasAttachment(const Component::Key& key) const
		{
			return m_attachments.find(key) != m_attachments.end();
		}

		template<typename T>
		inline T& getAttachment(const Component::Key& key);

		inline auto getNumberOfAttachements() const
		{
			return m_attachments.size();
		}


		/**
		 * Get the right vector of the camera.
		 */
		inline auto getRightVector() const {
			return m_orientation * glm::vec3(1, 0, 0);
		}

		/**
		 * Get the up vector of the camera.
		 */
		inline auto getUpVector() const {
			return m_orientation * glm::vec3(0, 1, 0);
		}

		/**
		 * Get the back vector of the camera.
		 */
		inline auto getBackVector() const {
			return m_orientation * glm::vec3(0, 0, 1);
		}

		inline void lookAt(const glm::vec3& where, const glm::vec3& up)
		{
			glm::mat4 viewMatrix = glm::lookAt(m_position, where, up);
			// We use glm::transpose instead of glm::inverse
			// because it's equivalent for pure rotation matrices,
			// and much faster.
			m_orientation = glm::quat_cast(glm::transpose(viewMatrix));
		}

		/**
		 * Move camera foward in meters.
		 */
		inline void moveFoward(const float amount) {
			m_position = m_position - getBackVector() * amount;
		}

		/**
		 * Move camera backward in meters.
		 */
		inline void moveBackward(const float amount) {
			m_position = m_position + getBackVector() * amount;
		}

		/**
		 * Move camera leftward in meters.
		 */
		inline void moveLeftward(const float amount) {
			m_position = m_position - getRightVector() * amount;
		}

		/**
		 * Move camera rightward in meters.
		 */
		inline void moveRightward(const float amount) {
			m_position = m_position + getRightVector() * amount;
		}

		/**
		 * Move camera upward in meters.
		 */
		inline void moveUpward(const float amount) {
			m_position = m_position + getUpVector() * amount;
		}

		/**
		 * Move camera downward in meters.
		 */
		inline void moveDownward(const float amount) {
			m_position = m_position - getUpVector() * amount;
		}

		/**
		 * Rotate camera around an pivot vector.
		 * Update orientation, m_upVector, m_rightVector
		 * and m_backVector;
		 */
		inline void rotateRadianAroundPivot(const float rad, const glm::vec3& pivot) {
			glm::quat pivotRotation = getQuaternion(rad, pivot);

			m_orientation = pivotRotation * m_orientation;

		}

		inline void rotateDegreeAroundUpVector(const float degree) {
			rotateRadianAroundPivot(glm::radians(degree), getUpVector());
		}

		inline void rotateDegreeAroundRightVector(const float degree) {
			rotateRadianAroundPivot(glm::radians(degree), getRightVector());
		}

		inline void rotateDegreeAroundBackVector(const float degree) {
			rotateRadianAroundPivot(glm::radians(degree), getBackVector());
		}

		/** Entity direction, actually the front vector */
		inline auto getDirection() const { return -this->getBackVector(); }


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
			/*m_rightVector = m_orientation * glm::vec3(1, 0, 0);
			m_upVector = m_orientation * glm::vec3(0, 1, 0);
			m_backVector = m_orientation * glm::vec3(0, 0, 1);*/
		}

		inline auto getModelMatrix() const
		{
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
