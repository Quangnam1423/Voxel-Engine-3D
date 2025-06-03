#pragma once

#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec2 textCoords;
	int id;
};

struct VoxelVertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textCoord;
};

//Type of block 
enum class Type
{
	AIR,
	GRASS,
	STONE,
	WATER,
	SAND
};

//face of cube
enum class Face
{
	FRONT,
	RIGHT,
	BACK,
	LEFT,
	TOP,
	BOTTOM
};