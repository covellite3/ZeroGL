/**
 * @author: Corentin Asso
 * @date: 2025-03-19
 * @brief: Header for class 'zerogl.Pose'.
 */

#ifndef H_ZGL_ZEROGL_POSE
#define H_ZGL_ZEROGL_POSE

// Includes
#include "zerogl/Bone.hpp"
#include <vector>
// End includes

namespace zgl
{
	/**
	 * @author: Corentin Asso
	 * @date: 2025-03-19
	 * @brief: Pose for animation.
	 */
	class Pose
	{
	public:
		enum class TransformationSpace { LOCAL, HIERARCHICAL };
	private:
		TransformationSpace m_eTransformationSpace;

		std::vector<Bone> m_bones;
	protected:
	public:
		inline Pose() : m_eTransformationSpace(TransformationSpace::LOCAL) {}
		inline Pose(TransformationSpace t_eTransformationSpace) : m_eTransformationSpace(t_eTransformationSpace) {}
 		inline Pose(TransformationSpace t_eTransformationSpace, std::initializer_list<Bone> t_bones)
			: m_eTransformationSpace(t_eTransformationSpace), m_bones(t_bones) {}

		inline Pose(const Pose& other)
			: m_eTransformationSpace(other.m_eTransformationSpace), m_bones(other.m_bones) {}


		inline Pose& operator=(const Pose& other)
		{
			if (this != &other) {
				m_eTransformationSpace = other.m_eTransformationSpace;
				m_bones = other.m_bones;
			}
			return *this;
		}

		inline Bone& operator[](const size_t index) { return m_bones[index]; }

		inline auto getNbrOfBones() const { return m_bones.size(); }

		inline auto getTransformationSpace() const { return m_eTransformationSpace; }

		inline void setTransformationSpace(const TransformationSpace t_eTransformationSpace) { m_eTransformationSpace = t_eTransformationSpace; }

		inline Pose interpolate(const Pose& other, const float k) const
		{
			assert(this->m_eTransformationSpace == TransformationSpace::LOCAL);
			assert(other.m_eTransformationSpace == TransformationSpace::LOCAL);
			assert(this->m_bones.size() == other.m_bones.size());

			auto newPose = Pose();
			newPose.m_bones.resize(this->m_bones.size());
			for (size_t i = 0; i < m_bones.size(); ++i) {
				// Interpolate position and rotation for each bone
				glm::vec3 interpolatedPosition = glm::mix(this->m_bones[i].getPosition(), other.m_bones[i].getPosition(), k);
				glm::quat interpolatedRotation = glm::normalize(glm::slerp(this->m_bones[i].getOrientation(), other.m_bones[i].getOrientation(), k));

				// Set the interpolated values back to the Pose
				newPose.m_bones[i] = Bone(interpolatedPosition, interpolatedRotation);
			}
			return newPose;
		}
	}; // End class Pose

} // End namespace zgl

// Import template file.
#include "zerogl/Pose.tcc"

#endif // H_ZGL_ZEROGL_POSE
