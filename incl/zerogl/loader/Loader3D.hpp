/**
 * @author: Asso Corentin
 * @date: 2025-02-21
 * @brief: Header for class 'zerogl.loader.Loader3D'.
 */

#ifndef H_ZGL_ZEROGL_LOADER_LOADER3D
#define H_ZGL_ZEROGL_LOADER_LOADER3D

// Includes
#include "zerogl/Mesh.hpp"
// End includes

namespace zgl
{
	/**
	 * @author: Asso Corentin
	 * @date: 2025-02-21
	 * @brief: Load 3D meshes
	 */
	class Loader3D
	{
	private:
	protected:
	public:
		static Mesh loadTriangle();
		static Mesh loadCube();
	}; // End class Loader3D

} // End namespace zgl

// Import template file.
#include "zerogl/loader/Loader3D.tcc"

#endif // H_ZGL_ZEROGL_LOADER_LOADER3D
