#pragma once

#include <glm/glm.hpp>
#include "Vertex.h"

// position of each vertex of cube 
//#define BLOCK_FRONT_TOPLEFT(x, y, z)		glm::vec3(-0.5f + x, -0.5f  + y, 0.5f + z)
//#define BLOCK_FRONT_BOTTOMLEFT(x, y, z)		glm::vec3(-0.5f + x, -0.5f + y, 0.5f + z)
//#define BLOCK_FRONT_BOTTOMRIGHT(x, y, z) 	glm::vec3(0.5f  + x, -0.5f + y, 0.5f + z)
//#define BLOCK_FRONT_TOPRIGHT(x, y, z) 		glm::vec3(0.5f  + x, 0.5f  + y, 0.5f + z)
//
//#define BLOCK_BACK_TOPLEFT(x, y, z)			glm::vec3(0.5f  + x, 0.5f  + y, -0.5f + z)
//#define BLOCK_BACK_BOTTOMLEFT(x, y, z)		glm::vec3(0.5f  + x, -0.5f + y, -0.5f + z)
//#define BLOCK_BACK_BOTTOMRIGHT(x, y, z) 	glm::vec3(-0.5f + x, -0.5f + y, -0.5f + z)
//#define BLOCK_BACK_TOPRIGHT(x, y, z) 		glm::vec3(-0.5f + x, 0.5f  + y, -0.5f + z)
//
//#define BLOCK_LEFT_TOPLEFT(x, y, z)			glm::vec3(-0.5f + x, 0.5f  + y, -0.5f + z)
//#define BLOCK_LEFT_BOTTOMLEFT(x, y, z)		glm::vec3(-0.5f + x, -0.5f + y, -0.5f + z)
//#define BLOCK_LEFT_BOTTOMRIGHT(x, y, z) 	glm::vec3(-0.5f + x, -0.5f + y, 0.5f  + z)
//#define BLOCK_LEFT_TOPRIGHT(x, y, z) 		glm::vec3(-0.5f + x, 0.5f  + y, 0.5f  + z)
//
//#define BLOCK_RIGHT_TOPLEFT(x, y, z)		glm::vec3(0.5f + x, 0.5f  + y, 0.5f  + z)
//#define BLOCK_RIGHT_BOTTOMLEFT(x, y, z)		glm::vec3(0.5f + x, -0.5f + y, 0.5f  + z)
//#define BLOCK_RIGHT_BOTTOMRIGHT(x, y, z) 	glm::vec3(0.5f + x, -0.5f + y, -0.5f + z)
//#define BLOCK_RIGHT_TOPRIGHT(x, y, z) 		glm::vec3(0.5f + x, 0.5f  + y, -0.5f + z)
//
//#define BLOCK_TOP_TOPLEFT(x, y, z)			glm::vec3(-0.5f + x, 0.5f + y, -0.5f + z)
//#define BLOCK_TOP_BOTTOMLEFT(x, y, z)		glm::vec3(-0.5f + x, 0.5f + y, 0.5f  + z)
//#define BLOCK_TOP_BOTTOMRIGHT(x, y, z) 		glm::vec3(0.5f  + x, 0.5f + y, 0.5f  + z)
//#define BLOCK_TOP_TOPRIGHT(x, y, z) 		glm::vec3(0.5f  + x, 0.5f + y, -0.5f + z)
//
//#define BLOCK_BOTTOM_TOPLEFT(x, y, z)		glm::vec3(-0.5f + x, -0.5f + y, 0.5f  + z)
//#define BLOCK_BOTTOM_BOTTOMLEFT(x, y, z)	glm::vec3(-0.5f + x, -0.5f + y, -0.5f + z)
//#define BLOCK_BOTTOM_BOTTOMRIGHT(x, y, z) 	glm::vec3(0.5f  + x, -0.5f + y, -0.5f + z)
//#define BLOCK_BOTTOM_TOPRIGHT(x, y, z) 		glm::vec3(0.5f  + x, -0.5f + y, 0.5f  + z)

// front face
#define BLOCK_FRONT_BOTTOMLEFT(x, y , z) glm::vec3(-0.5f + x, -0.5f + y, 0.5f + z)
#define BLOCK_FRONT_BOTTOMRIGHT(x, y, z) glm::vec3(0.5f + x, -0.5f + y, 0.5f + z)
#define BLOCK_FRONT_TOPRIGHT(x, y, z) glm::vec3(0.5f + x, 0.5f + y, 0.5f + z)
#define BLOCK_FRONT_TOPLEFT(x, y, z) glm::vec3(-0.5f + x, 0.5f + y, 0.5f + z)

