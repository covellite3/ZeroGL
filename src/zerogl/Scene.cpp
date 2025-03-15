/**
 * @author: Corentin Asso
 * @date: 2025-02-24
 * @brief: C++ file for class 'zerogl.Scene'.
 */
 
// Import header file.
#include "zerogl/Scene.hpp"

namespace zgl
{
	void Scene::render(const Component::Key& rendererType, Camera& camera)
	{
		auto skyColor = m_skyColors[rendererType];
		glClearColor(skyColor.x, skyColor.y, skyColor.z, 1.0f);
		zglCheckOpenGL();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		zglCheckOpenGL();
		for(auto& p_entity : m_entities)
		{
			Renderer& renderer = dynamic_cast<Renderer&>(p_entity->template getAttachment<Renderer>(rendererType));
			renderer.render(*this, camera, *p_entity.get());
		}

	}
} // End namespace zgl
