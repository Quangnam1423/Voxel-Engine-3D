#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

struct FloorVertex
{
	glm::vec3 position;
	glm::vec3 normal;
};

class Shader;

class Floor
{
public:
	Floor();
	~Floor();
private:
	void cleanup();
	void init();

	void setPosition(glm::vec3 position) { m_position = position; }

private:
	glm::vec3 m_position;
	unsigned int m_vao, m_vbo, m_ebo;;
	unsigned int m_numIndices;
};

