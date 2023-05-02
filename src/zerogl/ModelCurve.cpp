/**
 * @author: Asso Corentin
 * @date: 2023-04-19
 * @brief: C++ file for class 'zerogl.ModelCurve'.
 */
 
// Import header file.
#include "zerogl/ModelCurve.hpp"
#include <vector>

namespace zgl
{
	ModelCurve::ModelCurve()
	: IModel()
	{
		// Empty
	}

	void ModelCurve::init(const IMesh& mesh)
	{
		m_lenght = mesh.useIndex() ? mesh.getNumberOfIndicies() : mesh.getNumberOfVerticies();

		// Interwine attribute in a single array [pos]
		std::vector<float> interwined;
		for (size_t i = 0; i < mesh.getNumberOfVerticies(); ++i) {
			auto pos = mesh.get3DPositions()[i];

			interwined.push_back(pos.x);	
			interwined.push_back(pos.y);	
			interwined.push_back(pos.z);	
		}

		// VBO
		m_vbo.init(GL_ARRAY_BUFFER);
		m_vbo.send(interwined.size()*sizeof(float), interwined.data(), GL_STATIC_DRAW);
		zglCheckOpenGL();

		// EBO
		if (mesh.useIndex()) {
			m_ebo.init(GL_ELEMENT_ARRAY_BUFFER);
			m_ebo.send(mesh.getNumberOfIndicies()*sizeof(GLuint), mesh.getIndicies(), GL_STATIC_DRAW);
			zglCheckOpenGL();
		}

		// VAO
		size_t width_pos = 3*sizeof(float);
		size_t stride = width_pos;
		m_vao.init();

		// Position
		m_vao.enableAttribPointer(0);
		m_vao.setAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0, m_vbo);
		
		if (mesh.useIndex()) {
			m_vao.setElementArrayBuffer(m_ebo);
		}
	}
} // End namespace zgl
