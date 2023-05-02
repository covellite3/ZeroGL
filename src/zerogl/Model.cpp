/**
 * @author: Corentin Asso
 * @date: 2023-03-31
 * @brief: C++ file for class 'zerogl.Model'.
 */
 
// Import header file.
#include "zerogl/Model.hpp"
#include <vector>

namespace zgl
{
	Model::Model()
	: IModel()
	{
		// Empty
	}

	void Model::init(const IMesh& mesh)
	{
		m_lenght = mesh.useIndex() ? mesh.getNumberOfIndicies() : mesh.getNumberOfVerticies();
		//std::cout << __FILE__ << "::" << __func__ << " " << m_lenght << std::endl;

		// Interwine attribute in a single array [pos, normal, uv, ...]
		std::vector<float> interwined;
		for (size_t i = 0; i < mesh.getNumberOfVerticies(); ++i) {
			auto pos = mesh.get3DPositions()[i];
			auto normal = mesh.getNormals()[i];
			auto uv = mesh.getUVcoords()[i];

			interwined.push_back(pos.x);	
			interwined.push_back(pos.y);	
			interwined.push_back(pos.z);	

			interwined.push_back(normal.x);	
			interwined.push_back(normal.y);	
			interwined.push_back(normal.z);	

			interwined.push_back(uv.x);	
			interwined.push_back(uv.y);	
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
		size_t width_normal = 3*sizeof(float);
		size_t width_uv = 2*sizeof(float);
		size_t stride = width_pos + width_normal + width_uv;
		m_vao.init();

		// Position
		m_vao.enableAttribPointer(0);
		m_vao.setAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0, m_vbo);
		
		// Normal
		m_vao.enableAttribPointer(1);
		m_vao.setAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)width_pos, m_vbo);
		
		// UV
		m_vao.enableAttribPointer(2);
		m_vao.setAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(width_pos + width_normal), m_vbo);

		if (mesh.useIndex()) {
			m_vao.setElementArrayBuffer(m_ebo);
		}
	}
} // End namespace zgl
