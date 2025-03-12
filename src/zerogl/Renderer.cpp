/**
 * @author: Corentin Asso
 * @date: 2025-03-08
 * @brief: C++ file for class 'zerogl.Renderer'.
 */
 
// Import header file.
#include "zerogl/Renderer.hpp"
 
namespace zgl
{

	void printMatrix(const glm::mat4 &matrix) {
		for (int row = 0; row < 4; ++row) {
			for (int col = 0; col < 4; ++col) {
				std::cout << matrix[row][col] << " ";
			}
			std::cout << std::endl;
		}
	}

	void Renderer::render(Scene& scene, Camera& camera, Entity& entity)
	{
		(void)scene;
		Model& model = entity.getAttachment<Model>(Component::Key::MODEL);

		zglCheckOpenGL();

		glm::mat4 modelMat = entity.getModelMatrix();
		glm::mat4 viewMat = camera.getViewMatrix();
		glm::mat4 projMat = camera.getProjectionMatrix();

		auto loc = m_shaderProgram->getUniformLocation("u_modelMat");
		m_shaderProgram->setUniformMatrix(loc, modelMat);

		loc = m_shaderProgram->getUniformLocation("u_viewMat");
		m_shaderProgram->setUniformMatrix(loc, viewMat);

		loc = m_shaderProgram->getUniformLocation("u_projMat");
		m_shaderProgram->setUniformMatrix(loc, projMat);

		loc = m_shaderProgram->getUniformLocation("u_pointLight");
		glm::vec3 pointLight = glm::vec3(-10, 5, 10);
		m_shaderProgram->setUniformMatrix(loc, pointLight);

		loc = m_shaderProgram->getUniformLocation("u_tex");
		if(model.getTexture() != nullptr)
		{
			std::cout << "[Renderer ?] Model as texture: " << model.getTexture()->getHandle() << std::endl;
			m_shaderProgram->setUniformTexture(loc, model.getTexture()->getHandle(), 0);
		}
		else if(model.getFramebuffer() != nullptr)
		{
			std::cout << "[Renderer ?] Model as framebuffer: " << model.getFramebuffer()->getTextureHandle() << std::endl;
			m_shaderProgram->setUniformTexture(loc, model.getFramebuffer()->getTextureHandle(), 0);
		}
		else std::runtime_error("Missing texture or framebuffer");

		GLint boundTexture;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &boundTexture);
		zglCheckOpenGL();
		std::cout << "[Renderer ?] Bounded texture before drawing: " << boundTexture << std::endl;
		
		model.getMesh().draw(*m_shaderProgram.get());
	}

} // End namespace zgl
