#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <FastNoiseLite.h>

#define CHUNK_SIZE 16

class ChunkMesh;
class Shader;
class Voxel;

class Chunk
{
public:
	Chunk();
	~Chunk();
	void setupChunk();
	void draw(glm::mat4 view, glm::mat4 projection);
	void setShader(Shader* shader) { m_shader = shader; }
	void setPosition(glm::vec3 position) { m_position = position; }
	void initChunk();
	void setTexture(GLuint textureId) { m_textureID = textureId; }
private:
	glm::vec3 m_position;
	GLuint m_textureID;
	Shader* m_shader;
	ChunkMesh* m_chunkMesh;
	std::vector<Voxel*> m_voxels;	
};

