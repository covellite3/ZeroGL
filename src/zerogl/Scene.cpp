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
		// If camera has a valide framebuffer, we render to it otherwise we render to the default framebuffer (the screen)
		if(camera.getFramebuffer() != nullptr && camera.getFramebuffer()->isInit()) {
			camera.getFramebuffer()->bind();
			//std::cout << "Bound framebuffer " << FrameBuffer::getBound()  << std::endl;
		} else {
			FrameBuffer::unbind();
			//std::cout << "Unbound framebuffer " << FrameBuffer::getBound() << std::endl;
		}

		// We choose the correct sky color,
		// there is a sky color for each rendererType
		// stored in the scene.
		// We clear color & depth buffer
		auto skyColor = m_skyColors[rendererType];
		zglCheckOpenGL();
		glClearColor(skyColor.x, skyColor.y, skyColor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		zglCheckOpenGL();

		// We render each element of the scene.
		// Each entity will be rendered with
		// it's given renderer for the current
		// rendererType choosed for this
		// rendering of the scene.
		for(auto& p_entity : m_entities)
		{
			Renderer& renderer = dynamic_cast<Renderer&>(p_entity->template getAttachment<Renderer>(rendererType));
			renderer.render(*this, camera, *p_entity.get());
		}

	}
} // End namespace zgl
