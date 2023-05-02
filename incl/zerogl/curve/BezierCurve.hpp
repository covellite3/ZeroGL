/**
 * @author: Corentin Asso
 * @date: 2023-02-14
 * @brief: Header for class 'zerogl.curve.BezierCurve'.
 */

#ifndef H_ZGL_ZEROGL_CURVE_BEZIERCURVE
#define H_ZGL_ZEROGL_CURVE_BEZIERCURVE

// Includes
#include <cassert>
#include <vector>
#include "zerogl/curve/ICurve.hpp"
#include "zerogl/ZeroGL.hpp"
#include "zerogl/Math.hpp"
// End includes

namespace zgl
{
	/**
	 * @author: Corentin Asso
	 * @date: 2023-02-14
	 * @brief: Bezier implementation.
	 */
	template<typename T>
	class BezierCurve : public ICurve<T>
	{
	private:
		/** Control points. */
		std::vector<T> m_controlPoints;
	protected:
	public:
		/** Add control points to the curve. */
		void addControlPoint(const T& point);

		/** Get point in Bezier's curve from t in [0;1]. */
		T operator() (const float t) const;

		/** TODO comment */
		inline auto getSize() { return m_controlPoints.size(); }

		/** TODO commment */
		static void unittest();
	}; // End class BezierCurve

} // End namespace zgl

// Import template file.
#include "zerogl/curve/BezierCurve.tcc"

#endif // H_ZGL_ZEROGL_CURVE_BEZIERCURVE
