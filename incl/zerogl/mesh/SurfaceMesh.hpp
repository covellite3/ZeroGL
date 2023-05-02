/**
 * @author: Asso Corentin
 * @date: 2023-04-20
 * @brief: Header for class 'zerogl.mesh.SurfaceMesh'.
 */

#ifndef H_ZGL_ZEROGL_MESH_SURFACEMESH
#define H_ZGL_ZEROGL_MESH_SURFACEMESH

// Includes
#include <vector>
#include "zerogl/mesh/IMesh.hpp"
// End includes

namespace zgl
{
	/**
	 * @author: Asso Corentin
	 * @date: 2023-04-20
	 * @brief: Mesh for parametric surfaces.
	 */
	template<class F>
	class SurfaceMesh : public IMesh
	{
	private:
	protected:
		/** TODO comment */
		size_t m_nbOfVerticies, m_nbOfIndicies;

		/** TODO comment */
		std::vector<glm::vec3> m_vertices, m_normals;

		/** TODO comment */
		std::vector<glm::vec2> m_uvcoors;
		
		/** TODO comment */
		std::vector<GLuint> m_indicies;
	public:
		/** TODO comment */
		SurfaceMesh();

		/** TODO comment */
		SurfaceMesh(const size_t nbOfSegmentsWidth, const size_t nbOfSegmentsHeight, const F& surfaceFunctor);

		const glm::vec2* get2DPositions () const;
		const glm::vec3* get3DPositions () const;
		const glm::vec3* getRGBColors () const;
		const glm::vec3* getNormals () const;
		const glm::vec2* getUVcoords () const;
		const GLuint* getIndicies () const;
		//GLenum getRenderingMode () const;
		size_t getNumberOfVerticies () const;
		size_t getNumberOfIndicies () const;
		bool useIndex () const;
		Dimensions getDim () const;
	}; // End class SurfaceMesh

} // End namespace zgl

// Import template file.
#include "zerogl/mesh/SurfaceMesh.tcc"

#endif // H_ZGL_ZEROGL_MESH_SURFACEMESH
