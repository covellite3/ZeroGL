/**
 * @author: Corentin Asso
 * @date: 2025-02-24
 * @brief: Header for class 'zerogl.Scene'.
 */

#ifndef H_ZGL_ZEROGL_SCENE
#define H_ZGL_ZEROGL_SCENE

// Includes
#include "zerogl/Entity.hpp"
#include "zerogl/Camera.hpp"
#include "zerogl/Renderer.hpp"
#include "zerogl/Light.hpp"

#include <vector>
// End includes

namespace zgl
{
	class Camera;
	class Renderer;

	//class Renderer;

	/**
	 * @author: Corentin Asso
	 * @date: 2025-02-24
	 * @brief: A scene.
	 */
	class Scene
	{
	private:
		std::vector<std::shared_ptr<Entity>> m_entities;
		glm::vec3 m_skyColor;
		std::shared_ptr<Light> m_light;
	protected:
	public:
		void render(Camera& camera);

		inline void add(std::shared_ptr<Entity>& entity) { m_entities.push_back(entity); }

		inline void setSkyColor(const glm::vec3& t_skyColor) { m_skyColor = t_skyColor; }

		inline void setLight(std::shared_ptr<Light>& t_light) { m_light = t_light; }

		inline auto getLight() { return m_light; }
	}; // End class Scene

} // End namespace zgl

// Import template file.
#include "zerogl/Scene.tcc"

#endif // H_ZGL_ZEROGL_SCENE
