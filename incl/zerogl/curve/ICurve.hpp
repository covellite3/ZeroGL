/**
 * @author: Corentin Asso
 * @date: 2023-02-14
 * @brief: Header for class 'zerogl.curve.ICurve'.
 */

#ifndef H_ZGL_ZEROGL_CURVE_ICURVE
#define H_ZGL_ZEROGL_CURVE_ICURVE

// Includes
#include <cstddef>
// End includes

namespace zgl
{
	/**
	 * @author: Corentin Asso
	 * @date: 2023-02-14
	 * @brief: Curve interface.
	 */
	template<typename T>
	class ICurve
	{
	private:
	protected:
	public:
		/** TODO comment */
		virtual T operator() (const float t) const = 0;

		/** TODO comment */
		//virtual size_t getNumberOfControlPoints() const;

		/** TODO comment */
		//virtual const T* getControlPoints () const;
	}; // End class ICurve

} // End namespace zgl

// Import template file.
#include "zerogl/curve/ICurve.tcc"

#endif // H_ZGL_ZEROGL_CURVE_ICURVE
