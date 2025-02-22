#include <iostream>
#include <fstream>
#include <string>

#include "zerogl/ZeroGL.hpp"
#include "zerogl/Model.hpp"
#include "zerogl/Mesh.hpp"
#include "zerogl/loader/Loader3D.hpp"

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace zgl;

sf::Window window;
ShaderProgram shaderProgram;
Mesh mesh;
int width = 0, height = 0;

void init()
{
	std::cout << "[MAIN] Init" << std::endl;
	// Setting context
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antiAliasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	// Create windows
	window = sf::Window(
		sf::VideoMode(sf::Vector2u(800, 600)),
		sf::String("ZeroGL's example program using SFML."),
		(sf::State)sf::Style::Default,
		settings
	);
	window.setVerticalSyncEnabled(true);

	// Show what setting context actually did.
	settings = window.getSettings();
	std::cout << "depth bits:" << settings.depthBits << std::endl;
	std::cout << "stencil bits:" << settings.stencilBits << std::endl;
	std::cout << "antialiasing level:" << settings.antiAliasingLevel << std::endl;
	std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;

	// Opengl's options
	glewInit();
	glEnable(GL_DEBUG_OUTPUT);
	
	glEnable(GL_DEPTH_TEST);
	zglCheckOpenGL();

	// Shader
	shaderProgram.init();
	shaderProgram.loadFromFile(GL_VERTEX_SHADER, "assets/lib/std/basicVertexShader.glsl");
	shaderProgram.loadFromFile(GL_FRAGMENT_SHADER, "assets/lib/std/basicFragmentShader.glsl");
	zglCheckOpenGL();
	if (!shaderProgram.compile()) {
		shaderProgram.showErrors(std::cout);
		exit(EXIT_FAILURE);
	}
	if (!shaderProgram.link()) {
		shaderProgram.showErrors(std::cout);
		exit(EXIT_FAILURE);
	}

	std::cout << "[MAIN] Done init" << std::endl;
}

float foo = 0;
inline void pipeline ()
{
	zglCheckOpenGL();
	glClearColor(0.5f, 0.5f*std::cos(foo), 0.75f*std::sin(foo), 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0f), glm::radians(200.f*foo), glm::vec3(1.5f, 0.0f, 1.0f));
	glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -4.0f*foo));

	glm::mat4 modelMat = translateMat * rotateMat * scaleMat;
	glm::mat4 viewMat(1.0f);
	glm::mat4 projMat = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);

	auto loc = shaderProgram.getUniformLocation("u_modelMat");
	shaderProgram.setUniform(loc, modelMat);

	loc = shaderProgram.getUniformLocation("u_viewMat");
	shaderProgram.setUniform(loc, viewMat);

	loc = shaderProgram.getUniformLocation("u_projMat");
	shaderProgram.setUniform(loc, projMat);

	loc = shaderProgram.getUniformLocation("u_lightVector");
	glm::vec3 lightVector = glm::normalize(glm::vec3(1.0f, -1.0f, -1.0f));
	shaderProgram.setUniform(loc, lightVector);

	mesh.draw(shaderProgram);
	zglCheckOpenGL();
	


	foo += 0.01f;
}

void loop()
{
	// Application loop.
	while (window.isOpen())
	{
		// Pop an event from stack.
		while (const std::optional event = window.pollEvent())
		{
			if(event->is<sf::Event::Closed>())
			{
				std::cout << "[EVENT] Closed window" << std::endl;
				window.close();
			}
			if (const auto* resized = event->getIf<sf::Event::Resized>())
			{
				width = resized->size.x;
				height = resized->size.y;
				glViewport(0, 0, width, height);
			}
			if(event->is<sf::Event::KeyPressed>())
			{
				if(event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
				{
					std::cout << "[EVENT] Pressed ESC" << std::endl;
					window.close();
				}
			}
		}
		pipeline();
		window.display();
	}
}

int main ()
{
	init();
	mesh = Loader3D::loadTriangle();
	loop();
	return 0;
}
