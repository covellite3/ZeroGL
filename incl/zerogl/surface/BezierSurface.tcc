/**
 * @author: Asso Corentin
 * @date: 2023-04-20
 * @brief: Template file for class 'zerogl.surface.BezierSurface'.
 */
 
namespace zgl
{
	template<typename T>
	inline size_t BezierSurface<T>::getIndexCtrlMat (const size_t i, const size_t j) const
	{
		size_t index = i*m_ctrl_pts_width + j;
		assert(index < m_ctrl_pts_width * m_ctrl_pts_height);
		return index;
	}

	template<typename T>
	BezierSurface<T>::BezierSurface (const size_t ctrl_pts_width, const size_t ctrl_pts_height)
	: m_ctrl_matrix(new T[ctrl_pts_width*ctrl_pts_height]), m_ctrl_pts_width(ctrl_pts_width), m_ctrl_pts_height(ctrl_pts_height)
	{
	}

	template<typename T>
	void BezierSurface<T>::setControlPoint (size_t i, size_t j, const T& point)
	{
		m_ctrl_matrix[getIndexCtrlMat(i, j)] = point;
	}

	template<typename T>
	T BezierSurface<T>::operator() (const float u, const float w) const
	{
		assert(u >= 0.0f-FLT_EPSILON);
		assert(u <= 1.0f+FLT_EPSILON);
		assert(w >= 0.0f-FLT_EPSILON);
		assert(w <= 1.0f+FLT_EPSILON);
		auto n = m_ctrl_pts_width-1;
		auto m = m_ctrl_pts_height-1;
		T sum(0.0f);
		for (size_t i = 0; i < n+1; ++i) {
			for (size_t j = 0; j < m+1; ++j) {
				float bernI = bernsteinPolynomial(n, i, u);
				float bernJ = bernsteinPolynomial(m, j, w);
				sum += bernI*bernJ*m_ctrl_matrix[getIndexCtrlMat(i, j)];
			}
		}
		return sum;
	}
} // End namespace zgl
