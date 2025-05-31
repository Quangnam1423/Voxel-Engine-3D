#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "Material.h"
#include "Texture.h"

class Shader;
class Mesh;

class Model
{
private:
	std::vector<Texture> m_texture_loaded;
	std::vector<Mesh*> m_meshes;
	std::string m_directory;
	bool m_gammaCorrection;
public:
	Model();
	~Model();
	void draw(Shader& shader);
	void setDirectory(const std::string& directory) { m_directory = directory; }
	std::string getDirectory() const { return m_directory; }
	void setGammaCorrection(bool gamma) { m_gammaCorrection = gamma; }
	void addMesh(Mesh* mesh);
	std::vector<Texture> getTextures() const { return m_texture_loaded; }
	void addTexture(Texture texture) 
	{ 
		m_texture_loaded.push_back(texture); 
	}
};

