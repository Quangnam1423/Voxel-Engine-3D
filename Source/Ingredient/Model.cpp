#include "Model.h"
#include "Mesh.h"
#include "../Objects/Shader.h"


Model::Model() {
	m_shader = nullptr;
	m_gammaCorrection = true;
}

Model::~Model() {
	// Destructor implementation can be added here if needed
	m_meshes.clear();
	m_texture_loaded.clear();
}

void Model::draw(glm::mat4 view, glm::mat4 projection) 
{
	m_shader->use();
	m_shader->setMat4("view", view);
	m_shader->setMat4("projection", projection);
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, m_position);
	modelMatrix = glm::scale(modelMatrix, {2.0f, 2.0f, 2.0f});
	m_shader->setMat4("model", modelMatrix);
	for (unsigned int i = 0; i < m_meshes.size(); i++) {
		m_meshes[i]->draw(*m_shader);
	}
}

void Model::addMesh(Mesh* mesh)
{
	m_meshes.push_back(mesh);
}
