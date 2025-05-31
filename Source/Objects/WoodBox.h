#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Shader;

struct WoodBoxVertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoord;
};

class WoodBox
{
public:
	WoodBox();
	~WoodBox();
	void draw(glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPosition, glm::vec3 lightPosition);
	void cleanup();
	void setShader(Shader* shader) { m_shader = shader; }
	void setSpecularTexture(GLuint textureId) { m_specularTextureId = textureId; }
	void setDiffuseTexture(GLuint textureId) { m_diffuseTextureId = textureId; }
private:
	std::vector<WoodBoxVertex> m_vertices;
	std::vector<GLuint> m_indices;
	GLuint m_vao, m_vbo, m_ebo;
	Shader* m_shader;
	GLuint m_specularTextureId;
	GLuint m_diffuseTextureId;
};

