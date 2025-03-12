/**
 * @author: Corentin Asso
 * @date: 2025-03-12
 * @brief: C++ file for class 'zerogl.opengl.Texture'.
 */
 
// Import header file.
#include "zerogl/opengl/Texture.hpp"
#include "zerogl/ZeroGL.hpp"
#include <SFML/Graphics.hpp>

namespace zgl
{
	Texture::Texture() : m_handle(0)
	{

	}

	Texture::~Texture()
	{
		release();
	}

	void Texture::release() {
		if (m_handle != 0) {
			glDeleteTextures(1, &m_handle);
			m_handle = 0;
		}
	}

	Texture::Texture(Texture &&other) noexcept : m_handle(other.m_handle)
	{
		other.m_handle= 0;
	}

	Texture &Texture::operator=(Texture &&other) noexcept {
		if (this != &other) {
			release();
			m_handle = other.m_handle;
			other.m_handle = 0;
		}
		return *this;
	}

	bool Texture::loadFromFile(const std::string& filePath) {
		if (isInit()) {
			throw std::runtime_error("Texture already initialized.");
		}

		sf::Image image;
		if(!image.loadFromFile(filePath)) return false;

		glGenTextures(1, &m_handle);
		zglCheckOpenGL();
		glBindTexture(GL_TEXTURE_2D, m_handle);
		zglCheckOpenGL();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		zglCheckOpenGL();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		zglCheckOpenGL();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		zglCheckOpenGL();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		zglCheckOpenGL();

		glBindTexture(GL_TEXTURE_2D, 0);
		zglCheckOpenGL();

		std::cout << "[Texture !] Init <" << m_handle << "> <- '"  << filePath << "'" << std::endl;
		
		return true;
	}

} // End namespace zgl
