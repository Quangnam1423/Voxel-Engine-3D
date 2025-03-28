#include "ResourceManager.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	for (auto it = m_textureMap.begin(); it != m_textureMap.end(); it++)
	{
		glDeleteTextures(1, &it->second);
	}

	m_textureMap.clear();
}

bool ResourceManager::loadTexture(const char* path, TEXTURE_EXTENSION extension)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;
		if (extension == TEXTURE_EXTENSION::PNG)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		}
		else if (extension == TEXTURE_EXTENSION::JPG)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture: " << path << std::endl;
		stbi_image_free(data);
		return false;
	}
	stbi_image_free(data);
	m_textureMap[path] = texture;
	return true;
}

GLuint ResourceManager::getTexture(const char* path)
{
	for (auto it : m_textureMap)
	{
		if (it.first == path)
		{
			return it.second;
		}
	}

	std::string ext = std::filesystem::path(path).extension().string();
	
	bool isPNG = (ext == ".png" || ext == ".PNG");
	bool isJPG = (ext == ".jpg" || ext == ".jpeg" || ext == ".JPG" || ext == ".JPEG");

	if (isPNG) {
		TEXTURE_EXTENSION extension = TEXTURE_EXTENSION::PNG;
		return loadTexture(path, extension);
	}
	else if (isJPG) {
		TEXTURE_EXTENSION extension = TEXTURE_EXTENSION::JPG;
		return loadTexture(path, extension);
	}
	else {
		std::cout << "Unknown texture extension: " << ext << std::endl;
		return 0;
	}

	return m_textureMap[path];
}

void ResourceManager::deleteTexture(const char* path)
{
	for (auto it : m_textureMap)
	{
		if (it.first == path)
		{
			glDeleteTextures(1, &it.second);
			m_textureMap.erase(it.first);
			break;
		}
	}
	return;
}
