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
private:
	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;
	unsigned int m_vao, m_vbo, m_ebo;
	GLuint m_textureID;
	Shader* m_shader;

public:
	Cube();
	~Cube();
	void draw(glm::mat4 view, glm::mat4 projection);
	void cleanup();
	void setShader(Shader* shader) { m_shader = shader; }
	void setTexture(GLuint textureID) { m_textureID = textureID; }
	std::vector<Vertex>& getVertices() { return m_vertices; }
	std::vector<GLuint>& getIndices() { return m_indices; }
	unsigned int getVao() { return m_vao; }
	unsigned int getVbo() { return m_vbo; }
	unsigned int getEbo() { return m_ebo; }
};

