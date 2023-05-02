#include <iostream>
#include <fstream>
#include <string>

#include "zerogl/ZeroGL.hpp"
#include "zerogl/mesh/CubeMesh.hpp"
#include "zerogl/Model.hpp"

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace zgl;

std::string vertexShaderSource, fragmentShaderSource;

CubeMesh cubemesh(true);
Model model;
ShaderProgram shaderProgram;
size_t width = 0, height = 0;

void readFile(std::stringstream& ss, const std::string& filepath) {
	char buffer[256];
	std::ifstream ifs;
	ifs.open(filepath, std::ios::in);
       	while (!ifs.eof()) {
		ifs.read(buffer, sizeof(buffer)-1);
		auto count =  ifs.gcount();
		buffer[count] = '\0';
		ss << buffer;
	}
	ifs.close();
}

inline void init ()
{
	std::stringstream ss;
	readFile(ss, "assets/lib/std/basicVertexShader.glsl");
	vertexShaderSource = ss.str();
	ss.str(std::string());
	std::cout << vertexShaderSource << std::endl;

	readFile(ss, "assets/lib/std/basicFragmentShader.glsl");
	fragmentShaderSource = ss.str();
	ss.str(std::string());
	std::cout << fragmentShaderSource << std::endl;

	zglCheckOpenGL();
	std::cout << "Shader" << std::endl;
	shaderProgram.init();
	shaderProgram.attachVertexShader(vertexShaderSource.c_str());
	shaderProgram.attachFragmentShader(fragmentShaderSource.c_str());
	if (!shaderProgram.compile()) {
		shaderProgram.showErrors(std::cout);
		exit(EXIT_FAILURE);
	}
	if (!shaderProgram.link()) {
		shaderProgram.showErrors(std::cout);
		exit(EXIT_FAILURE);
	}

	std::cout << "Model" << std::endl;
	model.init(cubemesh);

	std::cout << "OpenGL's options." << std::endl;
	glEnable(GL_DEPTH_TEST);  
	zglCheckOpenGL();
}

float foo = 0;
inline void pipeline ()
{
	zglCheckOpenGL();
	glClearColor(0.5f, 0.5f, 0.75f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0f), glm::radians(foo*200), glm::vec3(1.5f, 0.0f, 1.0f));
	glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -4.0f-foo));

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

	model.render(shaderProgram, GL_TRIANGLES);
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
