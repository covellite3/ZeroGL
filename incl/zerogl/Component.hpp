/**
 * @author: Corentin Asso
 * @date: 2025-03-07
 * @brief: Header for class 'zerogl.Component'.
 */

#ifndef H_ZGL_ZEROGL_COMPONENT
#define H_ZGL_ZEROGL_COMPONENT

// Includes
// End includes

namespace zgl
{
	/**
	 * @author: Corentin Asso
	 * @date: 2025-03-07
	 * @brief: Component attachable to an entity. Like mesh, texture, bones, LOD system, another entity etc...
	 */
	class Component
	{
	private:
	protected:
	public:
		enum class Key
		{
			ENTITY,
			RENDERER,
			MODEL,
			SKELETON,
			ANIMATION,
		};

		// Ensure polymorphism for derived classes.
		virtual ~Component() = default;
	}; // End class Component

} // End namespace zgl

// Import template file.
#include "zerogl/Component.tcc"

#endif // H_ZGL_ZEROGL_COMPONENT
