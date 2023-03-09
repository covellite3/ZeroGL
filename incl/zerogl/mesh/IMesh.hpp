/**
 * @author: Corentin Asso
 * @date: 2023-02-14
 * @brief: Header for class 'zerogl.mesh.IMesh'.
 */

#ifndef H_ZGL_ZEROGL_MESH_IMESH
#define H_ZGL_ZEROGL_MESH_IMESH

// Includes
#include <type_traits>
#include "zerogl/ZeroGL.hpp"
// End includes

namespace zgl
{

	/**
	 * @author: Corentin Asso
	 * @date: 2023-02-14
	 * @brief: Mesh interface.
	 */
	//template<typename INDEX_T>
	class IMesh
	{
		//static_assert(std::is_unsigned<INDEX_T>::value, "The type used for indexing must be an unsigned integer.");
	private:
	protected:
	public:
		//typedef enum { TWO_DIM = 2, THREE_DIM = 3 } Dimensions;
		enum class Dimensions { TWO_DIM = 2, THREE_DIM = 3 };

		IMesh ();

		/** Get 2D position of each verticies. */
		virtual const glm::vec2* get2DPositions () const = 0;

		/** Get 3D position of each verticies. */
		virtual const glm::vec3* get3DPositions () const = 0;

		/** Get RGB color of each verticies. */
		virtual const glm::vec3* getRGBColors () const = 0;

		/** Get normal of each verticies. */
		virtual const glm::vec3* getNormals () const = 0;

		/** Get UV coordinates of each verticies. */
		virtual const glm::vec2* getUVcoords () const = 0;

		/** Get array indexing verticies.  */
		virtual const size_t* getIndicies () const = 0;

		/** OpengGL rendering mode: GL_TRIANGLES, GL_POINTS, etc... */
		//virtual GLenum getRenderingMode ();

		/** Number of verticies. */
		virtual size_t getNumberOfVerticies () const = 0;

		/** Number of indicies. */
		virtual size_t getNumberOfIndicies () const = 0;

		/** Say if we use an index for this mesh. */
		virtual bool useIndex () const = 0;

		/** Get number of component per coodinate. */
		virtual Dimensions getDim () const = 0;

	}; // End class IMesh

} // End namespace zgl

// Import template file.
#include "zerogl/mesh/IMesh.tcc"

#endif // H_ZGL_ZEROGL_MESH_IMESH
