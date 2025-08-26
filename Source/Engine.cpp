#include "Engine.h"

#include "EngineManager/WindowManager.h"
#include "EngineManager/InputManager.h"
#include "EngineManager/ResourceManager.h"
#include "EngineManager/CameraManager.h"
#include "Objects/World.h"
#include <iostream>

Engine::Engine()
{
	m_elapseTime = 0.0f;
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
		GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_TITLE, NULL, NULL);
		if (!window) {
			std::cerr << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}
		WINDOW_MANAGER->setWindow(window);
	}

	// load glad
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cerr << "Failed to initialize GLAD" << std::endl;
			return;
		}
	}

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	{
		Camera* camera = new Camera();
		camera->setPosition(glm::vec3(-22.9384f, 20.3707f, 48.1196f));
		camera->setWorldUp(glm::vec3(0.0f, 1.0f, 0.0f));
		camera->setTarget(glm::vec3(-22.3352, 20.1152, 47.364));
		CM->setCamera(camera);
	}

	// init world
	{
		m_world = new World();
	}

	// callback
	{
		glfwSetCursorPosCallback(WINDOW_MANAGER->getWindow(), InputManager::mouseCallback);
			glfwSetKeyCallback(WINDOW_MANAGER->getWindow(), InputManager::keyCallback);
	}
}

void Engine::run()
{
	while (!glfwWindowShouldClose(WINDOW_MANAGER->getWindow())) {
		float deltaTime = static_cast<float>(glfwGetTime()) - m_elapseTime;
		m_elapseTime = static_cast<float>(glfwGetTime());
		std::cout << " camera target: " << CM->getCamera()->getTarget().x << " " << CM->getCamera()->getTarget().y << " " << CM->getCamera()->getTarget().z << std::endl;
		INPUT_MANAGER->processInput(deltaTime);
		m_world->update(deltaTime);
		glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_world->draw();
		WINDOW_MANAGER->render();
		INPUT_MANAGER->handleEvent();
	}
}

void Engine::cleanup()
{
	glfwTerminate();
}
