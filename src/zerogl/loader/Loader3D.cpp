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
		mesh.init(/*t_nAttributes*/3, /*t_useIndex*/true, GL_TRIANGLES);

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
		mesh.init(/*t_nAttributes*/3, /*t_useIndex*/true, GL_TRIANGLES);

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
		mesh.init(/*t_nAttributes*/3, /*t_useIndex*/true, GL_TRIANGLES);

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





	void Loader3D::calculateBoneWeights(
		const std::vector<float>& positions,
		const std::vector<float>& handles,
		std::vector<float>& weights,
		std::vector<uint32_t>& boneIndices)
	{
		assert(positions.size() % 3 == 0);
		assert(handles.size() % 3 == 0);
		assert(weights.empty());
		assert(boneIndices.empty());

		size_t nbrOfVertices = positions.size() / 3;
		size_t nbrHandles = handles.size() / 3;

		weights.resize(nbrOfVertices*3);
		boneIndices.resize(nbrOfVertices*3);



		for (size_t iVertex = 0; iVertex < nbrOfVertices; ++iVertex) {
			int iFirstClosest = 0, iSecondClosest = 0, iThirdClosest = 0;
			float distFirst = -1, distSecond = -1, distThird = -1;

			// Get the position of the current vertex
			float xVertex = positions[iVertex * 3];
			float yVertex = positions[iVertex * 3 + 1];
			float zVertex = positions[iVertex * 3 + 2];

			for (size_t iHandle = 0; iHandle < nbrHandles; ++iHandle) {
				// Get the position of the current handle
				float xHandle = handles[iHandle * 3];
				float yHandle = handles[iHandle * 3 + 1];
				float zHandle = handles[iHandle * 3 + 2];

				// Compute the distance between the vertex and the handle
				float dist = static_cast<float>(std::sqrt(std::pow(xVertex - xHandle, 2) +
									   std::pow(yVertex - yHandle, 2) +
									   std::pow(zVertex - zHandle, 2)));

				// Update the closest bones
				if (distFirst == -1 || dist < distFirst) {
					distThird = distSecond;
					iThirdClosest = iSecondClosest;

					distSecond = distFirst;
					iSecondClosest = iFirstClosest;

					distFirst = dist;
					iFirstClosest = static_cast<int>(iHandle);
				} else if (distSecond == -1 || dist < distSecond) {
					distThird = distSecond;
					iThirdClosest = iSecondClosest;

					distSecond = dist;
					iSecondClosest = static_cast<int>(iHandle);
				} else if (distThird == -1 || dist < distThird) {
					distThird = dist;
					iThirdClosest = static_cast<int>(iHandle);
				}
			}

			// Inverse distance weights
			float totalDist = std::max(0.f, distFirst) + std::max(0.f, distSecond) + std::max(0.f, distThird);
			assert(totalDist > 0);
			if (totalDist > 0) {
				weights[iVertex * 3] = std::max(0.f, distFirst) / totalDist;
				weights[iVertex * 3 + 1] = std::max(0.f, distSecond) / totalDist;
				weights[iVertex * 3 + 2] = std::max(0.f, distThird) / totalDist;
			} else {
				weights[iVertex * 3] = 0.0f;
				weights[iVertex * 3 + 1] = 0.0f;
				weights[iVertex * 3 + 2] = 0.0f;
			}
			assert(std::abs(weights[iVertex * 3] + weights[iVertex * 3 + 1] + weights[iVertex * 3 + 2] - 1.0) <= 0.0001);

			// Store the bone indices
			boneIndices[iVertex * 3] = iFirstClosest;
			boneIndices[iVertex * 3 + 1] = iSecondClosest;
			boneIndices[iVertex * 3 + 2] = iThirdClosest;
		}
	}

	
	std::tuple<Mesh, Skeleton> Loader3D::loadAnimatedCylinder(size_t nbrArcs, size_t nbrSections, size_t nbrOfBones, float lenght, float radius)
	{
		std::tuple<Mesh, Skeleton> meshAndSkeleton;
		Mesh& mesh = std::get<0>(meshAndSkeleton);
		Skeleton& skeleton = std::get<1>(meshAndSkeleton);
		mesh.init(/*t_nAttributes*/5, /*t_useIndex*/true, GL_TRIANGLE_STRIP);

		float axleIncrement = lenght / static_cast<float>(nbrSections);
		float phiIncrement = static_cast<float>((2.0 * M_PI) / static_cast<double>(nbrArcs));

		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> uvs;
		std::vector<float> weights;
		std::vector<uint32_t> boneIndices;
		std::vector<Mesh::IndexType> indices;

		for (size_t iSection = 0; iSection <= nbrSections; ++iSection) {
			float axlePos = static_cast<float>(iSection) * axleIncrement;
			for (size_t iArcSegment = 0; iArcSegment <= nbrArcs; ++iArcSegment) {
				float phi = static_cast<float>(iArcSegment) * phiIncrement;

				// Position
				float x = radius * static_cast<float>(cos(static_cast<double>(phi)));
				float y = radius * static_cast<float>(sin(static_cast<double>(phi)));
				float z = axlePos - lenght/2;
				positions.push_back(x);
				positions.push_back(y);
				positions.push_back(z);

				// Normal
				normals.push_back(x);
				normals.push_back(y);
				normals.push_back(0.0f);

				// UV
				float u = static_cast<float>(iArcSegment) / static_cast<float>(nbrArcs);
				float v = axlePos;
				uvs.push_back(u);
				uvs.push_back(v);
			}
		}

		for (size_t iSection = 0; iSection < nbrSections; ++iSection) {
			for (size_t iArcSegment = 0; iArcSegment <= nbrArcs; ++iArcSegment) {
				Mesh::IndexType current = static_cast<Mesh::IndexType>(
					iSection * (nbrArcs + 1) + iArcSegment
				);
				Mesh::IndexType next = static_cast<Mesh::IndexType>(
					(iSection + 1) * (nbrArcs + 1) + iArcSegment
				);

				indices.push_back(current);
				indices.push_back(next);
			}
		}

		// Create bones & skeleton
		std::vector<float> handles;
		auto itTree = skeleton.addRoot(0);
		auto handlesSpacing = lenght / static_cast<float>(nbrOfBones - 1);
		for(size_t iBone = 0; iBone < nbrOfBones; ++iBone)
		{
			handles.push_back(0);
			handles.push_back(0);
			handles.push_back(static_cast<float>(iBone)*handlesSpacing - lenght / 2);

			if(iBone < nbrOfBones-1) {
				itTree = itTree->addLeft(static_cast<uint8_t>(iBone+1));
			}
			
		}
		std::cout << "Loader3D skeleton tree: " << skeleton.getRoot()->toString() << std::endl;

		// Assign a weight to 3 bones for each vertices
		calculateBoneWeights(positions, handles, weights, boneIndices);

		mesh.send(
			std::span<float>(positions.data(), positions.size()),
			std::span<float>(normals.data(), normals.size()),
			std::span<float>(uvs.data(), uvs.size()),
			std::span<float>(weights.data(), weights.size()),
			std::span<uint32_t>(boneIndices.data(), boneIndices.size()),
			std::span<Mesh::IndexType>(indices.data(), indices.size())
		);

		return meshAndSkeleton;
	}

} // End namespace zgl
