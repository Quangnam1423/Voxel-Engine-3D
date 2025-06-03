#include "ChunkMesh.h"
#include "Shader.h"

ChunkMesh::ChunkMesh()
{
	m_vao = 0;
	m_vbo = 0;
	m_ebo = 0;
	m_numIndices = 0;
}

ChunkMesh::~ChunkMesh()
{
	if (m_vao != 0) {
		glDeleteVertexArrays(1, &m_vao);
		m_vao = 0;
	}
	if (m_vbo != 0) {
		glDeleteBuffers(1, &m_vbo);
		m_vbo = 0;
	}
	if (m_ebo != 0) {
		glDeleteBuffers(1, &m_ebo);
		m_ebo = 0;
	}
	m_numIndices = 0;
}

void ChunkMesh::draw(Shader& shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
	shader.use();
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void ChunkMesh::setupMesh(const std::vector<VoxelVertex> vertices, const std::vector<unsigned int> indices)
{
	m_numIndices = static_cast<unsigned int>(indices.size());
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VoxelVertex), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VoxelVertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VoxelVertex), (void*)offsetof(VoxelVertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VoxelVertex), (void*)offsetof(VoxelVertex, textCoord));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
