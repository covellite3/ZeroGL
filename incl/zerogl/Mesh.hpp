/**
 * @author: Asso Corentin
 * @date: 2025-02-21
 * @brief: Header for class 'zerogl.Mesh'.
 */

#ifndef H_ZGL_ZEROGL_MESH
#define H_ZGL_ZEROGL_MESH

// Includes
#include <span>
#include <array>
#include <vector>
#include <type_traits>
#include "zerogl/opengl/OpenGL.hpp"
// End includes

namespace zgl
{
	/**
	 * @author: Asso Corentin
	 * @date: 2025-02-21
	 * @brief: TODO comment.
	 */
	class Mesh
	{
	public:
		using IndexType = uint32_t;
		static constexpr size_t MAX_ATTRIBUTES = 16;
	private:
		GLuint m_vbo;
		GLuint m_ebo;
		GLuint m_vao;
		bool m_useIndex;
		uint8_t m_nAttributes;
		uint32_t m_count;

		/**
		 * GL_TRIANGLES
		 * GL_TRIANGLE_STRIP
		 * ...
		 */
		GLenum m_mode;

		///
		/// Send
		///


		/** Send an VBO or an EBO to GPU */
		template <typename T>
		static inline void _sendVboEbo(GLuint vbo_or_ebo, GLenum target, const size_t size, const T* p_buffer)
		{
			assert(target == GL_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER);

			std::cout << "[_sendVboEbo] Binding buffer: Target=" << target 
				  << ", VBO/EBO=" << vbo_or_ebo 
				  << ", Type=" << typeid(T).name() << std::endl;
			glBindBuffer(target, vbo_or_ebo);
			zglCheckOpenGL();

			std::cout << "[_sendVboEbo] Uploading data: Size=" << size 
				  << ", Type size=" << sizeof(T) 
				  << ", Type=" << typeid(T).name() << std::endl;
			glBufferData(target, size * sizeof(T), p_buffer, GL_STATIC_DRAW);

			std::cout << "[_sendVboEbo] Buffer uploaded successfully." << std::endl;
			zglCheckOpenGL();
		}


		//
		// Attributes
		//

		/** For each attribute. */
		/*template <size_t attribNumber, typename T>
		inline void _setInfoAttrib(const size_t stride, const size_t nComponents)
		{
			static_assert(std::is_arithmetic<T>::value, "Wrong attribute type, not supported by OpengGL.");
			GLenum type; 
			if constexpr(std::is_same<T, GLfloat>::value) type = GL_FLOAT;
			else if constexpr(std::is_same<T, GLhalf>::value) type = GL_HALF_FLOAT;
			else if constexpr(std::is_same<T, GLdouble>::value) type = GL_DOUBLE;
			else if constexpr(std::is_same<T, GLbyte>::value) type = GL_BYTE;
			else if constexpr(std::is_same<T, GLubyte>::value) type = GL_UNSIGNED_BYTE;
			else if constexpr(std::is_same<T, GLshort>::value) type = GL_SHORT;
			else if constexpr(std::is_same<T, GLushort>::value) type = GL_UNSIGNED_SHORT;
			else if constexpr(std::is_same<T, GLint>::value) type = GL_INT;
			else if constexpr(std::is_same<T, GLuint>::value) type = GL_UNSIGNED_INT;
			else static_assert(false, "Attribute can use either float or int.");
			glVertexAttribPointer(attribNumber, static_cast<GLint>(nComponents), type, GL_FALSE, static_cast<GLsizei>(stride), (void*)0);
			zglCheckOpenGL();
			glEnableVertexAttribArray(attribNumber);
			zglCheckOpenGL();
		}*/

		/*template <size_t IT, typename T, typename... Args>
		inline void _forEach([[maybe_unused]] const size_t stride, const std::span<T>& index, Args... args)
		{
			static_assert(sizeof...(args) == 0, "No more arguments after index.");
			_sendVboEbo<T>(this->m_ebo, GL_ELEMENT_ARRAY_BUFFER, index.size(), index.data());
		}*/

		/*template <size_t IT, typename T, typename... Args>
		inline void _forEach(const size_t stride, size_t nComponents, [[maybe_unused]] const std::span<T>& attrib, Args... args)
		{
			if constexpr(sizeof...(args) <= 0) {
				return;
			} else {
				_setInfoAttrib<IT, T>(stride, nComponents);
				_forEach<IT+1>(stride, args...);
			}
		}*/

