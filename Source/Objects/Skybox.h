#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>

class Shader;

class Skybox
{
public:
	Skybox();
	~Skybox();

	void draw(const glm::mat4& view, const glm::mat4& projection);
	void setTexture(GLuint cubemapTextureId) { m_cubemapTextureId = cubemapTextureId; }
	void setShader(Shader* shader) { m_shader = shader; }
	void init();
private:
	void cleanup();

	GLuint m_vao, m_vbo;
	GLuint m_cubemapTextureId;
	Shader* m_shader;
};

