/**
 * @author: Corentin Asso
 * @date: 2025-02-24
 * @brief: Header for class 'zerogl.Light'.
 */

#ifndef H_ZGL_ZEROGL_LIGHT
#define H_ZGL_ZEROGL_LIGHT

// Includes
#include "zerogl/ZeroGL.hpp"
#include "zerogl/Camera.hpp"
// End includes

namespace zgl
{
	/**
	 * @author: Corentin Asso
	 * @date: 2025-02-24
	 * @brief: Light in a scene.
	 */
	class Light : public Camera
	{
	private:
		glm::vec3 m_lightColor;
	protected:
	public:
		/** Light color */
		inline auto getLightColor() const { return m_lightColor; }

		/** Light direction is entity front vector */
		inline auto getLightDirection() const { return -this->getBackVector(); }
		//inline auto getShadownMap() { return m_; }
		
	}; // End class Light

} // End namespace zgl

// Import template file.
#include "zerogl/Light.tcc"

#endif // H_ZGL_ZEROGL_LIGHT
