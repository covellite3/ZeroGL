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

		static constexpr size_t m_indexedLenght = 8;

		static constexpr glm::vec3 m_indexedPos3[m_indexedLenght] = {
			{ -1.0f, -1.0f,  1.0f },
			{  1.0f, -1.0f,  1.0f },
			{ -1.0f,  1.0f,  1.0f },
			{  1.0f,  1.0f,  1.0f },
			{ -1.0f, -1.0f, -1.0f },
			{  1.0f, -1.0f, -1.0f },
			{ -1.0f,  1.0f, -1.0f },
			{  1.0f,  1.0f, -1.0f } 
		};

		static constexpr GLuint m_indices[m_unindexedLenght] = {
			//Top
			2, 6, 7,
			2, 3, 7,

			//Bottom
			0, 4, 5,
			0, 1, 5,

			//Left
			0, 2, 6,
			0, 4, 6,

			//Right
			1, 3, 7,
			1, 5, 7,

			//Front
			0, 2, 3,
			0, 1, 3,

			//Back
			4, 6, 7,
			4, 5, 7
		};
	protected:
	public:
		/** TODO comment */
		CubeMesh(bool useIndex);

		const glm::vec2* get2DPositions () const;
		const glm::vec3* get3DPositions () const;
		const glm::vec3* getRGBColors () const;
		const glm::vec3* getNormals () const;
		const glm::vec2* getUVcoords () const;
		const size_t* getIndicies () const;
		//GLenum getRenderingMode () const;
		size_t getLenght () const;
		bool useIndex () const;
		Dimensions getDim () const;


	}; // End class CubeMesh

} // End namespace zgl

// Import template file.
#include "zerogl/mesh/CubeMesh.tcc"

#endif // H_ZGL_ZEROGL_MESH_CUBEMESH
