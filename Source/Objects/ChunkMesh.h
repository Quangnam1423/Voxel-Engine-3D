#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <glm/fwd.hpp>
#include "Vertex.h"

class Shader;

class ChunkMesh
{
public:

	ChunkMesh();
	~ChunkMesh();

	void draw(Shader& shader, glm::mat4 model, glm::mat4 view,  glm::mat4 projection);
	void setupMesh(const std::vector<VoxelVertex> vertices, const std::vector<unsigned int> indices);
private:

	unsigned int m_numIndices;
	unsigned int m_vao, m_vbo, m_ebo;

};

