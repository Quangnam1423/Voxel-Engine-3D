#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <list>

class Skybox;
class Shader;
class Camera;
class Chunk;
class ChunkManager;
class Model;

class World
{
public:
	World();
	~World();
	void update(float deltaTime);
	void draw();
	
private:
	void init();
	void cleanup();

	Skybox* m_skybox;
	Chunk* m_chunk;
	//Model* m_model;
};

