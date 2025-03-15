#include "zerogl/ZeroGL.hpp"
#include "zerogl/Model.hpp"
#include "zerogl/Mesh.hpp"
#include "zerogl/Renderer.hpp"
#include "zerogl/Camera.hpp"
#include "zerogl/Light.hpp"
#include "zerogl/opengl/Texture.hpp"
#include "zerogl/loader/Loader3D.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
//#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace zgl;

sf::Window window;
Scene scene;
std::shared_ptr<Light> light;
std::shared_ptr<Camera> camera;

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
	if (glewInit() != GLEW_OK) {
		std::cerr << "GLEW initialization failed!" << std::endl;
		exit(EXIT_FAILURE);
	}

	zglCheckOpenGL();
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); 
	glCullFace(GL_FRONT);
	zglCheckOpenGL();

	//////
	//////
	//////

	// Assets
	auto shadowmapRenderer = Renderer::make("shadowmap");
	auto basicRenderer = Renderer::make("basic");
	auto tex1 = zgl::Texture::make("dirt");
	auto tex2 = zgl::Texture::make("tex2");

	// Camera
	std::cout << "Camera" << std::endl;
	camera = std::make_shared<Camera>();
	camera->setPosition(glm::vec3(0,0,10));

	// Light
	std::cout << "Light" << std::endl;
	light = std::make_shared<Light>();
	light->setPosition(glm::vec3(25, 50, 40));
	light->lookAt(glm::vec3(0,0,0), glm::vec3(0,1,0));

	light->setPerspective(glm::radians(45.0f), 1.0, 0.1f, 1000.0f);
	light->setFramebuffer(std::make_shared<FrameBuffer>());
	light->getFramebuffer()->init(0, 0, 2048, 2048);
	light->getFramebuffer()->attachTexture(); // TODO remove color attachment for shadowmap
	light->getFramebuffer()->attachDepthStencil();

	// Entities
	std::cout << "Entity" << std::endl;

	auto mesh1 = std::make_shared<zgl::Mesh>(std::move(Loader3D::loadCube()));
	auto model1 = std::make_shared<Model>();
	model1->setMesh(mesh1);
	model1->setTexture(tex1);
	auto component1 = std::static_pointer_cast<zgl::Component>(model1);
	auto entity = std::make_shared<Entity>(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
	entity->attachComponent(Component::Key::MODEL, component1);
	entity->attachComponent(Component::Key::RENDERER_0, basicRenderer);
	entity->attachComponent(Component::Key::RENDERER_1, shadowmapRenderer);

	auto mesh2 = std::make_shared<zgl::Mesh>(std::move(Loader3D::loadCube()));
	auto model2 = std::make_shared<Model>();
	model2->setMesh(mesh2);
	model2->setTexture(tex2);
	auto component2 = std::static_pointer_cast<zgl::Component>(model2);
	auto ground = std::make_shared<Entity>(glm::vec3(0.0f, -4.0f, 0.0f), glm::vec3(15.0f, 1.f, 15.f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
	ground->attachComponent(Component::Key::MODEL, component2);
	ground->attachComponent(Component::Key::RENDERER_0, basicRenderer);
	ground->attachComponent(Component::Key::RENDERER_1, shadowmapRenderer);

	auto meshQuad = std::make_shared<zgl::Mesh>(std::move(Loader3D::loadQuad()));
	auto modelQuad = std::make_shared<Model>();
	modelQuad->setMesh(meshQuad);
	modelQuad->setFramebuffer(light->getFramebuffer());
	auto componentQuad = std::static_pointer_cast<zgl::Component>(modelQuad);
	auto screen = std::make_shared<Entity>(glm::vec3(0.0f, 1.5f, -2.0f), glm::vec3(3.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
	screen->attachComponent(Component::Key::MODEL, componentQuad);
	screen->attachComponent(Component::Key::RENDERER_0, basicRenderer);
	screen->attachComponent(Component::Key::RENDERER_1, shadowmapRenderer);

	auto meshCylinder = std::make_shared<zgl::Mesh>(std::move(Loader3D::loadAnimatedCylinder(100, 10, 2)));
	auto modelCylinder = std::make_shared<Model>();
	modelCylinder->setMesh(meshCylinder);
	modelCylinder->setTexture(tex1);
	auto componentCylinder = std::static_pointer_cast<zgl::Component>(modelCylinder);
	auto cylinder = std::make_shared<Entity>(glm::vec3(4.0f, -1.0f, 0.0f), glm::vec3(0.1f, 0.1f, 5.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
	cylinder->attachComponent(Component::Key::MODEL, componentCylinder);
	cylinder->attachComponent(Component::Key::RENDERER_0, basicRenderer);
	cylinder->attachComponent(Component::Key::RENDERER_1, shadowmapRenderer);



	// Scene
	std::cout << "Scene" << std::endl;
	scene.setSkyColor(Component::Key::RENDERER_0, glm::vec3(0.5f, 0.5f, 1.0f));
	scene.setSkyColor(Component::Key::RENDERER_1, glm::vec3(1.0f, 0.0f, 0.0f));
	scene.setLight(light);
	scene.add(entity);
	scene.add(ground);
	scene.add(screen);
	scene.add(cylinder);

	std::cout << "[MAIN] Done init" << std::endl;
}

void loop()
{
	float moveSpeed = 10.f;
	const float rotationSpeed = 10.f;
	sf::Clock clock;
	clock.start();
	float dt = 0;
	size_t iter_count = 0, previous_iter_count = 0;
	sf::Vector2i windowCenter, currentMousePosition;
	const float timeThreshold = 0.02f;
	// Application loop.
	while (window.isOpen())
	{
		if(clock.getElapsedTime().asSeconds() >= timeThreshold)
		{
			previous_iter_count = iter_count;
			iter_count = 0;
			dt = clock.restart().asSeconds();
						   
			// Rotate camera based on mouse movement.
			auto delta = currentMousePosition - windowCenter;
			camera->rotateDegreeAroundUpVector(-static_cast<float>(delta.x) * rotationSpeed * dt);
			camera->rotateDegreeAroundRightVector(-static_cast<float>(delta.y) * rotationSpeed * dt);

			// Reset mouse position to the center.
			sf::Mouse::setPosition(windowCenter, window);
			
		}
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
				auto width = resized->size.x;
				auto height = resized->size.y;
				std::cout << "[EVENT] Resized window " << width << "x" << height << std::endl;
				FrameBuffer::setWindowViewport(0, 0, width, height);
				camera->setPerspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 1000.0f);
				// Get the center of the window
				windowCenter = sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2);

			}
			if (event->is<sf::Event::MouseMoved>())
			{
				currentMousePosition = sf::Mouse::getPosition(window);

			}
			if(event->is<sf::Event::KeyPressed>())
			{
				if(event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
				{
					std::cout << "[EVENT] Pressed ESC" << std::endl;
					window.close();
				}

				if(event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Z)
				{
					camera->moveFoward(moveSpeed*dt*(1.0f/static_cast<float>(previous_iter_count)));
				}
				if(event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Q)
				{
					camera->moveLeftward(moveSpeed*dt*(1.0f/static_cast<float>(previous_iter_count)));
				}
				if(event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::S)
				{
					camera->moveBackward(moveSpeed*dt*(1.0f/static_cast<float>(previous_iter_count)));
				}
				if(event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::D)
				{
					camera->moveRightward(moveSpeed*dt*(1.0f/static_cast<float>(previous_iter_count)));
				}
				if(event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::E)
				{
					camera->moveUpward(moveSpeed*dt*(1.0f/static_cast<float>(previous_iter_count)));
				}
				if(event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::A)
				{
					camera->moveDownward(moveSpeed*dt*(1.0f/static_cast<float>(previous_iter_count)));
				}
			}
		}


		camera->lookAt(glm::vec3(0,-1,0), glm::vec3(0,1,0));
		//camera->setRotorOrientation(light->getRotorOrientation());
		//camera->setPosition(light->getPosition());


		// Render shadow map
		scene.render(Component::Key::RENDERER_1, *light); 

		// Render final scene
		scene.render(Component::Key::RENDERER_0, *camera);

		window.display();
		++iter_count;
	}
}

int main ()
{
	init();
	loop();
	return 0;
}
