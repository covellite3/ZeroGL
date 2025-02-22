/**
 * @author: Asso Corentin
 * @date: 2023-04-20
 * @brief: C++ file for class 'zerogl.Math'.
 */
 
// Import header file.
#include "zerogl/Math.hpp"

#include <cassert>
#include <cmath>

namespace zgl
{
	int binomialCoeff(int n, int k)
	{
		assert(n >= 0);
		assert(k >= 0);
		if (k > n)
			return 0;
		if (k == 0 || n == k)
			return 1;
		return binomialCoeff(n-1, k-1)
			+ binomialCoeff(n-1, k);
	}

	float bernsteinPolynomial(int n, int i, float t)
	{
		float a = (float)binomialCoeff(n, i);
		float b = std::pow((float)t, (float)i);
		float c =  std::pow(1.0f-t, (float)(n-i));
		return a*b*c;
	}

	void Math::unittest()
	{
		//////
		// binomialCoeff
		//////
		// n = 0
		assert(binomialCoeff(0, 0) == 1);
		assert(binomialCoeff(0, 1) == 0);
		assert(binomialCoeff(0, 2) == 0);
		assert(binomialCoeff(0, 3) == 0);
		assert(binomialCoeff(0, 4) == 0);

		// n = 1
		assert(binomialCoeff(1, 0) == 1);
		assert(binomialCoeff(1, 1) == 1);
		assert(binomialCoeff(1, 2) == 0);
		assert(binomialCoeff(1, 3) == 0);
		assert(binomialCoeff(1, 4) == 0);

		// n = 2
		assert(binomialCoeff(2, 0) == 1);
		assert(binomialCoeff(2, 1) == 2);
		assert(binomialCoeff(2, 2) == 1);
		assert(binomialCoeff(2, 3) == 0);
		assert(binomialCoeff(2, 4) == 0);

		// n = 3
		assert(binomialCoeff(3, 0) == 1);
		assert(binomialCoeff(3, 1) == 3);
		assert(binomialCoeff(3, 2) == 3);
		assert(binomialCoeff(3, 3) == 1);
		assert(binomialCoeff(3, 4) == 0);

		// n = 4
		assert(binomialCoeff(4, 0) == 1);
		assert(binomialCoeff(4, 1) == 4);
		assert(binomialCoeff(4, 2) == 6);
		assert(binomialCoeff(4, 3) == 4);
		assert(binomialCoeff(4, 4) == 1);
	}
} // End namespace zgl
