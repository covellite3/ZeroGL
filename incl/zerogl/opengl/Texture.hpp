/**
 * @author: Corentin Asso
 * @date: 2025-03-12
 * @brief: Header for class 'zerogl.opengl.Texture'.
 */

#ifndef H_ZGL_ZEROGL_OPENGL_TEXTURE
#define H_ZGL_ZEROGL_OPENGL_TEXTURE

// Includes
#include <string>
#include <GL/glew.h>
#include <SFML/Graphics/Texture.hpp>

// End includes

namespace zgl
{
	/**
	 * @author: Corentin Asso
	 * @date: 2025-03-12
	 * @brief: Wrapper for OpenGL's textures.
	 */
	class Texture
	{
	private:
		GLuint m_handle;
	protected:
	public:
		Texture();
		~Texture();

		// Prevent copy
		Texture(const Texture &) = delete;
		Texture &operator=(const Texture &) = delete;

		// Allow move
		Texture(Texture &&other) noexcept;
		Texture &operator=(Texture &&other) noexcept;

		void release();

		bool loadFromFile(const std::string& filePath);

		inline auto isInit() const { return m_handle != 0; }
		inline auto getHandle() const { return m_handle; }

	}; // End class Texture

} // End namespace zgl

// Import template file.
#include "zerogl/opengl/Texture.tcc"

#endif // H_ZGL_ZEROGL_OPENGL_TEXTURE
