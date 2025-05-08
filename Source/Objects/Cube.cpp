#include "Cube.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Cube::Cube()
{
	m_shader = nullptr;
	m_textureID = 0;
    m_vertices = {
        // Front face
        Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 1.0f), 1 }, // Bottom-left
        Vertex{ glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 1.0f), 1 }, // Bottom-right
        Vertex{ glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f), 1 }, // Top-right
        Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 0.0f), 1 }, // Top-left

        // Back face
        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f), 1 }, // Bottom-left
        Vertex{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f), 1 }, // Bottom-right
        Vertex{ glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 0.0f), 1 }, // Top-right
        Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 0.0f), 1 }, // Top-left

        // Left face
        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f), 1 }, // Bottom-left
        Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 1.0f), 1 }, // Bottom-right
        Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f), 1 }, // Top-right
        Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 0.0f), 1 }, // Top-left

        // Right face
        Vertex{ glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 1.0f), 1 }, // Bottom-left
        Vertex{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f), 1 }, // Bottom-right
        Vertex{ glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 0.0f), 1 }, // Top-right
        Vertex{ glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 0.0f), 1 }, // Top-left

        // Top face
        Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 1.0f), 1 }, // Bottom-left
        Vertex{ glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f), 1 }, // Bottom-right
        Vertex{ glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 0.0f), 1 }, // Top-right
        Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 0.0f), 1 }, // Top-left

        // Bottom face
        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f), 1 }, // Bottom-left
        Vertex{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f), 1 }, // Bottom-right
        Vertex{ glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 1.0f), 1 }, // Top-right
        Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 1.0f), 1 }  // Top-left
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
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), m_indices.data(), GL_STATIC_DRAW);

	// position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textCoords));

	// texture coord attribute
	glEnableVertexAttribArray(2);
	glVertexAttribIPointer(2, 1, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, id));

	glBindVertexArray(0);
}

Cube::~Cube()
{
	cleanup();
}

void Cube::draw()
{
	m_shader->use();

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)800.0 / (float)600, 0.1f, 100.0f);
	m_shader->setMat4("model", model);
	m_shader->setMat4("view", view);
	m_shader->setMat4("projection", projection);

	m_shader->setInt("texture1", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Cube::cleanup()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	glDeleteTextures(1, &m_textureID);
	glDeleteProgram(m_shader->getId());
}
