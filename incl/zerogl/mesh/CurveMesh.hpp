/**
 * @author: Corentin Asso
 * @date: 2023-03-30
 * @brief: Header for class 'zerogl.mesh.CurveMesh'.
 */

#ifndef H_ZGL_ZEROGL_MESH_CURVEMESH
#define H_ZGL_ZEROGL_MESH_CURVEMESH

// Includes
#include <vector>
#include "zerogl/curve/ICurve.hpp"
#include "zerogl/mesh/IMesh.hpp"
#include "zerogl/ZeroGL.hpp"
// End includes

namespace zgl
{
	/**
	 * @author: Corentin Asso
	 * @date: 2023-03-30
	 * @brief: Create a mesh for a curve.
	 */
	template<typename T, class F>
	class CurveMesh : public IMesh
	{
	private:
		/** TODO comment */
		size_t m_nbOfVerticies;
	protected:
		/** TODO comment */
		std::vector<T> m_vertices;
	public:
		/** TODO comment */
		CurveMesh();

		/** TODO comment */
		CurveMesh(const size_t nbOfSegments, const F& curveFunctor);

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

	}; // End class CurveMesh

} // End namespace zgl

// Import template file.
#include "zerogl/mesh/CurveMesh.tcc"

#endif // H_ZGL_ZEROGL_MESH_CURVEMESH
