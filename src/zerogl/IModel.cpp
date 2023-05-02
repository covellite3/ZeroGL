/**
 * @author: Corentin Asso
 * @date: 2023-03-31
 * @brief: C++ file for class 'zerogl.IModel'.
 */
 
// Import header file.
#include "zerogl/IModel.hpp"

namespace zgl
{
	IModel::IModel()
	: m_lenght(0)
	{
		// Empty
	}

	void IModel::render(ShaderProgram& shaderProgram, const GLenum mode)
	{
		//std::cout << __FILE__ << "::" << __func__ << " " << mode << " " << m_lenght << std::endl;
		shaderProgram.draw(m_vao, mode, 0, m_lenght);
	}
} // End namespace zgl
