#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

#include "Texture.h"
#include "ModelVertex.h"

class Shader;

class Mesh
{
public:
	std::vector<ModelVertex> m_vertices;
	std::vector<GLuint> m_indices;
	std::vector<Texture> m_textures;
public:
	Mesh(std::vector<ModelVertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	~Mesh();

	void draw(Shader& shader);
	
private:
	void cleanup();
	void setupMesh();


private:
	
	unsigned int m_numIndices;
	unsigned int m_vao, m_vbo, m_ebo;

};

