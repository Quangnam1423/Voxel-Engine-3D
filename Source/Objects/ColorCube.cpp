#include "ColorCube.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

ColorCube::ColorCube()
{
	m_shader = nullptr;
	glm::vec3 frontNormal = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 backNormal = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 leftNormal = glm::vec3(-1.0f, 0.0f, 0.0f);
	glm::vec3 rightNormal = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 topNormal = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 bottomNormal = glm::vec3(0.0f, -1.0f, 0.0f);
	m_vertices = {
        // Front face
        {glm::vec3(-0.5f, -0.5f,  0.5f), frontNormal },
        { glm::vec3(0.5f, -0.5f,  0.5f), frontNormal },  // Bottom-right
        { glm::vec3(0.5f,  0.5f,  0.5f), frontNormal },  // Top-right
        { glm::vec3(-0.5f,  0.5f,  0.5f), frontNormal }, // Top-left

        // Back face
        { glm::vec3(-0.5f, -0.5f, -0.5f), backNormal },
        { glm::vec3(0.5f, -0.5f, -0.5f), backNormal },
        { glm::vec3(0.5f,  0.5f, -0.5f), backNormal },
        { glm::vec3(-0.5f,  0.5f, -0.5f), backNormal },

        // Left face
        { glm::vec3(-0.5f, -0.5f, -0.5f), leftNormal },
        { glm::vec3(-0.5f, -0.5f,  0.5f), leftNormal },
        { glm::vec3(-0.5f,  0.5f,  0.5f), leftNormal },
        { glm::vec3(-0.5f,  0.5f, -0.5f), leftNormal },

        // Right face
        { glm::vec3(0.5f, -0.5f,  0.5f), rightNormal },
        { glm::vec3(0.5f, -0.5f, -0.5f), rightNormal },
        { glm::vec3(0.5f,  0.5f, -0.5f), rightNormal },
        { glm::vec3(0.5f,  0.5f,  0.5f), rightNormal },

        // Top face
        { glm::vec3(-0.5f,  0.5f,  0.5f), topNormal },
        { glm::vec3(0.5f,  0.5f,  0.5f), topNormal },
        { glm::vec3(0.5f,  0.5f, -0.5f), topNormal },
        { glm::vec3(-0.5f,  0.5f, -0.5f), topNormal },

        // Bottom face
        { glm::vec3(-0.5f, -0.5f, -0.5f), bottomNormal },
        { glm::vec3(0.5f, -0.5f, -0.5f), bottomNormal },
        { glm::vec3(0.5f, -0.5f,  0.5f), bottomNormal },
        { glm::vec3(-0.5f, -0.5f,  0.5f), bottomNormal }
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
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(CubeVertex), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), m_indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CubeVertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CubeVertex), (void*)offsetof(CubeVertex, normal));

	glBindVertexArray(0);
}

ColorCube::~ColorCube()
{
	cleanup();
}

void ColorCube::draw(glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPosition, glm::vec3 lightPosition)
{
    m_shader->use();
    m_shader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    m_shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    m_shader->setVec3("lightPos", lightPosition);
    m_shader->setVec3("viewPos", cameraPosition);

    glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, -2.0f, 5.0f));
	m_shader->setMat4("model", model);
	m_shader->setMat4("view", view);
	m_shader->setMat4("projection", projection);

    //set color for fragment shader
	m_shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void ColorCube::cleanup()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteProgram(m_shader->getId());
    m_vertices.clear();
	m_indices.clear();
}
