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
#include <atomic>
#include <mutex>

#include "Material.h"
#include "Texture.h"

class Shader;
class Mesh;

class Model
{
private:
	std::vector<Texture> m_texture_loaded;
	std::vector<Mesh*> m_meshes;
	Shader* m_shader;
	std::string m_directory;
	glm::vec3 m_position;
	bool m_gammaCorrection;


	std::atomic<bool> m_isReadyToDraw;
	std::mutex m_mutex;
public:
	Model();
	~Model();
	void setShader(Shader* shader) { m_shader = shader; }
	void setPosition(const glm::vec3& position) { m_position = position; }
	void draw(glm::mat4 view, glm::mat4 projection);
	void setDirectory(const std::string& directory) { m_directory = directory; }
	std::string getDirectory() const { return m_directory; }
	void setGammaCorrection(bool gamma) { m_gammaCorrection = gamma; }
	void addMesh(Mesh* mesh);
	std::vector<Texture> getTextures() const { return m_texture_loaded; }
	std::mutex& getMutex() { return m_mutex; }
	void setIsReadyToDraw(bool ready) { m_isReadyToDraw = ready; }
	void addTexture(Texture texture) 
	{ 
		m_texture_loaded.push_back(texture); 
	}
};

