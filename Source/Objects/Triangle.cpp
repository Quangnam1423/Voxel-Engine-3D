#include "Triangle.h"
#include <glad/glad.h>
#include "Shader.h"

Triangle::Triangle()
{
	m_shader = nullptr;
}

Triangle::~Triangle()
{
}

void Triangle::init()
{
	// Vertex data for a triangle
	m_vertices = {
		0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	m_indices = {
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the VBO
	glBindVertexArray(0); // Unbind the VAO
}

void Triangle::draw()
{
	glUseProgram(m_shader->getId());
	m_shader->use();
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
}

void Triangle::cleanup()
{
	if (m_VBO)
	{
		glDeleteBuffers(1, &m_VBO);
		m_VBO = 0;
	}
	if (m_VAO)
	{
		glDeleteVertexArrays(1, &m_VAO);
		m_VAO = 0;
	}
	if (m_shader)
	{
		delete m_shader;
		m_shader = nullptr;
	}
}

void Triangle::setShader(Shader* shader)
{
	m_shader = shader;
}
