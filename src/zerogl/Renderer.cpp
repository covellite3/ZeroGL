/**
 * @author: Corentin Asso
 * @date: 2025-03-08
 * @brief: C++ file for class 'zerogl.Renderer'.
 */
 
// Import header file.
#include "zerogl/Renderer.hpp"
 
namespace zgl
{
	void Renderer::render(Scene& scene, Camera& camera, Entity& entity)
	{
		(void)scene;
		Model& model = entity.getAttachment<Model>(Component::Key::MODEL);

		zglCheckOpenGL();

		glm::mat4 modelMat = entity.getModelMatrix();
		glm::mat4 viewMat = camera.getViewMatrix();
		glm::mat4 projMat = camera.getProjectionMatrix();

		// Model View Perpective

		auto loc = m_shaderProgram->getUniformLocation("u_modelMat");
		m_shaderProgram->setUniformMatrix(loc, modelMat);

		loc = m_shaderProgram->getUniformLocation("u_viewMat");
		m_shaderProgram->setUniformMatrix(loc, viewMat);

		loc = m_shaderProgram->getUniformLocation("u_projMat");
		m_shaderProgram->setUniformMatrix(loc, projMat);

		// Camera
		loc = m_shaderProgram->getUniformLocation("u_positionCamera");
		m_shaderProgram->setUniformMatrix(loc, camera.getPosition());

		/*loc = m_shaderProgram->getUniformLocation("u_directionCamera");
		m_shaderProgram->setUniformMatrix(loc, -camera.getDirection());*/



		// Light
		loc = m_shaderProgram->getUniformLocation("u_colorLight");
		m_shaderProgram->setUniformMatrix(loc, scene.getLight()->getLightColor());
		loc = m_shaderProgram->getUniformLocation("u_coordLight");
		m_shaderProgram->setUniformMatrix(loc, scene.getLight()->getPosition());
		loc = m_shaderProgram->getUniformLocation("u_directionLight");
		m_shaderProgram->setUniformMatrix(loc, -scene.getLight()->getDirection());

		// Texture

		loc = m_shaderProgram->getUniformLocation("u_tex");
		if(model.getTexture() != nullptr)
		{
			//std::cout << "[Renderer ?] Model as texture: " << model.getTexture()->getHandle() << std::endl;
			m_shaderProgram->setUniformTexture(loc, model.getTexture()->getHandle(), 0);
		}
		else if(model.getFramebuffer() != nullptr)
		{
			//std::cout << "[Renderer ?] Model as framebuffer: " << model.getFramebuffer()->getTextureHandle() << std::endl;
			m_shaderProgram->setUniformTexture(loc, model.getFramebuffer()->getTextureHandle(), 0);
		}
		else std::runtime_error("Missing texture or framebuffer");

		// Render mesh
		
		model.getMesh().draw(*m_shaderProgram.get());
	}


	std::shared_ptr<Renderer> Renderer::make(const std::string& name)
	{
		auto shaderProgram = ShaderProgram::make(name);
		auto renderer = std::make_shared<Renderer>();
		renderer->setShaderProgram(shaderProgram);
		return renderer;
	}

} // End namespace zgl
