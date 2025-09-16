#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Vertex.h"

struct VoxelFace {
	Vertex vertices[4];
	GLuint indices[6];
};