#include "Engine.h"

#include "EngineManager/WindowManager.h"
#include "EngineManager/InputManager.h"
#include "EngineManager/ResourceManager.h"
#include "Objects/Triangle.h"	
#include "Objects/Shader.h"
#include "Objects/Cube.h"
#include "Objects/Rectangle.h"
#include <iostream>

Engine::Engine()
{
	m_window = nullptr;
	m_cube = nullptr;
}

Engine::~Engine()
{
	cleanup();
}

void Engine::init()
{
	// load glfw
	{
		if (!glfwInit()) {
			std::cerr << "Failed to initialize GLFW" << std::endl;
			return;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}


	// init window
	{
		m_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_TITLE, NULL, NULL);
		if (!m_window) {
			std::cerr << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(m_window);
		WINDOW_MANAGER->setWindow(m_window);
	}

	// load glad
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cerr << "Failed to initialize GLAD" << std::endl;
			return;
		}
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	// set viewport
	{
		glViewport(0, 0, 800, 600);
		glfwSetFramebufferSizeCallback(m_window, Engine::framebuffer_size_callback);
	}

	// init cube object
	{
		m_cube = new Cube();
		m_cube->setShader(new Shader("Source/Shaders/cube.vert", "Source/Shaders/cube.frag"));
		m_cube->setTexture(DATA->loadTexture("Resource/Texture/container.jpg"));
	}

}

void Engine::run()
{
	while (!glfwWindowShouldClose(m_window)) {
		INPUT_MANAGER->processInput(m_window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_cube->draw();

		WINDOW_MANAGER->render();
		INPUT_MANAGER->handleEvent();
	}
}

void Engine::cleanup()
{
	glfwTerminate();
}