		///
		/// Stride
		///
		/** For each attrib */
		/*template <typename T, typename... Args>
		size_t _getStride(const size_t nComponents, [[maybe_unused]] const std::span<T>& attrib, Args... args)
		{
			if constexpr(sizeof...(args) <= 1)
				return 0;
			else
				return sizeof(T)*nComponents + _getStride<>(args...); 
		}*/

		///
		/// Buffer size
		///
		/*template <typename T, typename... Args>
		size_t _getBufferSize([[maybe_unused]] const size_t nComponents, const std::span<T>& attrib, Args... args)
		{
			if constexpr(sizeof...(args) <= 1)
				return 0;
			else
				return sizeof(T)*attrib.size() + _getBufferSize<>(args...);
		}*/

		///
		/// Interwine
		///
		/** For each attribute */
		/*template <typename T, typename... Args>
		void _interwine(size_t offset, std::vector<uint8_t>& buffer, const size_t stride, const size_t nComponents, const std::span<T>& attrib, Args... args)
		{
			assert(attrib.size()%nComponents == 0); // Attribute is a multiple of the number of components
			if constexpr(sizeof...(args) <= 1) {	
				assert(offset == stride); // Last offset after all attributes is equivalent to stride
			} else {
				for(size_t idxVertice = 0; idxVertice < this->m_count; ++idxVertice) {
					memcpy(buffer.data()+idxVertice*stride+offset, &attrib[idxVertice*nComponents], nComponents*sizeof(T));
				}
				size_t addedOffset = offset + sizeof(T)*nComponents; 
				return _interwine<>(addedOffset, buffer, stride, args...); 
			}



		}*/

	protected:
	public:
		Mesh();
		~Mesh();

		Mesh(const Mesh& other) = delete;
		Mesh(Mesh&& other);

		Mesh& operator=(const Mesh& other) = delete;
		Mesh& operator=(Mesh&& other);

		void init(const uint8_t t_nAttributes, const bool t_useIndex, const GLenum t_mode);

		void send(const std::span<float>& position, const std::span<float>& normal, const std::span<float>& uv, const std::span<IndexType>& indices);

		/*template <typename T, typename... Args>
		inline void send(const size_t nComponents, const std::span<T>& attrib, Args... args)
		{
			std::cout << "[Mesh ->] Mesh is sending attribute(s) " << (this->hasIndex() ? "and index" : "") << " to GPU" << std::endl;
			assert(this->isInit());
			glBindVertexArray(m_vao);
			zglCheckOpenGL();
			this->m_count = static_cast<uint32_t>(attrib.size() / nComponents);
			size_t stride = _getStride<>(nComponents, attrib, args...);
			std::vector<uint8_t> buffer(_getBufferSize(nComponents, attrib, args...));
			_interwine<>(0, buffer, stride, nComponents, attrib, args...);
			Mesh::_sendVboEbo(m_vbo, GL_ARRAY_BUFFER, buffer.size(), buffer.data());
			_forEach<0>(stride, nComponents, attrib, args...); 
			std::cout
				<< "[Mesh -X] Sended "
				<< buffer.size()
				<< " bytes with "
				<< (this->hasIndex() ? "an index" : "no index")
				<< " and a stride of "
				<< stride
				<< " and count of "
				<< m_count
				<< std::endl;
		}*/





		inline void draw(const ShaderProgram& shader) const
		{
			assert(this->isInit());
			assert(this->m_count > 0);
			//assert(m_status == LINKED);
			zglCheckOpenGL();
			ShaderProgram::bind(shader);
			glBindVertexArray(this->m_vao);
			zglCheckOpenGL();
			if (this->hasIndex()) {
				GLenum type;
				if constexpr(std::is_same<IndexType, GLubyte>::value) type = GL_UNSIGNED_BYTE;
				else if constexpr(std::is_same<IndexType, GLushort>::value) type = GL_UNSIGNED_SHORT;
				else if constexpr(std::is_same<IndexType, GLuint>::value) type = GL_UNSIGNED_INT;
				else static_assert("Mesh's index's typeIndex must be an unsigned integer.");
				glDrawElements(m_mode, static_cast<GLuint>(this->m_count), type, 0);
			} else {
				glDrawArrays(m_mode, 0, static_cast<GLuint>(this->m_count));
			}
			zglCheckOpenGL();	
		}



		inline bool isInit() const { return m_vao != 0; }
		inline bool hasIndex() const{ return m_useIndex; }

	}; // End class Mesh

} // End namespace zgl

// Import template file.
#include "zerogl/Mesh.tcc"

#endif // H_ZGL_ZEROGL_MESH
