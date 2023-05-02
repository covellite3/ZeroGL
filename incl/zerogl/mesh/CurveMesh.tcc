/**
 * @author: Corentin Asso
 * @date: 2023-03-30
 * @brief: Template file for class 'zerogl.mesh.CurveMesh'.
 */
 
namespace zgl
{
	template<typename T, class F>
	CurveMesh<T, F>::CurveMesh()
	: m_nbOfVerticies(0)
	{
		// Empty
	}

	template<typename T, class F>
	CurveMesh<T, F>::CurveMesh(const size_t nbOfSegments, const F& curveFunctor)
	{
		m_nbOfVerticies = nbOfSegments > 0 ? nbOfSegments + 1 : 0;
		// Compute 'every' points of the curve.

		float stride = 1.0f/(m_nbOfVerticies-1);
		for (size_t i = 0; i < m_nbOfVerticies; ++i) {
			m_vertices.push_back(curveFunctor(i*stride));
		}
	}

	template<typename T, class F>
	const glm::vec2* CurveMesh<T, F>::get2DPositions () const
	{
		if constexpr (std::is_same<T, glm::vec2>::value)
			return m_vertices.data();
		else
			return NULL;
	}

	template<typename T, class F>
	const glm::vec3* CurveMesh<T, F>::get3DPositions () const
	{
		if constexpr (std::is_same<T, glm::vec3>::value)
			return m_vertices.data();
		else
			return NULL;
	}

	template<typename T, class F>
	const glm::vec3* CurveMesh<T, F>::getRGBColors () const
	{
		return NULL;
	}

	template<typename T, class F>
	const glm::vec3* CurveMesh<T, F>::getNormals () const
	{
		return NULL;
	}

	template<typename T, class F>
	const glm::vec2* CurveMesh<T, F>::getUVcoords () const
	{
		return NULL;
	}

	template<typename T, class F>
	const GLuint* CurveMesh<T, F>::getIndicies () const
	{
		return NULL;
	}

	//GLenum getRenderingMode () const;
	
	template<typename T, class F>
	size_t CurveMesh<T, F>::getNumberOfVerticies () const
	{
		return m_nbOfVerticies;
	}
	
	template<typename T, class F>
	size_t CurveMesh<T, F>::getNumberOfIndicies () const
	{
		return 0;
	}

	template<typename T, class F>
	bool CurveMesh<T, F>::useIndex () const
	{
		return false;
	}

	template<typename T, class F>
	typename CurveMesh<T, F>::Dimensions CurveMesh<T, F>::getDim () const
	{
		if constexpr (std::is_same<T, glm::vec2>::value)
			return IMesh::Dimensions::TWO_DIM;
		else if constexpr (std::is_same<T, glm::vec3>::value)
			return IMesh::Dimensions::THREE_DIM;
		else
			return IMesh::Dimensions::UNKNOW;
	}
} // End namespace zgl
