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
	Cube(const char* texturePath, const char* vertexShaderPath, const char* fragmentShaderPath);
	~Cube();
	void draw(const glm::mat4& view, const glm::mat4& projection,  const glm::mat4& model);
	void init(const char* texturePath, const char* vertexShaderPath, const char* fragmentShaderPath);
	void setShader(Shader* shader);

private:
	Shader* m_shader;
	GLuint m_textureID;
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;

	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;
};

