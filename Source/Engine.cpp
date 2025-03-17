#include "Engine.h"

#include "EngineManager/WindowManager.h"
#include "EngineManager/InputManager.h"
#include <iostream>

Engine::Engine()
{
	m_window = nullptr;
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
		WINDOW_MANAGER->setWindow(m_window);
	}

	// load glad
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cerr << "Failed to initialize GLAD" << std::endl;
			return;
		}
	}

	// set viewport
	{
		glViewport(0, 0, 800, 600);
		glfwSetFramebufferSizeCallback(m_window, Engine::framebuffer_size_callback);
	}
}

void Engine::run()
{
	while (!glfwWindowShouldClose(m_window)) {
		INPUT_MANAGER->processInput(m_window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		WINDOW_MANAGER->render();
		INPUT_MANAGER->handleEvent();
	}
}

void Engine::cleanup()
{
	glfwTerminate();
}
