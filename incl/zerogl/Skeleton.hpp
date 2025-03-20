/**
 * @author: Corentin Asso
 * @date: 2025-02-24
 * @brief: Header for class 'zerogl.Skeleton'.
 */

#ifndef H_ZGL_ZEROGL_SKELETON
#define H_ZGL_ZEROGL_SKELETON

// Includes
#include "zerogl/Component.hpp"
#include "zerogl/Pose.hpp"
#include <cstdint>
#include <vector>
// End includes

namespace zgl
{
	/**
	 * @author: Corentin Asso
	 * @date: 2025-02-24
	 * @brief: Skeleton for animation.
	 */
	class Skeleton : public Component
	{
	private:
		struct Node {
			uint8_t m_poseIdx;
			Node *m_left, *m_right;
			inline Node(uint8_t t_poseIdx) : m_poseIdx(t_poseIdx), m_left(nullptr), m_right(nullptr) {};

			inline auto addLeft(const uint8_t t_poseIdx) { return m_left = new Node(t_poseIdx); }
			inline auto addRight(const uint8_t t_poseIdx) { return m_right = new Node(t_poseIdx); }

			inline std::string toString() const
			{
				return std::string("[")+std::to_string(m_poseIdx)+"]{"+(m_left == nullptr ? "." : m_left->toString())+"|"+(m_right == nullptr ? "." : m_right->toString())+"}";
			}

			void hierarchize(Pose& pose) const;
		};

		Node* m_root;
	protected:
	public:
		inline Skeleton() : m_root(nullptr) {}

		inline void hierarchize(Pose& pose) const
		{
			assert(pose.getTransformationSpace() == Pose::TransformationSpace::LOCAL);
			assert(m_root->m_poseIdx == 0);
			m_root->hierarchize(pose);
			pose.setTransformationSpace(Pose::TransformationSpace::HIERARCHICAL);
		}

		inline auto addRoot(const uint8_t t_poseIdx) { assert(m_root == nullptr); return m_root = new Node(t_poseIdx); }

		inline auto getRoot() const { return m_root; };


		// TODO to hierachical pose

	}; // End class Skeleton

} // End namespace zgl

// Import template file.
#include "zerogl/Skeleton.tcc"

#endif // H_ZGL_ZEROGL_SKELETON
