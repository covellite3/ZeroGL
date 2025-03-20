/**
 * @author: Corentin Asso
 * @date: 2025-03-19
 * @brief: Header for class 'zerogl.Animation'.
 */

#ifndef H_ZGL_ZEROGL_ANIMATION
#define H_ZGL_ZEROGL_ANIMATION

// Includes
#include "zerogl/Component.hpp"
#include "zerogl/Pose.hpp"
#include <vector>
#include <tuple>
#include <SFML/System.hpp>
// End includes

namespace zgl
{
	/**
	 * @author: Corentin Asso
	 * @date: 2025-03-19
	 * @brief: Animation for skeleton, it's just a serie of poses at given time.
	 */
	class Animation : public Component
	{
	public:
		using TimeStamp = sf::Time;
		using AnimationFrame = Pose; // TOTO generalize animation to all kind of object
		using KeyFrame = std::tuple<TimeStamp, AnimationFrame>;
	private:
		std::vector<KeyFrame> m_keyFrames;

	protected:
	public:
		Animation() = default;
		inline Animation(std::initializer_list<KeyFrame> t_keyFrames) : m_keyFrames(t_keyFrames) {}
		Animation(const Animation&) = delete;
		Animation& operator=(const Animation&) = delete;
		Animation(Animation&& other) noexcept;
		Animation& operator=(Animation&& other) noexcept;
		AnimationFrame operator[](const TimeStamp& atTime) const;
		inline void addFrame(const TimeStamp& timeStamp, AnimationFrame& frame)
		{
			m_keyFrames.emplace_back(timeStamp, frame);
		}
	}; // End class Animation

} // End namespace zgl

// Import template file.
#include "zerogl/Animation.tcc"

#endif // H_ZGL_ZEROGL_ANIMATION
