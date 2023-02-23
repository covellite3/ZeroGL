/**
 * @author: Corentin Asso
 * @date: 2023-02-14
 * @brief: Header for class 'zerogl.mesh.CubeMesh'.
 */

#ifndef H_ZGL_ZEROGL_MESH_CUBEMESH
#define H_ZGL_ZEROGL_MESH_CUBEMESH

// Includes
#include "zerogl/ZeroGL.hpp"
#include "zerogl/mesh/IMesh.hpp"
// End includes

namespace zgl
{
	/**
	 * @author: Corentin Asso
	 * @date: 2023-02-14
	 * @brief: Cube mesh definition.
	 */
	//template<typename INDEX_T>
	class CubeMesh : public IMesh
	{
	private:
		/** TODO comment */
		bool m_useIndex;

		/** TODO comment */
		static constexpr size_t m_unindexedLenght = 36;

		/** TODO comment */
		static constexpr glm::vec3 m_unindexedPos3[m_unindexedLenght] = {
			{-1.0f,-1.0f,-1.0f},
			{-1.0f,-1.0f, 1.0f},
			{-1.0f, 1.0f, 1.0f},
					      
			{ 1.0f, 1.0f,-1.0f},
			{-1.0f,-1.0f,-1.0f},
			{-1.0f, 1.0f,-1.0f},
					       
			{ 1.0f,-1.0f, 1.0f},
			{-1.0f,-1.0f,-1.0f},
			{ 1.0f,-1.0f,-1.0f},

			{ 1.0f, 1.0f,-1.0f},
			{ 1.0f,-1.0f,-1.0f},
			{-1.0f,-1.0f,-1.0f},

			{-1.0f,-1.0f,-1.0f},
			{-1.0f, 1.0f, 1.0f},
			{-1.0f, 1.0f,-1.0f},

			{ 1.0f,-1.0f, 1.0f},
			{-1.0f,-1.0f, 1.0f},
			{-1.0f,-1.0f,-1.0f},

			{-1.0f, 1.0f, 1.0f},
			{-1.0f,-1.0f, 1.0f},
			{ 1.0f,-1.0f, 1.0f},

			{1.0f, 1.0f, 1.0f},
			{1.0f,-1.0f,-1.0f},
			{1.0f, 1.0f,-1.0f},

			{1.0f,-1.0f,-1.0f},
			{1.0f, 1.0f, 1.0f},
			{1.0f,-1.0f, 1.0f},

			{ 1.0f, 1.0f, 1.0f},
			{ 1.0f, 1.0f,-1.0f},
			{-1.0f, 1.0f,-1.0f},

			{ 1.0f, 1.0f, 1.0f},
			{-1.0f, 1.0f,-1.0f},
			{-1.0f, 1.0f, 1.0f},

			{ 1.0f, 1.0f, 1.0f},
			{-1.0f, 1.0f, 1.0f},
			{ 1.0f,-1.0f, 1.0f}
		};
	protected:
	public:
		/** TODO comment */
		CubeMesh(bool useIndex);

		virtual const glm::vec2* get2DPositions () const override;
		virtual const glm::vec3* get3DPositions () const override;
		virtual const glm::vec3* getRGBColors () const override;
		virtual const glm::vec3* getNormals () const override;
		virtual const glm::vec2* getUVcoords () const override;
		virtual const size_t* getIndicies () const override;
		//virtual GLenum getRenderingMode () const override;
		virtual size_t getLenght () const override;
		virtual bool useIndex () const override;
		virtual Dimensions getDim () const override;


	}; // End class CubeMesh

} // End namespace zgl

// Import template file.
#include "zerogl/mesh/CubeMesh.tcc"

#endif // H_ZGL_ZEROGL_MESH_CUBEMESH
