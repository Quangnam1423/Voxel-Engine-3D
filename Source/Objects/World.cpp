#include "World.h"

#include "../EngineManager/ResourceManager.h"
#include "../EngineManager/CameraManager.h"
#include "../EngineManager/InputManager.h"
#include "Skybox.h"
#include "Chunk.h"
#include "Shader.h"
#include "../Ingredient/Model.h"

World::World()
{
	m_skybox = nullptr;
	m_chunk = nullptr;
	init();
}

World::~World()
{
	cleanup();
}

void World::update(float deltaTime)
{
}

void World::draw() {
	glm::mat4 view = CM->getCamera()->getViewMatrix();
	glm::vec3 cameraPosition = CM->getCamera()->getPosition();
	float aspect = (float)WINDOW_MANAGER->getWindowSize().width / (float)WINDOW_MANAGER->getWindowSize().height;
	glm::mat4 projection = glm::perspective(glm::radians(CM->getCamera()->getZoom()), aspect, 0.1f, 500.f);

	m_chunk->draw(view, projection);
	m_model->draw(view, projection);
	glDepthMask(GL_FALSE);
	m_skybox->draw(view, projection);
	glDepthMask(GL_TRUE);
}

void World::init()
{
	// init skybox
	{
		m_skybox = new Skybox();
		m_skybox->setShader(new Shader("Resource/Shaders/skybox.vert", "Resource/Shaders/skybox.frag"));
		std::vector<std::string> faces = {
			"Resource/Texture/Skybox/right.jpg",
			"Resource/Texture/Skybox/left.jpg",
			"Resource/Texture/Skybox/top.jpg",
			"Resource/Texture/Skybox/bottom.jpg",
			"Resource/Texture/Skybox/front.jpg",
			"Resource/Texture/Skybox/back.jpg"
		};
		m_skybox->setTexture(DATA->loadCubemapTexture(faces, "skybox1"));
		m_skybox->init();
	}

	//init chunk
	{
		m_chunk = new Chunk();
		m_chunk->setShader(new Shader("Resource/Shaders/chunk.vert", "Resource/Shaders/chunk.frag"));
		m_chunk->setTexture(DATA->getTexture("Resource/Texture/blocks4.png"));
		m_chunk->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	}

	// init model
	{
		m_model = DATA->getModel("Resource/Models/backpack/backpack.obj");
		m_model->setShader(new Shader("Resource/Shaders/model.vert", "Resource/Shaders/model.frag"));
		m_model->setPosition({ 0.0f, 20.0f, 15.0f });
	}
}

void World::cleanup()
{
	if (m_skybox) {
		delete m_skybox;
		m_skybox = nullptr;
	}
	
	if (m_chunk) {
		delete m_chunk;
		m_chunk = nullptr;
	}

	if (m_model) {
		delete m_model;
		m_model = nullptr;
	}
}
