#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Shader;

struct LightVertex
{
	glm::vec3 position;
};

class LightCube
{
public:

	LightCube();
	~LightCube();
	void draw(glm::mat4 view, glm::mat4 projection);
	void cleanup();
	void setShader(Shader* shader) { m_shader = shader; }
private:
	std::vector<LightVertex> m_vertices;
	std::vector<GLuint> m_indices;
	GLuint m_vao, m_vbo, m_ebo;
	Shader* m_shader;
};

