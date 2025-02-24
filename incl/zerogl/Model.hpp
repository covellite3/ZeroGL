/**
 * @author: Asso Corentin
 * @date: 2025-02-21
 * @brief: Header for class 'zerogl.Model'.
 */

#ifndef H_ZGL_ZEROGL_MODEL
#define H_ZGL_ZEROGL_MODEL

// Includes
#include "zerogl/Entity.hpp"
#include "zerogl/Mesh.hpp"
#include "zerogl/Material.hpp"
#include "zerogl/Skeleton.hpp"
// End includes

namespace zgl
{
	/**
	 * @author: Asso Corentin
	 * @date: 2025-02-21
	 * @brief: TODO.
	 */
	template<size_t DIMENSION=3>
	class Model : Entity<DIMENSION>
	{
	private:
		Mesh m_mesh;
		Material m_material;
		Skeleton m_skeleton;
	protected:
	public:
		Model(Mesh&& t_mesh, Material&& t_material, Skeleton&& m_Skeleton);
	}; // End class Model

} // End namespace zgl

// Import template file.
#include "zerogl/Model.tcc"

#endif // H_ZGL_ZEROGL_MODEL
