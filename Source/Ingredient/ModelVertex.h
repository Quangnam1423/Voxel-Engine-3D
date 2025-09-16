#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

#define MAX_BONE_INFLUENCE 4

struct ModelVertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoord;
	glm::vec3 tangent;
	glm::vec3 bitangent;
	int boneIds[MAX_BONE_INFLUENCE];
	float weights[MAX_BONE_INFLUENCE];
};