#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>
#include <map>
#include <filesystem>
#include "../Singleton.h"

#define DATA ResourceManager::getInstance()

std::string getFileExtension(const std::string& filename);

// get texture from resource manager by path of texture
// if texture is not loaded, load it and return the texture id
// else	return the texture id
// if texture is not found, return -1

// Resource Manager can not distingush between .png and .jpg
// so that it will load the texture with the first extension found

class ResourceManager : public Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;
public:
	ResourceManager();
	~ResourceManager();

	GLuint getTexture(std::string texturePath);
	bool loadTexture(std::string texturePath);
private:
	std::map<std::string, GLuint> m_textures;
};


