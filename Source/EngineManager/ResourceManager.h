#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>
#include <map>
#include <filesystem>
#include "../Singleton.h"

#define DATA ResourceManager::getInstance()

enum class TEXTURE_EXTENSION
{
	PNG,
	JPG,
	JPEG,
	TGA,
	BMP,
	UNKNOWN
};

class ResourceManager :public Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;
public:
	ResourceManager();
	~ResourceManager();
	bool loadTexture(const char* path, TEXTURE_EXTENSION extension);
	GLuint getTexture(const char* path);
	void deleteTexture(const char* path);	
private:
	std::map<std::string, GLuint> m_textureMap;
};
