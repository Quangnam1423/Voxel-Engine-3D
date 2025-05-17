#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Vertex.h"
#include "VoxelFace.h"

#define BLOCK_LEFT_TOPLEFT(x, y, z)			glm::vec3(-0.5f + x, 0.5f  + y, -0.5f + z)
#define BLOCK_LEFT_BOTTOMLEFT(x, y, z)		glm::vec3(-0.5f + x, -0.5f + y, -0.5f + z)
#define BLOCK_LEFT_BOTTOMRIGHT(x, y, z) 	glm::vec3(-0.5f + x, -0.5f + y, 0.5f  + z)
#define BLOCK_LEFT_TOPRIGHT(x, y, z) 		glm::vec3(-0.5f + x, 0.5f  + y, 0.5f  + z)

#define BLOCK_RIGHT_TOPLEFT(x, y, z)		glm::vec3(0.5f + x, 0.5f  + y, 0.5f  + z)
#define BLOCK_RIGHT_BOTTOMLEFT(x, y, z)		glm::vec3(0.5f + x, -0.5f + y, 0.5f  + z)
#define BLOCK_RIGHT_BOTTOMRIGHT(x, y, z) 	glm::vec3(0.5f + x, -0.5f + y, -0.5f + z)
#define BLOCK_RIGHT_TOPRIGHT(x, y, z) 		glm::vec3(0.5f + x, 0.5f  + y, -0.5f + z)

#define BLOCK_TOP_TOPLEFT(x, y, z)			glm::vec3(-0.5f + x, 0.5f + y, -0.5f + z)
#define BLOCK_TOP_BOTTOMLEFT(x, y, z)		glm::vec3(-0.5f + x, 0.5f + y, 0.5f  + z)
#define BLOCK_TOP_BOTTOMRIGHT(x, y, z) 		glm::vec3(0.5f  + x, 0.5f + y, 0.5f  + z)
#define BLOCK_TOP_TOPRIGHT(x, y, z) 		glm::vec3(0.5f  + x, 0.5f + y, -0.5f + z)

#define BLOCK_BOTTOM_TOPLEFT(x, y, z)		glm::vec3(-0.5f + x, -0.5f + y, 0.5f  + z)
#define BLOCK_BOTTOM_BOTTOMLEFT(x, y, z)	glm::vec3(-0.5f + x, -0.5f + y, -0.5f + z)
#define BLOCK_BOTTOM_BOTTOMRIGHT(x, y, z) 	glm::vec3(0.5f  + x, -0.5f + y, -0.5f + z)
#define BLOCK_BOTTOM_TOPRIGHT(x, y, z) 		glm::vec3(0.5f  + x, -0.5f + y, 0.5f  + z)

#define BLOCK_FRONT_TOPLEFT(x, y, z)		glm::vec3(-0.5f + x, 0.5f  + y, 0.5f + z)
#define BLOCK_FRONT_BOTTOMLEFT(x, y, z)		glm::vec3(-0.5f + x, -0.5f + y, 0.5f + z)
#define BLOCK_FRONT_BOTTOMRIGHT(x, y, z) 	glm::vec3(0.5f  + x, -0.5f + y, 0.5f + z)
#define BLOCK_FRONT_TOPRIGHT(x, y, z) 		glm::vec3(0.5f  + x, 0.5f  + y, 0.5f + z)

#define BLOCK_BACK_TOPLEFT(x, y, z)			glm::vec3(0.5f  + x, 0.5f  + y, -0.5f + z)
#define BLOCK_BACK_BOTTOMLEFT(x, y, z)		glm::vec3(0.5f  + x, -0.5f + y, -0.5f + z)
#define BLOCK_BACK_BOTTOMRIGHT(x, y, z) 	glm::vec3(-0.5f + x, -0.5f + y, -0.5f + z)
#define BLOCK_BACK_TOPRIGHT(x, y, z) 		glm::vec3(-0.5f + x, 0.5f  + y, -0.5f + z)


struct Voxel {

};

