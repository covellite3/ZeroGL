/**
 * @author: Corentin Asso
 * @date: 2023-02-14
 * @brief: C++ file for class 'zerogl.mesh.CubeMesh'.
 */
 
// Import header file.
#include "zerogl/mesh/CubeMesh.hpp"

namespace zgl
{
	CubeMesh::CubeMesh(bool useIndex) : m_useIndex(useIndex)
	{
		// Empty
	}

	const glm::vec2* CubeMesh::get2DPositions () const
	{
		return NULL;
	}

	const glm::vec3* CubeMesh::get3DPositions () const
	{
		if (m_useIndex) {
			return NULL;
		} else {
			return m_unindexedPos3;
		}
	}

	const glm::vec3* CubeMesh::getRGBColors () const
	{
		return NULL;
	}

	const glm::vec3* CubeMesh::getNormals () const
	{
		return NULL;
	}

	const glm::vec2* CubeMesh::getUVcoords () const
	{
		return NULL;
	}

	const size_t* CubeMesh::getIndicies () const
	{
		return NULL;
	}

	size_t CubeMesh::getLenght () const
	{
		if (m_useIndex) {
			return 0;
		} else {
			return m_unindexedLenght;
		}
	}

	bool CubeMesh::useIndex () const
	{
		return m_useIndex;
	}

	IMesh::Dimensions CubeMesh::getDim () const
	{
		return 3D;
	}

} // End namespace zgl
