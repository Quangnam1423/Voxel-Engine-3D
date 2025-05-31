#include "Engine.h"

#include "EngineManager/WindowManager.h"
#include "EngineManager/InputManager.h"
#include "EngineManager/ResourceManager.h"
#include "EngineManager/CameraManager.h"
#include "Objects/Triangle.h"	
#include "Objects/Shader.h"
#include "Objects/Cube.h"
#include "Objects/ColorCube.h"
#include "Objects/LightCube.h"
#include "Objects/Rectangle.h"
#include "Objects/Camera.h"
#include "Objects/WoodBox.h"
#include "Objects/Cube.h"
#include "Ingredient/Model.h"
#include <iostream>

Engine::Engine()
{
	m_elapseTime = 0.0f;
	m_lightCube = nullptr;
	m_colorCube = nullptr;
	m_woodBox = nullptr;
	m_normalCube = nullptr;
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
		camera->setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
		camera->setWorldUp(glm::vec3(0.0f, 1.0f, 0.0f));
		camera->setTarget({ 0.0f, 0.0f, 0.0f });
		CM->setCamera(camera);
	}

	{
		m_shader = new Shader("Resource/Shaders/model.vert", "Resource/Shaders/model.frag");
	}

	{
		m_model = DATA->getModel("Resource/Models/backpack/backpack.obj");
		m_model2 = DATA->getModel("Resource/Models/dead_by_daylight_-_the_animatronic/scene.gltf");
	}


	// init color Cube
	{
		m_colorCube = new ColorCube();
		m_colorCube->setShader(new Shader("Resource/Shaders/colorCube.vert", "Resource/Shaders/colorCube.frag"));
	}

	// init normal Cube
	{
		m_normalCube = new Cube();
		m_normalCube->setShader(new Shader("Resource/Shaders/cube.vert", "Resource/Shaders/cube.frag"));
		m_normalCube->setTexture(DATA->getTexture("Resource/Texture/container.jpg"));
	}

	//init light source cube
	{
		m_lightCube = new LightCube();
		m_lightCube->setShader(new Shader("Resource/Shaders/lightCube.vert", "Resource/Shaders/lightCube.frag"));
	}

	// init wood box
	{
		m_woodBox = new WoodBox();
		m_woodBox->setShader(new Shader("Resource/Shaders/WoodBox.vert", "Resource/Shaders/WoodBox.frag"));
		m_woodBox->setDiffuseTexture(DATA->getTexture("Resource/Texture/container.png"));
		m_woodBox->setSpecularTexture(DATA->getTexture("Resource/Texture/container_specular.png"));
	}

	// callback
	{
		glfwSetCursorPosCallback(WINDOW_MANAGER->getWindow(), InputManager::mouseCallback);
	}
}

void Engine::run()
{
	while (!glfwWindowShouldClose(WINDOW_MANAGER->getWindow())) {
		float deltaTime = static_cast<float>(glfwGetTime()) - m_elapseTime;
		float m_elapseTime = static_cast<float>(glfwGetTime());
		INPUT_MANAGER->processInput(deltaTime);

		glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = CM->getCamera()->getViewMatrix();
		glm::vec3 cameraPosition = CM->getCamera()->getPosition();
		float aspect = (float)WINDOW_MANAGER->getWindowSize().width / (float)WINDOW_MANAGER->getWindowSize().height;
		glm::mat4 projection = glm::perspective(glm::radians(CM->getCamera()->getZoom()), aspect, 0.1f, 500.f);
		m_colorCube->draw(view, projection, cameraPosition, {0.0f, 0.0f, 0.0f});
		m_lightCube->draw(view, projection);

		m_normalCube->draw(view, projection);
		m_woodBox->draw(view, projection, cameraPosition, { 0.0f, 0.0f, 0.0f });
		m_shader->use();
		m_shader->setMat4("view", view);
		m_shader->setMat4("projection", projection);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		m_shader->setMat4("model", model);
		m_model->draw(*m_shader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 5.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
		m_shader->setMat4("model", model);
		m_model2->draw(*m_shader);
		WINDOW_MANAGER->render();
		INPUT_MANAGER->handleEvent();
	}
}

void Engine::cleanup()
{
	glfwTerminate();
}
