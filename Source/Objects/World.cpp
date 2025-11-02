#include "World.h"

#include "../EngineManager/ResourceManager.h"
#include "../EngineManager/CameraManager.h"
#include "../EngineManager/InputManager.h"
#include "Skybox.h"
#include "Chunk.h"
#include "ChunkManager.h"
#include "Shader.h"
#include "../Ingredient/Model.h"

World::World()
{
	m_skybox = nullptr;
	//m_chunk = nullptr;
	init();
}

World::~World()
{
	cleanup();
}

void World::update(float deltaTime)
{
	//if (m_chunk && m_chunk->isMeshReady() && !m_chunk->isReadyToDraw()) {
	//	m_chunk->setupMesh();
	//}
	// update camera position
	{
		glm::vec3 cameraPos = CM->getCamera()->getPosition();
		m_chunkManager->Update(deltaTime, cameraPos);
	}
}

void World::draw() {
	glm::mat4 view = CM->getCamera()->getViewMatrix();
	glm::vec3 cameraPosition = CM->getCamera()->getPosition();
	float aspect = (float)WINDOW_MANAGER->getWindowSize().width / (float)WINDOW_MANAGER->getWindowSize().height;
	glm::mat4 projection = glm::perspective(glm::radians(CM->getCamera()->getZoom()), aspect, 0.1f, 500.f);

	//if (m_chunk->isReadyToDraw()) {
	//	m_chunk->draw(view, projection);
	//}
	if (m_chunkManager) {
		m_chunkManager->DrawVisibleChunks(view, projection);
	}

	// draw skybox last
	{
		glDepthMask(GL_FALSE);
		m_skybox->draw(view, projection);
		glDepthMask(GL_TRUE);
	}
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
	// init ChunkManager
	{
		m_chunkManager = new ChunkManager();
		m_chunkManager->setShader(new Shader("Resource/Shaders/chunk.vert", "Resource/Shaders/chunk.frag"));
		//m_chunkManager->Init(CM->getCamera()->getPosition());
	}
}

void World::cleanup()
{
	if (m_skybox) {
		delete m_skybox;
		m_skybox = nullptr;
	}

	if (m_chunkManager) {
		delete m_chunkManager;
		m_chunkManager = nullptr;
	}
	
	//if (m_chunk) {
	//	delete m_chunk;
	//	m_chunk = nullptr;
	//}

	//if (m_model) {
	//	delete m_model;
	//	m_model = nullptr;
	//}
}
