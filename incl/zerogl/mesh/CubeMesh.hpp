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
		static constexpr size_t s_lenght = 36;

		/** TODO comment */
		static constexpr glm::vec3 s_pos3[s_lenght] = {		      

			// Back
			{-1.0f,-1.0f,-1.0f},
			{-1.0f, 1.0f,-1.0f},
			{ 1.0f, 1.0f,-1.0f},
			{ 1.0f, 1.0f,-1.0f},
			{ 1.0f,-1.0f,-1.0f},
			{-1.0f,-1.0f,-1.0f},

			// Front
			{-1.0f,-1.0f, 1.0f},
			{-1.0f, 1.0f, 1.0f},
			{ 1.0f, 1.0f, 1.0f},
			{ 1.0f, 1.0f, 1.0f},
			{ 1.0f,-1.0f, 1.0f},
			{-1.0f,-1.0f, 1.0f},

			// Left
			{-1.0f,-1.0f, 1.0f},
			{-1.0f, 1.0f, 1.0f},
			{-1.0f, 1.0f,-1.0f},
			{-1.0f, 1.0f,-1.0f},
			{-1.0f,-1.0f,-1.0f},
			{-1.0f,-1.0f, 1.0f},

			// Right
			{ 1.0f,-1.0f, 1.0f},
			{ 1.0f, 1.0f, 1.0f},
			{ 1.0f, 1.0f,-1.0f},
			{ 1.0f, 1.0f,-1.0f},
			{ 1.0f,-1.0f,-1.0f},
			{ 1.0f,-1.0f, 1.0f},

			// Top
			{-1.0f, 1.0f, 1.0f},
			{ 1.0f, 1.0f, 1.0f},
			{-1.0f, 1.0f,-1.0f},
			{-1.0f, 1.0f,-1.0f},
			{ 1.0f, 1.0f,-1.0f},
			{ 1.0f, 1.0f, 1.0f},

			// Bottom
			{-1.0f, -1.0f, 1.0f},
			{ 1.0f, -1.0f, 1.0f},
			{-1.0f, -1.0f,-1.0f},
			{-1.0f, -1.0f,-1.0f},
			{ 1.0f, -1.0f,-1.0f},
			{ 1.0f, -1.0f, 1.0f}

		};

		static constexpr glm::vec3 s_normal[s_lenght] = {
			
  			// Back			
			{ 0.0f,  0.0f, -1.0f},
			{ 0.0f,  0.0f, -1.0f},
			{ 0.0f,  0.0f, -1.0f},

			{ 0.0f,  0.0f, -1.0f},
			{ 0.0f,  0.0f, -1.0f},
			{ 0.0f,  0.0f, -1.0f},

			// Front
			{ 0.0f,  0.0f,  1.0f},
			{ 0.0f,  0.0f,  1.0f},
			{ 0.0f,  0.0f,  1.0f},

			{ 0.0f,  0.0f,  1.0f},
			{ 0.0f,  0.0f,  1.0f},
			{ 0.0f,  0.0f,  1.0f},

			// Left
			{-1.0f,  0.0f,  0.0f},
			{-1.0f,  0.0f,  0.0f},
			{-1.0f,  0.0f,  0.0f},

			{-1.0f,  0.0f,  0.0f},
			{-1.0f,  0.0f,  0.0f},
			{-1.0f,  0.0f,  0.0f},

			// Right
			{ 1.0f,  0.0f,  0.0f},
			{ 1.0f,  0.0f,  0.0f},
			{ 1.0f,  0.0f,  0.0f},

			{ 1.0f,  0.0f,  0.0f},
			{ 1.0f,  0.0f,  0.0f},
			{ 1.0f,  0.0f,  0.0f},

			// Top
			{ 0.0f,  1.0f,  0.0f},
			{ 0.0f,  1.0f,  0.0f},
			{ 0.0f,  1.0f,  0.0f},

			{ 0.0f,  1.0f,  0.0f},
			{ 0.0f,  1.0f,  0.0f},
			{ 0.0f,  1.0f,  0.0f},

			// Bottom
			{ 0.0f, -1.0f,  0.0f},
			{ 0.0f, -1.0f,  0.0f},
			{ 0.0f, -1.0f,  0.0f},

			{ 0.0f, -1.0f,  0.0f},
			{ 0.0f, -1.0f,  0.0f},
			{ 0.0f, -1.0f,  0.0f}
		};

		static constexpr glm::vec2 s_uv[s_lenght] = {		      

			// Back
			{ 0.0f, 0.0f},
			{ 0.0f, 1.0f},
			{ 1.0f, 1.0f},
			{ 0.0f, 0.0f},
			{ 1.0f, 0.0f},
			{ 1.0f, 1.0f},

			// Front
			{ 0.0f, 0.0f},
			{ 0.0f, 1.0f},
			{ 1.0f, 1.0f},
			{ 0.0f, 0.0f},
			{ 1.0f, 0.0f},
			{ 1.0f, 1.0f},

			// Left
			{ 0.0f, 0.0f},
			{ 0.0f, 1.0f},
			{ 1.0f, 1.0f},
			{ 0.0f, 0.0f},
			{ 1.0f, 0.0f},
			{ 1.0f, 1.0f},

			// Right
			{ 0.0f, 0.0f},
			{ 0.0f, 1.0f},
			{ 1.0f, 1.0f},
			{ 0.0f, 0.0f},
			{ 1.0f, 0.0f},
			{ 1.0f, 1.0f},

			// TOP
			{ 0.0f, 0.0f},
			{ 0.0f, 1.0f},
			{ 1.0f, 1.0f},
			{ 0.0f, 0.0f},
			{ 1.0f, 0.0f},
			{ 1.0f, 1.0f},
	

			// Bottom
			{ 0.0f, 0.0f},
			{ 0.0f, 1.0f},
			{ 1.0f, 1.0f},
			{ 0.0f, 0.0f},
			{ 1.0f, 0.0f},
			{ 1.0f, 1.0f}
		};



		static constexpr GLuint s_indices[s_lenght] = {
			 0,  1,  2,
			 3,  4,  5,

			 6,  7,  8,
			 9, 10, 11,

			12, 13, 14, 
			15, 16, 17,
		       
			18, 19, 20,	
			21, 22, 23,

			24, 25, 26,
			27, 28, 29,
		       	
			30, 31,	32,
		       	33, 34, 35
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
		const GLuint* getIndicies () const;
		//GLenum getRenderingMode () const;
		size_t getNumberOfVerticies () const;
		size_t getNumberOfIndicies () const;
		bool useIndex () const;
		Dimensions getDim () const;


	}; // End class CubeMesh

} // End namespace zgl

// Import template file.
#include "zerogl/mesh/CubeMesh.tcc"

#endif // H_ZGL_ZEROGL_MESH_CUBEMESH
