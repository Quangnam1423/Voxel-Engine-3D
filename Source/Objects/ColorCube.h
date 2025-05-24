#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Shader;

struct CubeVertex
{
	glm::vec3 position;
	glm::vec3 normal;
};

class ColorCube
{
public:
	ColorCube();
	~ColorCube();
	void draw(glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPosition, glm::vec3 lightPosition);
	void cleanup();
	void setShader(Shader* shader) { m_shader = shader; }

private:
	std::vector<CubeVertex> m_vertices;
	std::vector<GLuint> m_indices;
	GLuint m_vao, m_vbo, m_ebo;
	Shader* m_shader;
};

