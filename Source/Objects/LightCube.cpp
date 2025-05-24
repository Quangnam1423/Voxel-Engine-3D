#include "LightCube.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

LightCube::LightCube()
{
	m_shader = nullptr;

	m_vertices = {
        // Front face
		{glm::vec3(-0.5f, -0.5f,  0.5f)},
		{ glm::vec3(0.5f, -0.5f,  0.5f) },  // Bottom-right
		{ glm::vec3(0.5f,  0.5f,  0.5f)},  // Top-right
		{ glm::vec3(-0.5f,  0.5f,  0.5f)}, // Top-left

		// Back face
		{ glm::vec3(-0.5f, -0.5f, -0.5f)},
		{ glm::vec3(0.5f, -0.5f, -0.5f)},
		{ glm::vec3(0.5f,  0.5f, -0.5f)},
		{ glm::vec3(-0.5f,  0.5f, -0.5f)},

		// Left face
		{ glm::vec3(-0.5f, -0.5f, -0.5f)},
		{ glm::vec3(-0.5f, -0.5f,  0.5f) },
		{ glm::vec3(-0.5f,  0.5f,  0.5f) },
		{ glm::vec3(-0.5f,  0.5f, -0.5f) },

		// Right face
		{ glm::vec3(0.5f, -0.5f,  0.5f) },
		{ glm::vec3(0.5f, -0.5f, -0.5f) },
		{ glm::vec3(0.5f,  0.5f, -0.5f) },
		{ glm::vec3(0.5f,  0.5f,  0.5f) },

		// Top face
		{ glm::vec3(-0.5f,  0.5f,  0.5f) },
		{ glm::vec3(0.5f,  0.5f,  0.5f) },
		{ glm::vec3(0.5f,  0.5f, -0.5f) },
		{ glm::vec3(-0.5f,  0.5f, -0.5f) },

		// Bottom face
		{ glm::vec3(-0.5f, -0.5f, -0.5f) },
		{ glm::vec3(0.5f, -0.5f, -0.5f) },
		{ glm::vec3(0.5f, -0.5f,  0.5f) },
		{ glm::vec3(-0.5f, -0.5f,  0.5f) }
	};

	m_indices = {
		// Front face
		0, 1, 2, 2, 3, 0,
		// Back face
		4, 5, 6, 6, 7, 4,
		// Left face
		8, 9, 10, 10, 11, 8,
		// Right face
		12, 13, 14, 14, 15, 12,
		// Top face
		16, 17, 18, 18, 19, 16,
		// Bottom face
		20, 21, 22, 22, 23, 20
	};

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(LightVertex), m_vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), m_indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LightVertex), (void*)0);
	glBindVertexArray(0);
}

LightCube::~LightCube()
{
	cleanup();
}

void LightCube::draw(glm::mat4 view, glm::mat4 projection)
{
	m_shader->use();

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	m_shader->setMat4("model", model);
	m_shader->setMat4("view", view);
	m_shader->setMat4("projection", projection);

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void LightCube::cleanup()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	glDeleteProgram(m_shader->getId());
	m_vertices.clear();
	m_indices.clear();
}
