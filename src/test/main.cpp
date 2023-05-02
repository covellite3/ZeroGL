#include <iostream>
#include <cmath>

#include "zerogl/ZeroGL.hpp"
#include "zerogl/Math.hpp"
#include "zerogl/curve/BezierCurve.hpp"
#include "zerogl/surface/BezierSurface.hpp"

void showBar(unsigned char width, float percent)
{
	for (float t = 0; t < width*percent; t += 1.0f/width)
		std::cout << "X";
	std::cout << std::endl;
}

char grey_to_acsii(float value)
{
	const size_t N = 8;
	const char l[N] = { '.', ':', '!', '/', 'M', '%', '#', '@' };
	size_t i = std::max(std::min((size_t)(value*N), (size_t)N), (size_t)0L);
	return l[i];
}

int main () {
	std::cout << "unit testing...";
	zgl::BezierCurve<glm::vec3>::unittest();
	zgl::Math::unittest();
	std::cout << "done" << std::endl;

	/*int n = 6;
	for (int i = 0; i <= n; i += 1) {
		std::cout << "i:" << i << std::endl;
		for (float t = 0; t < 1.1f; t += 0.1f) {
			auto value = zgl::bernsteinPolynomial(n, i, t);
			showBar(10, value);
		}
		std::cout << std::endl;
	}*/

	/*zgl::BezierCurve<glm::vec2> bezier;
	bezier.addControlPoint(glm::vec2(0.0f, 0.0f));
	bezier.addControlPoint(glm::vec2(0.0f, 1.0f));
	bezier.addControlPoint(glm::vec2(0.2f, 0.4f));
	bezier.addControlPoint(glm::vec2(0.0f, 1.0f));
	std::cout << "x;y" << std::endl;
	for (float t = 0; t < 1.1f; t += 0.001f) {
		auto p = bezier(t);
		//showBar(10, p.y);
		std::cout << p.x << ";" << p.y << std::endl;
	}
	std::cout << std::endl;
	*/

	zgl::BezierSurface<glm::vec3> bezierSurface(3, 3);
	bezierSurface.setControlPoint(0, 0, glm::vec3(0, 0, 1));
	bezierSurface.setControlPoint(0, 1, glm::vec3(0, 1, 0));
	bezierSurface.setControlPoint(0, 2, glm::vec3(0, 2, 1));
	bezierSurface.setControlPoint(1, 0, glm::vec3(1, 0, 0));
	bezierSurface.setControlPoint(1, 1, glm::vec3(1, 1, 0));
	bezierSurface.setControlPoint(1, 2, glm::vec3(1, 2, 0));
	bezierSurface.setControlPoint(2, 0, glm::vec3(2, 0, 1));
	bezierSurface.setControlPoint(2, 1, glm::vec3(2, 1, 0));
	bezierSurface.setControlPoint(2, 2, glm::vec3(2, 2, 1));

	for (float i = 0; i <= 1.0f; i += 0.05f) {
		for (float j = 0; j <= 1.0f; j += 0.05f) {
			auto value = bezierSurface(i, j);
			std::cout << grey_to_acsii(value.z) << " ";
		}
		std::cout << std::endl;
	}


	return 0;
}
