/**
 * @author: Corentin Asso
 * @date: 2025-03-08
 * @brief: C++ file for class 'zerogl.Renderer'.
 */
 
// Import header file.
#include "zerogl/Renderer.hpp"
#include "zerogl/Animation.hpp"
 
namespace zgl
{
	void Renderer::render(Scene& scene, Camera& camera, Entity& entity, const sf::Time& time)
	{
		zglCheckOpenGL();

		Model& model = entity.getAttachment<Model>(Component::Key::MODEL);

		// Animation
		if(entity.hasAttachment(Component::Key::ANIMATION) && entity.hasAttachment(Component::Key::ANIMATION)) {
			Skeleton& skeleton = entity.getAttachment<Skeleton>(Component::Key::SKELETON);
			Animation& animation = entity.getAttachment<Animation>(Component::Key::ANIMATION);

			Pose pose = animation[time];
			skeleton.hierarchize(pose);
			assert(pose.getTransformationSpace() == Pose::TransformationSpace::HIERARCHICAL);

			std::cout << "Has skeleton or animation with " << pose.getNbrOfBones() << std::endl;
			for(size_t iBone = 0; iBone < pose.getNbrOfBones(); ++iBone) {
				auto loc = m_shaderProgram->getUniformLocation(("u_bones["+std::to_string(iBone)+"]").c_str());
				m_shaderProgram->setUniformMatrix(loc, pose[iBone].getMatrix());
			}
		}


		// Model View Perpective
		glm::mat4 modelMat = entity.getModelMatrix();
		glm::mat4 viewMat = camera.getViewMatrix();
		glm::mat4 projMat = camera.getProjectionMatrix();

		auto loc = m_shaderProgram->getUniformLocation("u_modelMat");
		m_shaderProgram->setUniformMatrix(loc, modelMat);

		loc = m_shaderProgram->getUniformLocation("u_viewMat");
		m_shaderProgram->setUniformMatrix(loc, viewMat);

		loc = m_shaderProgram->getUniformLocation("u_projMat");
		m_shaderProgram->setUniformMatrix(loc, projMat);

		// Camera
		loc = m_shaderProgram->getUniformLocation("u_positionCamera");
		m_shaderProgram->setUniform(loc, camera.getPosition());

		// Light
		loc = m_shaderProgram->getUniformLocation("u_colorLight");
		m_shaderProgram->setUniform(loc, scene.getLight()->getLightColor());
		loc = m_shaderProgram->getUniformLocation("u_coordLight");
		m_shaderProgram->setUniform(loc, scene.getLight()->getPosition());
		loc = m_shaderProgram->getUniformLocation("u_directionLight");
		m_shaderProgram->setUniform(loc, -scene.getLight()->getDirection());
		loc = m_shaderProgram->getUniformLocation("u_zNearLight");
		m_shaderProgram->setUniform(loc, scene.getLight()->getNearPlane());
		loc = m_shaderProgram->getUniformLocation("u_zFarLight");
		m_shaderProgram->setUniform(loc, scene.getLight()->getFarPlane());
		loc = m_shaderProgram->getUniformLocation("u_lightProjMat");
		auto lightProjMat = scene.getLight()->getProjectionMatrix() * scene.getLight()->getViewMatrix();
		m_shaderProgram->setUniformMatrix(loc, lightProjMat);

		// Texture
		loc = m_shaderProgram->getUniformLocation("u_tex");
		if(model.getTexture() != nullptr)
		{
			//std::cout << "[Renderer ? ] Model as texture: " << model.getTexture()->getHandle() << std::endl;
			m_shaderProgram->setUniformTexture(loc, model.getTexture()->getHandle(), 0);
		}
		else if(model.getFramebuffer() != nullptr)
		{
			//std::cout << "[Renderer ? ] Model as framebuffer: " << model.getFramebuffer()->getTextureHandle() << std::endl;
			m_shaderProgram->setUniformTexture(loc, model.getFramebuffer()->getTextureHandle(), 0);
		}
		else std::runtime_error("Missing texture or framebuffer");

		// Shadowmap
		loc = m_shaderProgram->getUniformLocation("u_shadowmap");
		m_shaderProgram->setUniformTexture(loc, scene.getLight()->getFramebuffer()->getDepthStencilHandle(), 1);

		// Render mesh
		//std::cout << "[Renderer ? ] Draw mesh to FBO " << FrameBuffer::getBound() << std::endl;;
		model.getMesh().draw(*m_shaderProgram.get());
	}


	std::shared_ptr<Renderer> Renderer::make(const std::string& vertexName, const std::string& fragmentName)
	{
		auto shaderProgram = ShaderProgram::make(vertexName, fragmentName);
		auto renderer = std::make_shared<Renderer>();
		renderer->setShaderProgram(shaderProgram);
		return renderer;
	}

} // End namespace zgl
