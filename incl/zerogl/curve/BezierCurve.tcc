/**
 * @author: Corentin Asso
 * @date: 2023-02-14
 * @brief: Template file for class 'zerogl.curve.BezierCurve'.
 */
 
namespace zgl
{
	template<typename T>
	void BezierCurve<T>::addControlPoint(const T& point)
	{
		m_controlPoints.push_back(point);
	}

	template<typename T>
	T BezierCurve<T>::operator() (const float t) const
	{
		assert(t >= 0.0f-FLT_EPSILON);
		assert(t <= 1.0f+FLT_EPSILON);
		auto n = m_controlPoints.size()-1;
		T sum(0.0f);
		for (size_t i = 0; i < n+1; ++i) {
			float bern = bernsteinPolynomial(n, i, t);
			sum += bern*m_controlPoints[i];
		}
		return sum;
	}

	template<typename T>
	void BezierCurve<T>::unittest()
	{
		// TODO unittest
	}

} // End namespace zgl
