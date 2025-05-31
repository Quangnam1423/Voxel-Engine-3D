#include "Model.h"
#include "Mesh.h"


Model::Model() {
	// Constructor implementation can be added here if needed
	m_gammaCorrection = true;
}

Model::~Model() {
	// Destructor implementation can be added here if needed
	m_meshes.clear();
	m_texture_loaded.clear();
}

void Model::draw(Shader& shader) 
{
	for (unsigned int i = 0; i < m_meshes.size(); i++) {
		m_meshes[i]->draw(shader);
	}
}

void Model::addMesh(Mesh* mesh)
{
	m_meshes.push_back(mesh);
}
