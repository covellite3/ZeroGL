/**
 * @author: Corentin Asso
 * @date: 2025-02-24
 * @brief: C++ file for class 'zerogl.Scene'.
 */
 
// Import header file.
#include "zerogl/Scene.hpp"

namespace zgl
{
	void Scene::render(Camera& camera)
	{
		glClearColor(m_skyColor.x, m_skyColor.y, m_skyColor.z, 1.0f);
		zglCheckOpenGL();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		zglCheckOpenGL();
		for(auto& p_entity : m_entities)
		{
			Renderer& renderer = dynamic_cast<Renderer&>(p_entity->template getAttachment<Renderer>(Component::Key::RENDERER));
			renderer.render(*this, camera, *p_entity.get());
		}

	}
} // End namespace zgl
