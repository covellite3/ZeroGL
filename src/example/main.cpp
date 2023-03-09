#include <iostream>
#include <string>

#include "zerogl/ZeroGL.hpp"
#include "zerogl/mesh/CubeMesh.hpp"

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace zgl;

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

const GLchar* vertexShaderSource =
"#version 330 core\n\
layout (location = 0) in vec3 aPos;\n\
\n\
uniform mat4 u_modelViewProjMat;\n\
\n\
void main()\n\
{\n\
    gl_Position = u_modelViewProjMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n\
}";

const GLchar* fragmentShaderSource =
"#version 330 core\n\
out vec4 FragColor;\n\
\n\
void main()\n\
{\n\
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n\
} ";

CubeMesh cubemesh(false);
ArrayBuffer vbo;
VertexArray vao;
ShaderProgram shaderProgram;
size_t width = 0, height = 0;

inline void init ()
{
	zglCheckOpenGL();
	std::cout << "Shader" << std::endl;
	shaderProgram.init();
	shaderProgram.attachVertexShader(vertexShaderSource);
	shaderProgram.attachFragmentShader(fragmentShaderSource);
	if (!shaderProgram.compile()) {
		shaderProgram.showErrors(std::cout);
		exit(EXIT_FAILURE);
	}
	if (!shaderProgram.link()) {
		shaderProgram.showErrors(std::cout);
		exit(EXIT_FAILURE);
	}

	std::cout << "VBO" << std::endl;
	vbo.init();
	vbo.send(cubemesh.getNumberOfVerticies()*sizeof(glm::vec3), cubemesh.get3DPositions(), GL_STATIC_DRAW);
	zglCheckOpenGL();

	std::cout << "VAO" << std::endl;
	vao.init();
	vao.enableAttribPointer(0);
	vao.setAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0, vbo);
}

float foo = 0;
inline void pipeline ()
{
	zglCheckOpenGL();
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	auto scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	auto rotateMat = glm::rotate(glm::mat4(1.0f), glm::radians(foo*200), glm::vec3(1.5f, 0.0f, 1.0f));
	auto translateMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -4.0f-foo));

	auto modelMat = translateMat * rotateMat * scaleMat;
	auto viewMat(1.0f);
	auto projMat = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);

	auto modelViewProjMat = projMat * viewMat * modelMat;


	auto location = shaderProgram.getUniformLocation("u_modelViewProjMat");
	shaderProgram.setUniform(location, modelViewProjMat);
	shaderProgram.draw(vao, GL_TRIANGLES, 0, cubemesh.getLenght());
	foo += 0.01f;
}

int main ()
{
	// Setting context
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	// Create windows
	sf::Window window(
		sf::VideoMode(800, 600),
		"ZeroGL's example program using SFML.",
		sf::Style::Default,
		settings
	);
	window.setVerticalSyncEnabled(true);

	// Show what setting context actually did.
	settings = window.getSettings();
	std::cout << "depth bits:" << settings.depthBits << std::endl;
	std::cout << "stencil bits:" << settings.stencilBits << std::endl;
	std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
	std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;

	glewInit();

	init();

	// Application loop.
	while (window.isOpen())
	{
		// Pop an event from stack.
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
				case sf::Event::Closed:
				window.close();
				break;

				case sf::Event::Resized:
				glViewport(0, 0, event.size.width, event.size.height);
				width = event.size.width;
				height = event.size.width;
				break;
				
				case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) window.close();
				break;

				case sf::Event::GainedFocus: break;
				case sf::Event::LostFocus: break;
				case sf::Event::TextEntered: break;
				case sf::Event::KeyReleased: break;
				case sf::Event::MouseWheelMoved: break;
				case sf::Event::MouseWheelScrolled: break;
				case sf::Event::MouseButtonPressed: break;
				case sf::Event::MouseButtonReleased: break;
				case sf::Event::MouseMoved: break;
				case sf::Event::MouseEntered: break;
				case sf::Event::MouseLeft: break;
				case sf::Event::JoystickButtonPressed: break;
				case sf::Event::JoystickButtonReleased: break;
				case sf::Event::JoystickMoved: break;
				case sf::Event::JoystickConnected: break;
				case sf::Event::JoystickDisconnected: break;
				case sf::Event::TouchBegan: break;
				case sf::Event::TouchEnded: break;
				case sf::Event::TouchMoved: break;
				case sf::Event::SensorChanged: break;
				case sf::Event::Count: break;
			}
		}
		pipeline();
		window.display();
	}

	return 0;
}
