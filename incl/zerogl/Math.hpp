/**
 * @author: Asso Corentin
 * @date: 2023-04-20
 * @brief: Header for class 'zerogl.Math'.
 */

#ifndef H_ZGL_ZEROGL_MATH
#define H_ZGL_ZEROGL_MATH

// Includes
#include "zerogl/ZeroGL.hpp"
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

	/*
	 * QUATERNION
	 */

	/** Get oriented rotation around an pivot vector. */
	inline static glm::quat getQuaternion(const float rad, const glm::vec3& pivot) {
		double x = pivot.x * sin(rad / 2.0);
		double y = pivot.y * sin(rad / 2.0);
		double z = pivot.z * sin(rad / 2.0);
		double w = cos(rad / 2.0);
		return glm::quat((float)w, (float)x, (float)y, (float)z);
	}


} // End namespace zgl

// Import template file.
#include "zerogl/Math.tcc"

#endif // H_ZGL_ZEROGL_MATH
