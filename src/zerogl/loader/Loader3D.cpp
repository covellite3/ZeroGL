/**
 * @author: Asso Corentin
 * @date: 2025-02-21
 * @brief: C++ file for class 'zerogl.loader.Loader3D'.
 */
 
// Import header file.
#include "zerogl/loader/Loader3D.hpp"

namespace zgl
{


	Mesh Loader3D::loadTriangle()
	{

		Mesh mesh;
		mesh.init(/*t_nAttributes*/3, /*t_useIndex*/true);

		std::array<float, 9> positions = { 0.0f,  0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f };
		std::array<float, 9> normals = { 0.0f,  0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f };
		std::array<float, 6> uvs = { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f };
		std::array<Mesh::IndexType, 3> indices = { 0, 1, 2 };

		mesh.send(
			std::span<float>(positions),           // POS
			std::span<float>(normals),             // NORMAL
			std::span<float>(uvs),                 // UV
			std::span<Mesh::IndexType>(indices)       // INDEX
		);

		return mesh;
	}


	Mesh Loader3D::loadCube()
	{
		Mesh mesh;
		mesh.init(/*t_nAttributes*/3, /*t_useIndex*/true);

		std::array<float, 36*3> positions = {
			// Back
			-1.0f,-1.0f,-1.0f,
			-1.0f, 1.0f,-1.0f,
			 1.0f, 1.0f,-1.0f,
			 1.0f, 1.0f,-1.0f,
			 1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f,

			// Front
			-1.0f,-1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f,
			 1.0f,-1.0f, 1.0f,
			-1.0f,-1.0f, 1.0f,

			// Left
			-1.0f,-1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f,-1.0f,
			-1.0f, 1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f, 1.0f,

			// Right
			 1.0f,-1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f,-1.0f,
			 1.0f, 1.0f,-1.0f,
			 1.0f,-1.0f,-1.0f,
			 1.0f,-1.0f, 1.0f,

			// Top
			-1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f,-1.0f,
			-1.0f, 1.0f,-1.0f,
			 1.0f, 1.0f,-1.0f,
			 1.0f, 1.0f, 1.0f,

			// Bottom
			-1.0f, -1.0f, 1.0f,
			 1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f,-1.0f,
			-1.0f, -1.0f,-1.0f,
			 1.0f, -1.0f,-1.0f,
			 1.0f, -1.0f, 1.0f
		};

		std::array<float, 36*3> normals = {
  			// Back			
			 0.0f,  0.0f, -1.0f,
			 0.0f,  0.0f, -1.0f,
			 0.0f,  0.0f, -1.0f,

			 0.0f,  0.0f, -1.0f,
			 0.0f,  0.0f, -1.0f,
			 0.0f,  0.0f, -1.0f,

			// Front
			 0.0f,  0.0f,  1.0f,
			 0.0f,  0.0f,  1.0f,
			 0.0f,  0.0f,  1.0f,

			 0.0f,  0.0f,  1.0f,
			 0.0f,  0.0f,  1.0f,
			 0.0f,  0.0f,  1.0f,

			// Left
			-1.0f,  0.0f,  0.0f,
			-1.0f,  0.0f,  0.0f,
			-1.0f,  0.0f,  0.0f,

			-1.0f,  0.0f,  0.0f,
			-1.0f,  0.0f,  0.0f,
			-1.0f,  0.0f,  0.0f,

			// Right
			 1.0f,  0.0f,  0.0f,
			 1.0f,  0.0f,  0.0f,
			 1.0f,  0.0f,  0.0f,

			 1.0f,  0.0f,  0.0f,
			 1.0f,  0.0f,  0.0f,
			 1.0f,  0.0f,  0.0f,

			// Top
			 0.0f,  1.0f,  0.0f,
			 0.0f,  1.0f,  0.0f,
			 0.0f,  1.0f,  0.0f,

			 0.0f,  1.0f,  0.0f,
			 0.0f,  1.0f,  0.0f,
			 0.0f,  1.0f,  0.0f,

			// Bottom
			 0.0f, -1.0f,  0.0f,
			 0.0f, -1.0f,  0.0f,
			 0.0f, -1.0f,  0.0f,

			 0.0f, -1.0f,  0.0f,
			 0.0f, -1.0f,  0.0f,
			 0.0f, -1.0f,  0.0f
		};


		std::array<float, 36*2> uvs = {
			// Back
			 0.0f, 0.0f,
			 0.0f, 1.0f,
			 1.0f, 1.0f,
			 1.0f, 1.0f,
			 1.0f, 0.0f,
			 0.0f, 0.0f,

			// Front
			 0.0f, 0.0f,
			 1.0f, 0.0f,
			 1.0f, 1.0f,
			 1.0f, 1.0f,
			 0.0f, 1.0f,
			 0.0f, 0.0f,

			// Left
			 0.0f, 0.0f,
			 0.0f, 1.0f,
			 1.0f, 1.0f,
			 1.0f, 1.0f,
			 1.0f, 0.0f,
			 0.0f, 0.0f,

			// Right
			 0.0f, 0.0f,
			 0.0f, 1.0f,
			 1.0f, 1.0f,
			 1.0f, 1.0f,
			 1.0f, 0.0f,
			 0.0f, 0.0f,

			// Top
			 0.0f, 0.0f,
			 0.0f, 1.0f,
			 1.0f, 1.0f,
			 1.0f, 1.0f,
			 1.0f, 0.0f,
			 0.0f, 0.0f,

			// Bottom
			 0.0f, 0.0f,
			 0.0f, 1.0f,
			 1.0f, 1.0f,
			 1.0f, 1.0f,
			 1.0f, 0.0f,
			 0.0f, 0.0f
		};

		std::array<Mesh::IndexType, 36> indices = {
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

		mesh.send(
			std::span<float>(positions),           // POS
			std::span<float>(normals),             // NORMAL
			std::span<float>(uvs),                 // UV
			std::span<Mesh::IndexType>(indices)       // INDEX
		);

		return mesh;
	}


} // End namespace zgl
