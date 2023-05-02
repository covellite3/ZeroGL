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
		assert(false); // 3D cube cannot be interpreted has a 2D shape.
		return NULL;
	}

	const glm::vec3* CubeMesh::get3DPositions () const
	{
		return s_pos3;
	}

	const glm::vec3* CubeMesh::getRGBColors () const
	{
		assert(false);
		return NULL;
	}

	const glm::vec3* CubeMesh::getNormals () const
	{
		return s_normal;
	}

	const glm::vec2* CubeMesh::getUVcoords () const
	{
		return s_uv;
	}

	const GLuint* CubeMesh::getIndicies () const
	{
		return s_indices;
	}

	size_t CubeMesh::getNumberOfVerticies () const
	{
		assert(m_useIndex);
		return s_lenght;
	}

	size_t CubeMesh::getNumberOfIndicies () const
	{
		assert(m_useIndex);
		return s_lenght;
	}

	bool CubeMesh::useIndex () const
	{
		return m_useIndex;
	}

	IMesh::Dimensions CubeMesh::getDim () const
	{
		return IMesh::Dimensions::THREE_DIM;
	}

} // End namespace zgl
