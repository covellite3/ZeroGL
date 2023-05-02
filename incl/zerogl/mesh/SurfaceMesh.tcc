/**
 * @author: Asso Corentin
 * @date: 2023-04-20
 * @brief: Template file for class 'zerogl.mesh.SurfaceMesh'.
 */
 
namespace zgl
{
	template<class F>
	SurfaceMesh<F>::SurfaceMesh()
	: IMesh(), m_nbOfVerticies(0), m_nbOfIndicies(0)
	{
		// Empty
	}

	template<class F>
	SurfaceMesh<F>::SurfaceMesh(const size_t nbOfSegmentsWidth, const size_t nbOfSegmentsHeight, const F& curveFunctor)
	{
		size_t nbOfVerticiesWidth = nbOfSegmentsWidth > 0 ? nbOfSegmentsWidth + 1 : 0;
		size_t nbOfVerticiesHeight = nbOfSegmentsHeight > 0 ? nbOfSegmentsHeight + 1 : 0;
		m_nbOfVerticies = ((nbOfVerticiesWidth-1) * (nbOfVerticiesHeight-1)) * 4;
		m_nbOfIndicies = ((nbOfVerticiesWidth-1) * (nbOfVerticiesHeight-1)) * 6;
		// Compute 'every' points of the surface.

		float strideX = 1.0f/(nbOfVerticiesWidth-1);
		float strideY = 1.0f/(nbOfVerticiesHeight-1);
		size_t offset_index = 0;
		for (size_t i = 0; i < nbOfVerticiesWidth-1; ++i) {
			for (size_t j = 0; j < nbOfVerticiesHeight-1; ++j) {
				// Position
				m_vertices.push_back(curveFunctor((i+0)*strideX, (j+0)*strideY)); // 0
				m_vertices.push_back(curveFunctor((i+0)*strideX, (j+1)*strideY)); // 1
				m_vertices.push_back(curveFunctor((i+1)*strideX, (j+0)*strideY)); // 2
				m_vertices.push_back(curveFunctor((i+1)*strideX, (j+1)*strideY)); // 3

				// UV
				m_uvcoors.push_back(glm::vec2((i+0)*strideX, (j+0)*strideY));
				m_uvcoors.push_back(glm::vec2((i+0)*strideX, (j+1)*strideY));
				m_uvcoors.push_back(glm::vec2((i+1)*strideX, (j+0)*strideY));
				m_uvcoors.push_back(glm::vec2((i+1)*strideX, (j+1)*strideY));

				//Normal
				// Bottomleft
				glm::vec3 a = m_vertices[offset_index+0]-m_vertices[offset_index+1];
				glm::vec3 b = m_vertices[offset_index+0]-m_vertices[offset_index+2];
				glm::vec3 normal = -glm::normalize(glm::cross(a, b));
				m_normals.push_back(normal);

				// Upperleft
				a = m_vertices[offset_index+1]-m_vertices[offset_index+0];
				b = m_vertices[offset_index+1]-m_vertices[offset_index+3];
				normal = glm::normalize(glm::cross(a, b));
				m_normals.push_back(normal);

				// Bottomright
				a = m_vertices[offset_index+2]-m_vertices[offset_index+1];
				b = m_vertices[offset_index+2]-m_vertices[offset_index+3];
				normal = -glm::normalize(glm::cross(a, b));
				m_normals.push_back(normal);

				// Upperright
				a = m_vertices[offset_index+3]-m_vertices[offset_index+1];
				b = m_vertices[offset_index+3]-m_vertices[offset_index+2];
				normal = glm::normalize(glm::cross(a, b));
				m_normals.push_back(normal);

				// Indicies
				m_indicies.push_back(offset_index + 3);
				m_indicies.push_back(offset_index + 1);
				m_indicies.push_back(offset_index + 0);
				m_indicies.push_back(offset_index + 0);
				m_indicies.push_back(offset_index + 2);
				m_indicies.push_back(offset_index + 3);

				offset_index += 4;

				/*std::cout <<
				nbOfVerticiesWidth << " " <<
				nbOfVerticiesHeight << " " <<
				m_nbOfVerticies << " " <<
				m_nbOfIndicies << " " <<
				offset_index << " " <<
				strideX << " " <<
				strideY << " " <<
				std::endl;*/

				assert(offset_index == m_vertices.size());
			}
		}
		assert(offset_index == m_nbOfVerticies);
		assert(m_indicies.size() == m_nbOfIndicies);

		/*for (auto it = m_vertices.begin(); it != m_vertices.end(); ++it) std::cout << "(" << (*it).x << ":" << (*it).y << ":" << (*it).z << "), ";
		std::cout << std::endl;
		for (auto it = m_indicies.begin(); it != m_indicies.end(); ++it) std::cout << *it << ", ";
		std::cout << std::endl;*/
	}

	template<class F>
	const glm::vec2* SurfaceMesh<F>::get2DPositions () const
	{
		assert(false);
		return NULL;
	}

	template<class F>
	const glm::vec3* SurfaceMesh<F>::get3DPositions () const
	{
		return m_vertices.data();
	}

	template<class F>
	const glm::vec3* SurfaceMesh<F>::getRGBColors () const
	{
		assert(false);
		return NULL;
	}

	template<class F>
	const glm::vec3* SurfaceMesh<F>::getNormals () const
	{
		return m_normals.data();
	}

	template<class F>
	const glm::vec2* SurfaceMesh<F>::getUVcoords () const
	{
		return m_uvcoors.data();
	}

	template<class F>
	const GLuint* SurfaceMesh<F>::getIndicies () const
	{
		return m_indicies.data();
	}

	template<class F>
	size_t SurfaceMesh<F>::getNumberOfVerticies () const
	{
		return m_nbOfVerticies;
	}

	template<class F>
	size_t SurfaceMesh<F>::getNumberOfIndicies () const
	{
		return m_nbOfIndicies;
	}

	template<class F>
	bool SurfaceMesh<F>::useIndex () const
	{
		return true;
	}

	template<class F>
	typename SurfaceMesh<F>::Dimensions SurfaceMesh<F>::getDim () const
	{
		return IMesh::Dimensions::THREE_DIM;
	}
} // End namespace zgl
