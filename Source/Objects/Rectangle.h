#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
class Shader;

class Rectangle
{
private:
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
	unsigned int m_vao, m_vbo, m_ebo;
	GLuint m_textureID;
	Shader* m_shader;
public:
	Rectangle();
	~Rectangle();
	void draw();
	void cleanup();
	std::vector<float>& getVertices() { return m_vertices; }
	std::vector<unsigned int>& getIndices() { return m_indices; }
	unsigned int getVao() { return m_vao; }
	unsigned int getVbo() { return m_vbo; }
	unsigned int getEbo() { return m_ebo; }

	void setShader(Shader* shader) { m_shader = shader; }
	void setTexure(GLuint textureID) { m_textureID = textureID; }
};

