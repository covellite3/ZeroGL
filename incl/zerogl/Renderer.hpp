/**
 * @author: Corentin Asso
 * @date: 2025-03-08
 * @brief: Header for class 'zerogl.Renderer'.
 */

#ifndef H_ZGL_ZEROGL_RENDERER
#define H_ZGL_ZEROGL_RENDERER

// Includes
#include "zerogl/Component.hpp"
#include "zerogl/Camera.hpp"
#include "zerogl/Model.hpp"
#include "zerogl/Entity.hpp"
#include "zerogl/Scene.hpp"
#include "zerogl/opengl/ShaderProgram.hpp"
#include <memory>
// End includes

namespace zgl
{
	class Scene;
	class Camera;
	/**
	 * @author: Corentin Asso
	 * @date: 2025-03-08
	 * @brief: Rendering pipeline of the scene.
	 */
	class Renderer : public Component
	{
	private:
		std::shared_ptr<ShaderProgram> m_shaderProgram;
	protected:
	public:
		void render(Scene& scene, Camera& camera, Entity& entity);

		inline void setShaderProgram(std::shared_ptr<ShaderProgram> t_shaderProgram)
		{
			m_shaderProgram = t_shaderProgram;
		}

	}; // End class Renderer

} // End namespace zgl

// Import template file.
#include "zerogl/Renderer.tcc"

#endif // H_ZGL_ZEROGL_RENDERER
