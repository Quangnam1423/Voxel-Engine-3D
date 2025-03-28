#include "Cube.h"
#include "Shader.h"

Cube::Cube()
{
}

Cube::~Cube()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	delete m_shader;
}

void Cube::draw()
{
	m_shader->use();
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Cube::setShader(Shader* shader)
{
	m_shader = shader;
}
