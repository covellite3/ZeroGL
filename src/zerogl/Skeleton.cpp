/**
 * @author: Corentin Asso
 * @date: 2025-02-24
 * @brief: C++ file for class 'zerogl.Skeleton'.
 */
 
// Import header file.
#include "zerogl/Skeleton.hpp"

namespace zgl
{
	void Skeleton::Node::hierarchize(Pose& pose) const
	{
		std::cout << "Skeleton::Node::hierarchize " << ((int)m_poseIdx) << std::endl;
		if(m_left != nullptr) {
			std::cout << "Skeleton::Node::left " << m_left << std::endl;
			pose[m_left->m_poseIdx] = pose[m_poseIdx]*pose[m_left->m_poseIdx];
			m_left->hierarchize(pose);
		}
		if(m_right != nullptr) {
			std::cout << "Skeleton::Node::right " << m_right << std::endl;
			pose[m_right->m_poseIdx] = pose[m_poseIdx]*pose[m_right->m_poseIdx];
			m_right->hierarchize(pose);
		}
	}
} // End namespace zgl
