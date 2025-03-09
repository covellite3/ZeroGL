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
		glm::vec3 m_sunDirection;
	protected:
	public:
		void render(Camera& camera);

		inline void add(std::shared_ptr<Entity>& entity) { m_entities.push_back(entity); }

		inline auto getSunDirection() const { return m_sunDirection; }
		inline void setSunDirection(const glm::vec3& t_sunDirection) { m_sunDirection = glm::normalize(t_sunDirection); }
		inline void setSkyColor(const glm::vec3& t_skyColor) { m_skyColor = t_skyColor; }
	}; // End class Scene

} // End namespace zgl

// Import template file.
#include "zerogl/Scene.tcc"

#endif // H_ZGL_ZEROGL_SCENE
