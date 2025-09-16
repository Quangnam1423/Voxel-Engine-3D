#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <mutex>
#include <atomic>
#include <FastNoiseLite.h>
#include "Voxel.h"

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
	void setupMesh();
	void draw(glm::mat4 view, glm::mat4 projection);
	void setShader(Shader* shader) { m_shader = shader; }
	void setPosition(glm::vec3 position) { m_position = position; }
	void initChunk();
	void setTexture(GLuint textureId) { m_textureID = textureId; }
	GLuint getTexture() const { return m_textureID; }
	std::atomic<bool>& isReadyToDraw() { return m_isReadyToDraw; }
	std::atomic<bool>& isMeshReady() { return m_isMeshReady; }
private:
	glm::vec3 m_position;
	GLuint m_textureID;
	Shader* m_shader;
	ChunkMesh* m_chunkMesh;
	std::vector<Voxel*> m_voxels;	
	std::vector<VoxelVertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::mutex m_mutex;
	std::atomic<bool> m_isReadyToDraw;
	std::atomic<bool> m_isMeshReady;

	static FastNoiseLite& getNoise() {
		static FastNoiseLite noise2d;
		noise2d.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
		noise2d.SetSeed(1337);
		noise2d.SetFrequency(0.015f);
		return noise2d;
	}
};

