#include "WoodBox.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Shader.h"

WoodBox::WoodBox()
{
	m_shader = nullptr;
	m_diffuseTextureId = 0;
	m_specularTextureId = 0;
	glm::vec3 frontNormal = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 backNormal = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 leftNormal = glm::vec3(-1.0f, 0.0f, 0.0f);
	glm::vec3 rightNormal = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 topNormal = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 bottomNormal = glm::vec3(0.0f, -1.0f, 0.0f);
	m_vertices = {
		//Front face
		{ glm::vec3(-0.5f, -0.5f,  0.5f), frontNormal, glm::vec2(0.0f, 1.0f) }, // Bottom-left
		{ glm::vec3(0.5f, -0.5f,  0.5f), frontNormal, glm::vec2(1.0f, 1.0f) }, // Bottom-right
		{ glm::vec3(0.5f,  0.5f,  0.5f), frontNormal, glm::vec2(1.0f, 0.0f) }, // Top-right
		{ glm::vec3(-0.5f,  0.5f,  0.5f), frontNormal, glm::vec2(0.0f, 0.0f) }, // Top-left

		// Back face
		{ glm::vec3(-0.5f, -0.5f, -0.5f), backNormal, glm::vec2(1.0f, 1.0f) }, // Bottom-left
		{ glm::vec3(0.5f, -0.5f, -0.5f), backNormal, glm::vec2(0.0f, 1.0f) }, // Bottom-right
		{ glm::vec3(0.5f,  0.5f, -0.5f), backNormal, glm::vec2(0.0f, 0.0f) }, // Top-right
		{ glm::vec3(-0.5f,  0.5f, -0.5f),  backNormal,glm::vec2(1.0f, 0.0f) }, // Top-left

		// Left face
		{ glm::vec3(-0.5f, -0.5f, -0.5f), leftNormal,  glm::vec2(0.0f, 1.0f) }, // Bottom-left
		{ glm::vec3(-0.5f, -0.5f,  0.5f), leftNormal, glm::vec2(1.0f, 1.0f) }, // Bottom-right
		{ glm::vec3(-0.5f,  0.5f,  0.5f), leftNormal, glm::vec2(1.0f, 0.0f) }, // Top-right
		{ glm::vec3(-0.5f,  0.5f, -0.5f), leftNormal, glm::vec2(0.0f, 0.0f) }, // Top-left

		// Right face
		{ glm::vec3(0.5f, -0.5f,  0.5f), leftNormal, glm::vec2(0.0f, 1.0f) }, // Bottom-left
		{ glm::vec3(0.5f, -0.5f, -0.5f), leftNormal, glm::vec2(1.0f, 1.0f) }, // Bottom-right
		{ glm::vec3(0.5f,  0.5f, -0.5f), leftNormal, glm::vec2(1.0f, 0.0f) }, // Top-right
		{ glm::vec3(0.5f,  0.5f,  0.5f), leftNormal, glm::vec2(0.0f, 0.0f) }, // Top-left

		// Top face
		{ glm::vec3(-0.5f,  0.5f,  0.5f), topNormal, glm::vec2(0.0f, 1.0f) }, // Bottom-left
		{ glm::vec3(0.5f,  0.5f,  0.5f), topNormal, glm::vec2(1.0f, 1.0f) }, // Bottom-right
		{ glm::vec3(0.5f,  0.5f, -0.5f), topNormal, glm::vec2(1.0f, 0.0f) }, // Top-right
		{ glm::vec3(-0.5f,  0.5f, -0.5f), topNormal, glm::vec2(0.0f, 0.0f) }, // Top-left

		// Bottom face
		{ glm::vec3(-0.5f, -0.5f, -0.5f), bottomNormal, glm::vec2(0.0f, 0.0f) }, // Bottom-left
		{ glm::vec3(0.5f, -0.5f, -0.5f), bottomNormal, glm::vec2(1.0f, 0.0f) }, // Bottom-right
		{ glm::vec3(0.5f, -0.5f,  0.5f), bottomNormal, glm::vec2(1.0f, 1.0f) }, // Top-right
		{ glm::vec3(-0.5f, -0.5f,  0.5f), bottomNormal, glm::vec2(0.0f, 1.0f) }  // Top-left
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
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(WoodBoxVertex), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), m_indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(WoodBoxVertex), (void*)0);

	glEnableVertexAttribArray(1); // Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(WoodBoxVertex), (void*)offsetof(WoodBoxVertex, normal));

	glEnableVertexAttribArray(2); // Texture Coordinate
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(WoodBoxVertex), (void*)offsetof(WoodBoxVertex, textureCoord));

	glBindVertexArray(0); // Unbind VAO

}

WoodBox::~WoodBox()
{
    cleanup();
}

void WoodBox::draw(glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPosition, glm::vec3 lightPosition)
{
    m_shader->use();
	m_shader->setVec3("light.position", lightPosition);
	m_shader->setVec3("viewPos", cameraPosition);   
	
	// light properties
	m_shader->setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	m_shader->setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	m_shader->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

	m_shader->setFloat("material.shininess", 64.0f);

	// view/projection transformations
	m_shader->setMat4("view", view);
	m_shader->setMat4("projection", projection);
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 2.0f, 2.0f));
	m_shader->setMat4("model", model);

	glActiveTexture(GL_TEXTURE0);
	if (m_diffuseTextureId) {
		glBindTexture(GL_TEXTURE_2D, m_diffuseTextureId);
		m_shader->setInt("material.diffuse", 0);
	}

	glActiveTexture(GL_TEXTURE1);
	if (m_specularTextureId) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_specularTextureId);
		m_shader->setInt("material.specular", 1);
	}

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);
}

void WoodBox::cleanup()
{
	if (m_vao) {
		glDeleteVertexArrays(1, &m_vao);
		m_vao = 0;
	}
	if (m_vbo) {
		glDeleteBuffers(1, &m_vbo);
		m_vbo = 0;
	}
	if (m_ebo) {
		glDeleteBuffers(1, &m_ebo);
		m_ebo = 0;
	}
	if (m_shader) {
		delete m_shader;
		m_shader = nullptr;
	}
	if (m_specularTextureId) {
		glDeleteTextures(1, &m_specularTextureId);
		m_specularTextureId = 0;
	}
	if (m_diffuseTextureId) {
		glDeleteTextures(1, &m_diffuseTextureId);
		m_diffuseTextureId = 0;
	}
}
