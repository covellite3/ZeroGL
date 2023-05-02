/**
 * @author: Asso Corentin
 * @date: 2023-04-20
 * @brief: Header for class 'zerogl.surface.ISurface'.
 */

#ifndef H_ZGL_ZEROGL_SURFACE_ISURFACE
#define H_ZGL_ZEROGL_SURFACE_ISURFACE

// Includes
#include <cstddef>
// End includes

namespace zgl
{
	/**
	 * @author: Asso Corentin
	 * @date: 2023-04-20
	 * @brief: Interface for parametric surfaces.
	 */
	template<typename T>
	class ISurface
	{
	private:
	protected:
	public:
		virtual T operator() (const float u, const float w) const = 0;
	}; // End class ISurface

} // End namespace zgl

// Import template file.
#include "zerogl/surface/ISurface.tcc"

#endif // H_ZGL_ZEROGL_SURFACE_ISURFACE
