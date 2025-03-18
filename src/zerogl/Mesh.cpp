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
		: m_vbo(0), m_ebo(0), m_vao(0), m_useIndex(false), m_nAttributes(0), m_count(0), m_mode(0)
	{
		std::cout << "[Mesh + ] New empty Mesh" << std::endl;
	}

	Mesh::~Mesh()
	{
		if(this->isInit()) {
			std::cout << "[Mesh - ] Delete init Mesh" << std::endl;
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
		m_mode = 0;
		
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
		this->m_mode = other.m_mode;

		// Cleanup
		other.m_vbo = 0;
		other.m_ebo = 0;
		other.m_vao = 0;
		other.m_useIndex = false;
		other.m_nAttributes = 0;
		other.m_count = 0;
		other.m_mode = 0;
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
		m_mode = 0;
		// Extract other mesh
		std::cout << "[Mesh = ] Assign Mesh" << std::endl;
		if (this != &other) {
			this->m_vbo = other.m_vbo;
			this->m_ebo = other.m_ebo;
			this->m_vao = other.m_vao;
			this->m_useIndex = other.m_useIndex;
			this->m_nAttributes = other.m_nAttributes;
			this->m_count = other.m_count;
			this->m_mode = other.m_mode;
			// Empty other
			other.m_vao = 0;
			other.m_vbo = 0;
			other.m_ebo = 0;
		}
		return *this;
	}

	void Mesh::init(const uint8_t t_nAttributes, const bool t_useIndex, const GLenum t_mode)
	{
		assert(!this->isInit());
		this->m_nAttributes = t_nAttributes;
		this->m_useIndex = t_useIndex;
		this->m_mode = t_mode;
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


	void Mesh::send(const std::span<float>& position, const std::span<float>& normal, const std::span<float>& uv, const std::span<IndexType>& indices)
	{
		std::cout << "[Mesh ->] None animated mesh is sending attribute(s) " << (this->hasIndex() ? "and index" : "") << " to GPU" << std::endl;

		assert(this->isInit());
		assert(hasIndex() && indices.size() > 0);
		glBindVertexArray(m_vao);
		zglCheckOpenGL();

		// Calculate total vertex count
		if(hasIndex()) this->m_count = static_cast<uint32_t>(indices.size()); 
		else this->m_count = static_cast<uint32_t>(position.size() / 3); 

		// Calculate stride (position + normal + uv)
		GLsizei stride = sizeof(float) * (3 + 3 + 2);

		// Create a buffer to hold interleaved data
		std::vector<uint8_t> buffer(this->m_count * stride);

		// Interleave position, normal, and uv data
		size_t offset = 0;
		for (size_t i = 0; i < this->m_count; ++i)
		{
			memcpy(buffer.data() + offset, &position[i * 3], 3 * sizeof(float)); // Copy position
			offset += 3 * sizeof(float);

			memcpy(buffer.data() + offset, &normal[i * 3], 3 * sizeof(float)); // Copy normal
			offset += 3 * sizeof(float);

			memcpy(buffer.data() + offset, &uv[i * 2], 2 * sizeof(float)); // Copy uv
			offset += 2 * sizeof(float);
		}

		// Send the interleaved buffer to the GPU
		Mesh::_sendVboEbo(m_vbo, GL_ARRAY_BUFFER, buffer.size(), buffer.data());

		// Enable and set vertex attributes
		glEnableVertexAttribArray(0); // Position attribute
		zglCheckOpenGL();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
		zglCheckOpenGL();

		glEnableVertexAttribArray(1); // Normal attribute
		zglCheckOpenGL();
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(3 * sizeof(float)));
		zglCheckOpenGL();

		glEnableVertexAttribArray(2); // UV attribute
		zglCheckOpenGL();
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(6 * sizeof(float)));
		zglCheckOpenGL();

		// Send indices to GPU if available
		if (!indices.empty())
		{
			Mesh::_sendVboEbo(m_ebo, GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(IndexType), indices.data());
		}

		std::cout
			<< "[Mesh -X] Sent "
			<< buffer.size()
			<< " bytes with "
			<< (this->hasIndex() ? "an index" : "no index")
			<< ", a stride of " << stride
			<< ", and a count of " << m_count
			<< std::endl;

		// Disable vertex attributes
		/*glDisableVertexAttribArray(0);
		zglCheckOpenGL();
		glDisableVertexAttribArray(1);
		zglCheckOpenGL();
		glDisableVertexAttribArray(2);
		zglCheckOpenGL();*/
	}


	void Mesh::send(const std::span<float>& position, const std::span<float>& normal, const std::span<float>& uv, const std::span<float>& boneWeights, const std::span<uint32_t>& boneIndices, const std::span<IndexType>& indices)
	{
		std::cout << "[Mesh ->] Animated mesh sending attributes " << (this->hasIndex() ? "and index" : "") << " to GPU" << std::endl;

		assert(this->isInit());
		assert(hasIndex() && indices.size() > 0);
		glBindVertexArray(m_vao);
		zglCheckOpenGL();

		// Calculate total vertex count
		if (hasIndex()) this->m_count = static_cast<uint32_t>(indices.size());
		else this->m_count = static_cast<uint32_t>(position.size() / 3);

		// Calculate stride (position + normal + uv + bone weights + bone indices)
		GLsizei stride = sizeof(float) * (3 + 3 + 2 + 3) + sizeof(uint32_t) * 3;

		// Create a buffer to hold interleaved data
		std::vector<uint8_t> buffer(this->m_count * stride);

		// Interleave position, normal, uv, bone weights, and bone indices
		size_t offset = 0;
		for (size_t i = 0; i < this->m_count; ++i)
		{
			memcpy(buffer.data() + offset, &position[i * 3], 3 * sizeof(float)); // Copy position
			offset += 3 * sizeof(float);

			memcpy(buffer.data() + offset, &normal[i * 3], 3 * sizeof(float)); // Copy normal
			offset += 3 * sizeof(float);

			memcpy(buffer.data() + offset, &uv[i * 2], 2 * sizeof(float)); // Copy uv
			offset += 2 * sizeof(float);

			memcpy(buffer.data() + offset, &boneWeights[i * 3], 3 * sizeof(float)); // Copy bone weights
			offset += 3 * sizeof(float);

			memcpy(buffer.data() + offset, &boneIndices[i * 3], 3 * sizeof(uint32_t)); // Copy bone indices
			offset += 3 * sizeof(uint32_t);
		}

		// Send the interleaved buffer to the GPU
		Mesh::_sendVboEbo(m_vbo, GL_ARRAY_BUFFER, buffer.size(), buffer.data());

		// Enable and set vertex attributes
		glEnableVertexAttribArray(0); // Position attribute
		zglCheckOpenGL();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
		zglCheckOpenGL();

		glEnableVertexAttribArray(1); // Normal attribute
		zglCheckOpenGL();
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(3 * sizeof(float)));
		zglCheckOpenGL();

		glEnableVertexAttribArray(2); // UV attribute
		zglCheckOpenGL();
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(6 * sizeof(float)));
		zglCheckOpenGL();

		glEnableVertexAttribArray(3); // Bone weights attribute
		zglCheckOpenGL();
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(8 * sizeof(float)));
		zglCheckOpenGL();

		glEnableVertexAttribArray(4); // Bone indices attribute
		zglCheckOpenGL();
		glVertexAttribIPointer(4, 3, GL_UNSIGNED_INT, stride, reinterpret_cast<void*>(8 * sizeof(float) + 3 * sizeof(float)));
		zglCheckOpenGL();

		// Send indices to GPU if available
		if (!indices.empty())
		{
			Mesh::_sendVboEbo(m_ebo, GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(IndexType), indices.data());
		}

		std::cout
			<< "[Mesh -X] Sent "
			<< buffer.size()
			<< " bytes with "
			<< (this->hasIndex() ? "an index" : "no index")
			<< ", a stride of " << stride
			<< ", and a count of " << m_count
			<< std::endl;
	}


} // End namespace zgl
