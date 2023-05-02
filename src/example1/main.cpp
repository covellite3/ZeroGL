#include <iostream>
#include <fstream>
#include <string>

#include "zerogl/ZeroGL.hpp"
#include "zerogl/mesh/CubeMesh.hpp"
#include "zerogl/mesh/CurveMesh.hpp"
#include "zerogl/mesh/SurfaceMesh.hpp"
#include "zerogl/curve/BezierCurve.hpp"
#include "zerogl/surface/BezierSurface.hpp"
#include "zerogl/Model.hpp"
#include "zerogl/ModelCurve.hpp"

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>

using namespace zgl;

sf::Texture tex;
Model cubeModel, bezierSurfaceModel;
ModelCurve bezierModel, lightvectorModel;
ShaderProgram shaderCurve, shaderModel;
size_t width = 0, height = 0;
glm::vec3 lightVector = glm::normalize(glm::vec3(0, -1, -1) - glm::vec3(0.0f, 0.0f, 0.0f));

sf::Clock chrono;
float spin = 0, angle = 0, speed = 3.14f/100.0f;


// PARAMETERS
size_t nsegments = 4;

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

void loadShader(ShaderProgram& shaderProgram, std::string vertexpath, std::string fragmentpath)
{
	std::string vertexShaderSource, fragmentShaderSource;

	std::stringstream ss;
	readFile(ss, vertexpath);
	vertexShaderSource = ss.str();
	ss.str(std::string());

	readFile(ss, fragmentpath);
	fragmentShaderSource = ss.str();
	ss.str(std::string());

	zglCheckOpenGL();
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
}

void createBezierCurve(ModelCurve& model) {
	BezierCurve<glm::vec3> bezier;
	bezier.addControlPoint(glm::vec3( 0.0f, 0.0f, 0.0f));
	bezier.addControlPoint(glm::vec3( 0.0f, 1.0f, 1.0f));
	bezier.addControlPoint(glm::vec3( 1.0f, 1.0f,-1.0f));
	bezier.addControlPoint(glm::vec3( 1.0f, 0.0f, 0.0f));
	CurveMesh<glm::vec3, BezierCurve<glm::vec3>> bezierMesh(nsegments, bezier);
	model.init(bezierMesh);
}

void createBezierSurface(Model& model) {
	zgl::BezierSurface<glm::vec3> bezierSurface(3, 3);
	bezierSurface.setControlPoint(0, 0, glm::vec3(-0.5f, -0.5f, 1));
	bezierSurface.setControlPoint(0, 1, glm::vec3(-0.5f,  0.0f, 0));
	bezierSurface.setControlPoint(0, 2, glm::vec3(-0.5f,  0.5f, 1));
	bezierSurface.setControlPoint(1, 0, glm::vec3( 0.0f, -0.5f, 0));
	bezierSurface.setControlPoint(1, 1, glm::vec3( 0.0f,  0.0f, 0));
	bezierSurface.setControlPoint(1, 2, glm::vec3( 0.0f,  0.5f, 0));
	bezierSurface.setControlPoint(2, 0, glm::vec3( 0.5f, -0.5f, 1));
	bezierSurface.setControlPoint(2, 1, glm::vec3( 0.5f,  0.0f, 0));
	bezierSurface.setControlPoint(2, 2, glm::vec3( 0.5f,  0.5f, 1));
	SurfaceMesh surfaceMesh(nsegments, nsegments, bezierSurface);
	model.init(surfaceMesh);
}

void createCube(Model& model) {
	CubeMesh cubeMesh(true);
	model.init(cubeMesh);
}

void createModels ()
{
	std::cout << "Bezier curve" << std::endl;
	createBezierCurve(bezierModel);

	std::cout << "Bezier surface" << std::endl;
	createBezierSurface(bezierSurfaceModel);

	//std::cout << "Cube" << std::endl;
	//createCube(cubeModel);
}

inline void init ()
{

	std::cout << "Shader" << std::endl;
	loadShader(shaderCurve, "assets/lib/std/curveVertexShader.glsl", "assets/lib/std/curveFragmentShader.glsl");
	loadShader(shaderModel, "assets/lib/std/basicVertexShader.glsl", "assets/lib/std/basicFragmentShader.glsl");

	createModels();

	if (!tex.loadFromFile("assets/tex/smiley.png")) {
		std::cout << "Unable to load texture from file." << std::endl;
	}

	std::cout << "OpenGL's options." << std::endl;
	glEnable(GL_DEPTH_TEST);  
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glLineWidth(3);
	glPointSize(9);
	zglCheckOpenGL();
}

inline void pipeline ()
{
	zglCheckOpenGL();
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Position Model
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -4.0f));
	glm::mat4 modelMat = translateMat * rotateMat * scaleMat;

	// Camera
	glm::mat4 viewMat(1.0f);
	glm::mat4 projMat = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);

	// Render bezier curve
	auto loc = shaderCurve.getUniformLocation("u_modelMat");
	shaderCurve.setUniform(loc, modelMat);

	loc = shaderCurve.getUniformLocation("u_viewMat");
	shaderCurve.setUniform(loc, viewMat);

	loc = shaderCurve.getUniformLocation("u_projMat");
	shaderCurve.setUniform(loc, projMat);

	bezierModel.render(shaderCurve, GL_LINE_STRIP);
	
	// Render bezier surface
	loc = shaderModel.getUniformLocation("u_modelMat");
	shaderModel.setUniform(loc, modelMat);

	loc = shaderModel.getUniformLocation("u_viewMat");
	shaderModel.setUniform(loc, viewMat);

	loc = shaderModel.getUniformLocation("u_projMat");
	shaderModel.setUniform(loc, projMat);

	loc = shaderModel.getUniformLocation("u_lightVector");
	shaderModel.setUniform(loc, lightVector);

	sf::Texture::bind(&tex);

	bezierSurfaceModel.render(shaderModel, GL_TRIANGLES);

	sf::Texture::bind(NULL);
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
		chrono.restart();
		// Pop an event from stack.
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
				case sf::Event::Closed:
				window.close();
				break;

				case sf::Event::Resized:
				width = event.size.width;
				height = event.size.height;
				glViewport(0, 0, width, height);
				std::cout << "SFML EVENT : resize window " << width << " " << height << std::endl;
				break;
				
				case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) window.close();
				if (event.key.code == sf::Keyboard::P) {
					++nsegments;
					createModels();
				}
				if (event.key.code == sf::Keyboard::M) {
					if (nsegments > 1) {
						--nsegments;
						createModels();
					}
				}
				if (event.key.code == sf::Keyboard::H) {
					spin = -1;
				}
				if (event.key.code == sf::Keyboard::L) {
					spin = 1;
				}
				break;

				case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::H) {
					spin = 0;
				}
				if (event.key.code == sf::Keyboard::L) {
					spin = 0;
				}
				break;

				case sf::Event::GainedFocus: break;
				case sf::Event::LostFocus: break;
				case sf::Event::TextEntered: break;
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
		sf::Time elapsed = chrono.getElapsedTime();
		angle += spin*speed*elapsed.asMilliseconds();
	}

	return 0;
}
