/**
 * @author: Corentin Asso
 * @date: 2025-03-19
 * @brief: Header for class 'zerogl.Bone'.
 */

#ifndef H_ZGL_ZEROGL_BONE
#define H_ZGL_ZEROGL_BONE

// Includes
#include "zerogl/opengl/OpenGL.hpp"
// End includes

namespace zgl
{
	/**
	 * @author: Corentin Asso
	 * @date: 2025-03-19
	 * @brief: Bone's transform for poses.
	 */
	class Bone
	{
	private:
		glm::vec3 m_position;
		glm::quat m_orientation;
	protected:
	public:
		inline Bone() : m_position(glm::vec3(0.0f)), m_orientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)) {}
		inline Bone(glm::vec3 t_position, glm::quat t_orientation) : m_position(t_position), m_orientation(t_orientation) {}

		inline auto getPosition() const { return m_position; }
		inline auto getOrientation() const { return m_orientation; }

		inline Bone operator*(const Bone& other) const
		{
			return Bone(this->m_position+other.m_position, this->m_orientation*other.m_orientation);
		}

		inline glm::mat4 getMatrix() const
		{
			//std::cout << "Bone::getMatrix " << glm::length(m_orientation) << std::endl;
			assert(glm::abs(glm::length(m_orientation) - 1.0f) < 0.0001f); // Check if quaternion is normalized
			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_position);
			glm::mat4 rotationMatrix = glm::mat4_cast(m_orientation);
			return translationMatrix * rotationMatrix;
		}
	}; // End class Bone

} // End namespace zgl

// Import template file.
#include "zerogl/Bone.tcc"

#endif // H_ZGL_ZEROGL_BONE
