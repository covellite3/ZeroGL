/**
 * @author: Corentin Asso
 * @date: 2025-02-24
 * @brief: C++ file for class 'zerogl.Skeleton'.
 */
 
// Import header file.
#include "zerogl/Skeleton.hpp"

namespace zgl
{
	Skeleton::~Skeleton()
	{
		if(m_root != nullptr) delete m_root;
	}

	Skeleton::Node::~Node()
	{
		if(m_left != nullptr) delete m_left;
		if(m_right != nullptr) delete m_right;
	}

	Skeleton::Skeleton(Skeleton&& other) : m_root(other.m_root)
	{
		other.m_root = nullptr;
	}

	Skeleton& Skeleton::operator=(Skeleton&& other)
	{
		if (this != &other) {
			delete m_root;
			m_root = other.m_root;
			other.m_root = nullptr;
		}
		return *this;
	}

	void Skeleton::Node::hierarchize(Pose& pose) const
	{
		//std::cout << "Skeleton::Node::hierarchize " << ((int)m_poseIdx) << std::endl;
		if(m_left != nullptr) {
			//std::cout << "Skeleton::Node::left " << m_left << std::endl;
			pose[m_left->m_poseIdx] = pose[m_poseIdx]*pose[m_left->m_poseIdx];
			m_left->hierarchize(pose);
		}
		if(m_right != nullptr) {
			//std::cout << "Skeleton::Node::right " << m_right << std::endl;
			pose[m_right->m_poseIdx] = pose[m_poseIdx]*pose[m_right->m_poseIdx];
			m_right->hierarchize(pose);
		}
	}
} // End namespace zgl
