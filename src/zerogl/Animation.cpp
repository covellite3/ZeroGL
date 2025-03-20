/**
 * @author: Corentin Asso
 * @date: 2025-03-19
 * @brief: C++ file for class 'zerogl.Animation'.
 */
 
// Import header file.
#include "zerogl/Animation.hpp"

namespace zgl
{

	Animation::AnimationFrame Animation::operator[](const TimeStamp& atTime) const {
		if (m_keyFrames.empty()) {
			assert(false);
			return AnimationFrame();
		}

		const KeyFrame *prevKeyFrame, *nextKeyFrame;
		float k = 0.0f;

		for (size_t i = 0; i < m_keyFrames.size() - 1; ++i) {
			prevKeyFrame = &m_keyFrames[i];
			nextKeyFrame = &m_keyFrames[i + 1];

			if (atTime >= std::get<0>(*prevKeyFrame) && atTime <= std::get<0>(*nextKeyFrame)) {
				TimeStamp frameDuration = std::get<0>(*nextKeyFrame) - std::get<0>(*prevKeyFrame);
				k = (atTime - std::get<0>(*prevKeyFrame)).asSeconds() / frameDuration.asSeconds();
				break;
			}
		}

		if (atTime < std::get<0>(m_keyFrames[0])) {
			return std::get<1>(m_keyFrames[0]);
		}

		if (atTime > std::get<0>(m_keyFrames.back())) {
			return std::get<1>(m_keyFrames.back());
		}

		const AnimationFrame& prevFrame = std::get<1>(*prevKeyFrame);
		const AnimationFrame& nextFrame = std::get<1>(*nextKeyFrame);

		AnimationFrame interpolatedFrame = prevFrame.interpolate(nextFrame, k);

		return interpolatedFrame;
	}
} // End namespace zgl
