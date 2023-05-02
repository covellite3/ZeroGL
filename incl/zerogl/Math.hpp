/**
 * @author: Asso Corentin
 * @date: 2023-04-20
 * @brief: Header for class 'zerogl.Math'.
 */

#ifndef H_ZGL_ZEROGL_MATH
#define H_ZGL_ZEROGL_MATH

// Includes
// End includes

namespace zgl
{
	/**
	 * @author: Asso Corentin
	 * @date: 2023-04-20
	 * @brief: Collection of maths functions.
	 */
	class Math
	{
	private:
	protected:
	public:
		/** TODO commment */
		static void unittest();
	}; // End class Math
	
	/** Compute binomial coefficient. */
	int binomialCoeff(int n, int k);

	/** Return value of the berstein polynome. */
	float bernsteinPolynomial(int n, int i, float t);

} // End namespace zgl

// Import template file.
#include "zerogl/Math.tcc"

#endif // H_ZGL_ZEROGL_MATH
