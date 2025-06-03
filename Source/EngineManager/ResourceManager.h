#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>
#include <iostream>
#include <map>
#include <unordered_map>
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "../Ingredient/Texture.h"
#include "../Singleton.h"

class Mesh;
class Model;

#define DATA ResourceManager::getInstance()

std::string getFileExtension(const std::string& filename);

// get texture from resource manager by path of texture
// if texture is not loaded, load it and return the texture id
// else	return the texture id
// if texture is not found, return -1

// Resource Manager can not distingush between .png and .jpg
// so that it will load the texture with the first extension foundas

class ResourceManager : public Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;
public:
	ResourceManager();
	~ResourceManager();

	GLuint getTexture(std::string texturePath);
	bool loadTexture(std::string texturePath);
	bool loadModel(std::string modelPath);
	Model* getModel(std::string modelPath);

	GLuint loadCubemapTexture(const std::vector<std::string>& faces, const std::string& cubemapName);
private:
	void processNode(aiNode* node, const aiScene* scene, Model* model);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene, Model* model);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, Model* model);

private:
	std::map<std::string, GLuint> m_textures;
	std::unordered_map<std::string, Model*> m_models;
	std::map<std::string, GLuint> m_cubemaps;
};


