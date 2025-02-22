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
		std::array<float, 9> normals = { 0.0f,  0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f };
		std::array<float, 6> uvs = { 0.0f, 0.0f, -0.5f, 0.5f, -0.5f, 0.0f };
		std::array<Mesh::IndexType, 3> indices = { 0, 1, 2 };

		mesh.send(
			3, std::span<float>(positions),           // POS
			3, std::span<float>(normals),             // NORMAL
			2, std::span<float>(uvs),                 // UV
			std::span<Mesh::IndexType>(indices)       // INDEX
		);

		return mesh;
	}

} // End namespace zgl