// back face
#define BLOCK_BACK_BOTTOMLEFT(x, y, z) glm::vec3(-0.5f + x, -0.5f + y, -0.5f + z)
#define BLOCK_BACK_BOTTOMRIGHT(x, y, z) glm::vec3(0.5f + x, -0.5f + y, -0.5f + z)
#define BLOCK_BACK_TOPRIGHT(x, y, z) glm::vec3(0.5f + x, 0.5f + y, -0.5f + z)
#define BLOCK_BACK_TOPLEFT(x, y, z) glm::vec3(-0.5f + x, 0.5f + y, -0.5f + z)

// Left face
#define BLOCK_LEFT_BOTTOMLEFT(x, y, z) glm::vec3(-0.5f + x, -0.5f + y, -0.5f + z)
#define BLOCK_LEFT_BOTTOMRIGHT(x, y, z)  glm::vec3(-0.5f + x, -0.5f + y,  0.5f + z)
#define BLOCK_LEFT_TOPRIGHT(x, y, z)     glm::vec3(-0.5f + x,  0.5f + y,  0.5f + z)
#define BLOCK_LEFT_TOPLEFT(x, y, z)      glm::vec3(-0.5f + x,  0.5f + y, -0.5f + z)

// Right face
#define BLOCK_RIGHT_BOTTOMLEFT(x, y, z)  glm::vec3( 0.5f + x, -0.5f + y,  0.5f + z)
#define BLOCK_RIGHT_BOTTOMRIGHT(x, y, z) glm::vec3( 0.5f + x, -0.5f + y, -0.5f + z)
#define BLOCK_RIGHT_TOPRIGHT(x, y, z)    glm::vec3( 0.5f + x,  0.5f + y, -0.5f + z)
#define BLOCK_RIGHT_TOPLEFT(x, y, z)     glm::vec3( 0.5f + x,  0.5f + y,  0.5f + z)

// Top face
#define BLOCK_TOP_BOTTOMLEFT(x, y, z)    glm::vec3(-0.5f + x,  0.5f + y,  0.5f + z)
#define BLOCK_TOP_BOTTOMRIGHT(x, y, z)   glm::vec3( 0.5f + x,  0.5f + y,  0.5f + z)
#define BLOCK_TOP_TOPRIGHT(x, y, z)      glm::vec3( 0.5f + x,  0.5f + y, -0.5f + z)
#define BLOCK_TOP_TOPLEFT(x, y, z)       glm::vec3(-0.5f + x,  0.5f + y, -0.5f + z)

// Bottom face
#define BLOCK_BOTTOM_BOTTOMLEFT(x, y, z) glm::vec3(-0.5f + x, -0.5f + y, -0.5f + z)
#define BLOCK_BOTTOM_BOTTOMRIGHT(x, y, z)glm::vec3( 0.5f + x, -0.5f + y, -0.5f + z)
#define BLOCK_BOTTOM_TOPRIGHT(x, y, z)   glm::vec3( 0.5f + x, -0.5f + y,  0.5f + z)
#define BLOCK_BOTTOM_TOPLEFT(x, y, z)    glm::vec3(-0.5f + x, -0.5f + y,  0.5f + z)

//Textcoords of the texture
#define TEXTCOORD_BOTTOMLEFT glm::vec2(0.0f, 0.0f)
#define TEXTCOORD_BOTTOMRIGHT glm::vec2(0.125f , 0.0f)
#define TEXTCOORD_TOPLEFT glm::vec2(0.0f , 0.125f)
#define TEXTCOORD_TOPRIGHT glm::vec2(0.125f ,0.125f)

//Grass alas coords
#define GRASS_TOP_ALAS glm::vec2(0.0f , 0.875f)
#define GRASS_SIDE_ALAS glm::vec2(0.0f , 0.75f)
#define GRASS_BOTTOM_ALAS glm::vec2(0.0f , 0.625f)
//Sand alas coords
#define SAND_ALAS glm::vec2(0.5f , 0.875f)
//Rock alas coords
#define STONE_ALAS glm::vec2(0.125f , 0.875f)



// Block face normals
#define BLOCK_NORMAL_LEFT 	{-1.0f, 0.0f, 0.0f}
#define BLOCK_NORMAL_RIGHT 	{1.0f, 0.0f, 0.0f}
#define BLOCK_NORMAL_TOP 	{0.0f, 1.0f, 0.0f}
#define BLOCK_NORMAL_BOTTOM {0.0f, -1.0f, 0.0f}
#define BLOCK_NORMAL_FRONT 	{0.0f, 0.0f, 1.0f}
#define BLOCK_NORMAL_BACK 	{0.0f, 0.0f, -1.0f}



class Voxel
{
public:
	Voxel(enum Type _type, int id);
	Voxel() {};
	~Voxel();
	
	std::vector<VoxelVertex> getFace(Face face);
	Type getType() const { return m_type; }
	unsigned int getId() const { return m_id; }
private:
	enum Type m_type;
	unsigned int m_id;
};


