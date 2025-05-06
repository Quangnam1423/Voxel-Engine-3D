#include "ResourceManager.h"


// function to get the file extension from a file name
std::string getFileExtension(const std::string& filename)
{
	std::filesystem::path path(filename);
	return path.extension().string();
}

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	for (auto& texture : m_textures)
	{
		glDeleteTextures(1, &texture.second);
	}
	m_textures.clear();
}

GLuint ResourceManager::getTexture(std::string texturePath)
{
	if (m_textures.find(texturePath) != m_textures.end())
	{
		return m_textures[texturePath];
	}
	else
	{
		if (loadTexture(texturePath))
		{
			return m_textures[texturePath];
		}
		else
		{
			std::cerr << "Failed to load texture: " << texturePath << std::endl;
			return -1;
		}
	}
	return 0;
}

bool ResourceManager::loadTexture(std::string texturePath)
{
    if (m_textures.find(texturePath) != m_textures.end()) {
        // Texture already loaded
        return true;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load texture data
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);

        // Store texture in the map
        m_textures[texturePath] = textureID;
        return true;
    }
    else {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
        stbi_image_free(data);
        return false;
    }
}