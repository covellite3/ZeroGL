/**
 * @author: Asso Corentin
 * @date: 2025-02-21
 * @brief: Header for class 'zerogl.Model'.
 */

#ifndef H_ZGL_ZEROGL_MODEL
#define H_ZGL_ZEROGL_MODEL

// Includes
#include "zerogl/Entity.hpp"
#include "zerogl/Mesh.hpp"
#include "zerogl/Material.hpp"
#include "zerogl/Skeleton.hpp"
#include "zerogl/opengl/FrameBuffer.hpp"
#include "zerogl/opengl/Texture.hpp"

#include <memory>
// End includes

namespace zgl
{
	/**
	 * @author: Asso Corentin
	 * @date: 2025-02-21
	 * @brief: TODO.
	 */
	class Model : public Component
	{
	private:
		std::shared_ptr<Mesh> m_mesh;
		std::shared_ptr<Texture> m_texture;
		std::shared_ptr<FrameBuffer> m_framebuffer;
		//Material m_material;
		//Skeleton m_skeleton;
	protected:
	public:
		inline Model(): m_mesh(nullptr), m_texture(nullptr) {}

		inline auto& getMesh() { return *m_mesh.get(); }
		inline void setMesh(std::shared_ptr<Mesh>& t_mesh) { m_mesh = t_mesh; }


		inline auto getTexture() { return m_texture.get(); }
		inline void setTexture(std::shared_ptr<Texture> t_texture) { m_texture = t_texture; }
		
		inline auto getFramebuffer() { return m_framebuffer.get(); }
		inline void setFramebuffer(std::shared_ptr<FrameBuffer> t_framebuffer) { m_framebuffer = t_framebuffer; }
		

		//Model(Mesh&& t_mesh, Material&& t_material, Skeleton&& m_Skeleton);
	}; // End class Model

} // End namespace zgl

// Import template file.
#include "zerogl/Model.tcc"

#endif // H_ZGL_ZEROGL_MODEL
