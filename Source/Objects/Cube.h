#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "Vertex.h"

class Shader;

class Cube
{
public:
	Cube();
	~Cube();
	void draw();

	void setShader(Shader* shader);

private:
	Shader* m_shader;
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;

	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;
};

