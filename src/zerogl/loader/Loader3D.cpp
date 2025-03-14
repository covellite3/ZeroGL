/**
 * @author: Asso Corentin
 * @date: 2025-02-21
 * @brief: C++ file for class 'zerogl.loader.Loader3D'.
 */
 
// Import header file.
#include "zerogl/loader/Loader3D.hpp"

namespace zgl
{

	Mesh Loader3D::loadQuad()
	{

		Mesh mesh;
		mesh.init(/*t_nAttributes*/3, /*t_useIndex*/true);

		std::array<float, 12> positions = {
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f
		};
		std::array<float, 12> normals = {
			0.0f,  0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f
		};
		std::array<float, 8> uvs = {
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 0.0f,
			1.0f, 1.0f
		};
		std::array<Mesh::IndexType, 6> indices = {
			0, 1, 2,
			2, 1, 3
		};

		mesh.send(
			std::span<float>(positions),           // POS
			std::span<float>(normals),             // NORMAL
			std::span<float>(uvs),                 // UV
			std::span<Mesh::IndexType>(indices)       // INDEX
		);

		return mesh;
	}

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
			// Vertices for each face of the cube
			1, -1, -1,  1, -1,  1,  1,  1,  1,  1,  1, -1, // +X face
			-1, -1, -1, -1,  1, -1, -1,  1,  1, -1, -1,  1, // -X face
			-1,  1, -1,  1,  1, -1,  1,  1,  1, -1,  1,  1, // +Y face
			-1, -1, -1, -1, -1,  1,  1, -1,  1,  1, -1, -1, // -Y face
			1, -1,  1, -1, -1,  1, -1,  1,  1,  1,  1,  1, // +Z face
			1, -1, -1,  1,  1, -1, -1,  1, -1, -1, -1, -1  // -Z face
		};

		std::array<float, 36*3> normals = {
			// Normals for each face of the cube
			1, 0, 0,  1, 0, 0,  1, 0, 0,  1, 0, 0, // +X face
			-1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, // -X face
			0, 1, 0,  0, 1, 0,  0, 1, 0,  0, 1, 0, // +Y face
			0, -1, 0,  0, -1, 0,  0, -1, 0,  0, -1, 0, // -Y face
			0, 0, 1,  0, 0, 1,  0, 0, 1,  0, 0, 1, // +Z face
			0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1  // -Z face
		};

		std::array<float, 36*2> uvs = {
			// UV coordinates for each face
			1, 0,  0, 0,  0, 1,  1, 1, // +X face
			1, 0,  0, 0,  0, 1,  1, 1, // -X face
			1, 0,  0, 0,  0, 1,  1, 1, // +Y face
			1, 0,  0, 0,  0, 1,  1, 1, // -Y face
			1, 0,  0, 0,  0, 1,  1, 1, // +Z face
			1, 0,  0, 0,  0, 1,  1, 1  // -Z face
		};

		std::array<Mesh::IndexType, 36> indices = {
			// Indices for triangles in each face
			0, 1, 2,  0, 2, 3,  // +X face
			4, 5, 6,  4, 6, 7,  // -X face
			8, 9, 10, 8, 10,11, // +Y face
			12,13,14, 12,14,15, // -Y face
			16,17,18, 16,18,19, // +Z face
			20,21,22, 20,22,23  // -Z face
		};

		mesh.send(
			std::span<float>(positions),           // POS
			std::span<float>(normals),             // NORMAL
			std::span<float>(uvs),                 // UV
			std::span<Mesh::IndexType>(indices)    // INDEX
		);

		return mesh;
	}


} // End namespace zgl
