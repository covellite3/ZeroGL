/**
 * @author: Asso Corentin
 * @date: 2025-02-21
 * @brief: C++ file for class 'zerogl.Mesh'.
 */
 
// Import header file.
#include "zerogl/Mesh.hpp"

namespace zgl
{
	Mesh::Mesh()
		: m_vbo(0), m_ebo(0), m_vao(0), m_useIndex(false), m_nAttributes(0), m_count(0)
	{
		std::cout << "[Mesh + ] New empty Mesh" << std::endl;
	}

	Mesh::~Mesh()
	{
		if(this->isInit()) {
			std::cout << "[Mesh - ] Delete Mesh" << std::endl;
		} else {
			std::cout << "[Mesh - ] Delete Mesh, but it was empty ;)" << std::endl;
		}
		if(this->m_useIndex) {
			glDeleteBuffers(1, &this->m_ebo);
			zglCheckOpenGL();
			m_ebo = 0;
			this->m_useIndex = false;
		}
		glDeleteBuffers(1, &this->m_vbo);
		zglCheckOpenGL();
		m_vbo = 0;
		m_nAttributes = 0;
		glDeleteVertexArrays(1, &this->m_vao);
		zglCheckOpenGL();
		m_vao = 0;
		m_count = 0;
		
	}

	Mesh::Mesh(Mesh&& other)
	{
		std::cout << "[Mesh > ] Move Mesh" << std::endl;
		this->m_vbo = other.m_vbo;
		this->m_ebo = other.m_ebo;
		this->m_vao = other.m_vao;
		this->m_useIndex = other.m_useIndex;
		this->m_nAttributes = other.m_nAttributes;
		this->m_count = other.m_count;
	}


	Mesh& Mesh::operator=(Mesh&& other) {
		assert(!this->isInit());
		// Erase previous mesh
		if(this->m_useIndex) {
			glDeleteBuffers(1, &this->m_ebo);
			zglCheckOpenGL();
			m_ebo = 0;
			this->m_useIndex = false;
		}
		glDeleteBuffers(1, &this->m_vbo);
		zglCheckOpenGL();
		m_vbo = 0;
		m_nAttributes = 0;
		glDeleteVertexArrays(1, &this->m_vao);
		zglCheckOpenGL();
		m_vao = 0;
		m_count = 0;
		// Extract other mesh
		std::cout << "[Mesh = ] Assign Mesh" << std::endl;
		if (this != &other) {
			this->m_vbo = other.m_vbo;
			this->m_ebo = other.m_ebo;
			this->m_vao = other.m_vao;
			this->m_useIndex = other.m_useIndex;
			this->m_nAttributes = other.m_nAttributes;
			this->m_count = other.m_count;
			// Empty other
			other.m_vao = 0;
			other.m_vbo = 0;
			other.m_ebo = 0;
		}
		return *this;
	}

	void Mesh::init(uint8_t t_nAttributes, bool t_useIndex)
	{
		assert(!this->isInit());
		this->m_nAttributes = t_nAttributes;
		this->m_useIndex = t_useIndex;
		std::cout << "[Mesh ! ] Create VAO" << std::endl;
		glGenVertexArrays(1, &this->m_vao);
		std::cout << "[Mesh ! ] Binding VAO " << this->m_vao <<  std::endl;
		glBindVertexArray(this->m_vao); 
		zglCheckOpenGL();
		if(this->m_useIndex) {
			std::cout << "[Mesh ! ] Create EBO" << std::endl;
			glGenBuffers(1, &this->m_ebo);
			zglCheckOpenGL();
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ebo);
			zglCheckOpenGL();
		}
		std::cout << "[Mesh ! ] Create VBO" << std::endl;
		glGenBuffers(1, &m_vbo);
		zglCheckOpenGL();
		glBindBuffer(GL_ARRAY_BUFFER, this->m_ebo);
		zglCheckOpenGL();
	}
} // End namespace zgl
