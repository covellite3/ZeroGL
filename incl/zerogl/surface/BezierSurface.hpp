/**
 * @author: Asso Corentin
 * @date: 2023-04-20
 * @brief: Header for class 'zerogl.surface.BezierSurface'.
 */

#ifndef H_ZGL_ZEROGL_SURFACE_BEZIERSURFACE
#define H_ZGL_ZEROGL_SURFACE_BEZIERSURFACE

// Includes
#include <memory>
#include <cassert>
#include <cfloat>
#include "zerogl/surface/ISurface.hpp"
#include "zerogl/Math.hpp"
// End includes

namespace zgl
{
	/**
	 * @author: Asso Corentin
	 * @date: 2023-04-20
	 * @brief: Class for defining Bezier's surfaces.
	 */
	template<typename T>
	class BezierSurface : public ISurface<T>
	{
	private:
	protected:
		/** Matrix who store controle points.  */
		std::shared_ptr<T[]> m_ctrl_matrix;

		/** Controle points matrix dimension. */
		size_t m_ctrl_pts_width, m_ctrl_pts_height;

		/** Get memory index of controle points in from two indicies. */
		inline size_t getIndexCtrlMat (const size_t i, const size_t j) const;
	public:
		/** Create a bezier surface of n*m controle points. */
		BezierSurface (const size_t ctrl_pts_width, const size_t ctrl_pts_height);

		/** Add control points to the curve. */
		void setControlPoint (size_t i, size_t j, const T& point);

		/** Functor, get bezier curve at u,v coord between 0 and 1. */
		T operator() (const float u, const float w) const;
	}; // End class BezierSurface

} // End namespace zgl

// Import template file.
#include "zerogl/surface/BezierSurface.tcc"

#endif // H_ZGL_ZEROGL_SURFACE_BEZIERSURFACE
