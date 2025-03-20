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

#include <SFML/System.hpp>
#include <vector>
// End includes

namespace zgl
{
	class Camera;
	class Renderer;
	class Entity;

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
		std::shared_ptr<Light> m_light;

		/** The given sky color for each renderer types */
		std::unordered_map<Component::Key, glm::vec3> m_skyColors;
	protected:
	public:
		/**
		 * rendererType: RENDERER_0, RENDERER_1, ...
		 */
		void render(const Component::Key& rendererType, Camera& camera, const sf::Time& time);

		inline void add(std::shared_ptr<Entity>& entity) { m_entities.push_back(entity); }

		inline void setSkyColor(const Component::Key& rendererType, const glm::vec3& t_skyColor) { m_skyColors[rendererType] = t_skyColor; }

		inline void setLight(std::shared_ptr<Light>& t_light) { m_light = t_light; }

		inline auto getLight() { return m_light; }
	}; // End class Scene

} // End namespace zgl

// Import template file.
#include "zerogl/Scene.tcc"

#endif // H_ZGL_ZEROGL_SCENE
