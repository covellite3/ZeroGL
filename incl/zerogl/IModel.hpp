/**
 * @author: Corentin Asso
 * @date: 2023-03-31
 * @brief: Header for class 'zerogl.IModel'.
 */

#ifndef H_ZGL_ZEROGL_IMODEL
#define H_ZGL_ZEROGL_IMODEL

// Includes
#include "zerogl/mesh/IMesh.hpp"
#include "zerogl/ZeroGL.hpp"
// End includes

namespace zgl
{
	/**
	 * @author: Corentin Asso
	 * @date: 2023-03-31
	 * @brief: Interface for model class, wrapper of meshes.
	 */
	class IModel
	{
	private:
	protected:
		ArrayBuffer m_vbo, m_ebo;
		VertexArray m_vao;
		size_t m_lenght;
	public:
		IModel();
		void render(ShaderProgram& shaderProgram, const GLenum mode);
	}; // End class IModel

} // End namespace zgl

// Import template file.
#include "zerogl/IModel.tcc"

#endif // H_ZGL_ZEROGL_IMODEL
