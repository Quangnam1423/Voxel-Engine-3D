#include "Voxel.h"

Voxel::Voxel(Type type, int id)
{
	m_type = type;
	m_id = id;
}

Voxel::~Voxel()
{
}

std::vector<VoxelVertex> Voxel::getFace(Face face)
{
    std::vector<VoxelVertex> vertices;
    glm::vec2 texture_atlas_base_coords;

    switch (m_type)
    {
    case Type::GRASS:
        if (face == Face::TOP)
            texture_atlas_base_coords = GRASS_TOP_ALAS;
        else if (face == Face::BOTTOM)
            texture_atlas_base_coords = GRASS_BOTTOM_ALAS;
        else
            texture_atlas_base_coords = GRASS_SIDE_ALAS;
        break;
    case Type::SAND:
        texture_atlas_base_coords = SAND_ALAS; 
        break;
    case Type::STONE:
        texture_atlas_base_coords = STONE_ALAS; 
        break;
    case Type::WATER:
        break;
    case Type::AIR:

        return vertices;
    }


    unsigned int y = m_id / (16 * 16);
	unsigned int remain = m_id % (16 * 16);
	unsigned int z = remain / 16;
    unsigned int x = remain % 16;

    switch (face)
    {
    case Face::FRONT: 
        vertices.push_back({ BLOCK_FRONT_BOTTOMLEFT(x, y, z), BLOCK_NORMAL_FRONT, texture_atlas_base_coords + TEXTCOORD_BOTTOMLEFT });
        vertices.push_back({ BLOCK_FRONT_BOTTOMRIGHT(x, y, z), BLOCK_NORMAL_FRONT, texture_atlas_base_coords + TEXTCOORD_BOTTOMRIGHT });
        vertices.push_back({ BLOCK_FRONT_TOPRIGHT(x, y, z), BLOCK_NORMAL_FRONT,   texture_atlas_base_coords + TEXTCOORD_TOPRIGHT });
        vertices.push_back({ BLOCK_FRONT_TOPLEFT(x, y, z), BLOCK_NORMAL_FRONT,    texture_atlas_base_coords + TEXTCOORD_TOPLEFT });
        break;

    case Face::BACK: 
        vertices.push_back({ BLOCK_BACK_TOPLEFT(x, y, z),    BLOCK_NORMAL_BACK, texture_atlas_base_coords + TEXTCOORD_TOPLEFT });
        vertices.push_back({ BLOCK_BACK_TOPRIGHT(x, y, z),   BLOCK_NORMAL_BACK, texture_atlas_base_coords + TEXTCOORD_TOPRIGHT });
        vertices.push_back({ BLOCK_BACK_BOTTOMRIGHT(x, y, z), BLOCK_NORMAL_BACK, texture_atlas_base_coords + TEXTCOORD_BOTTOMRIGHT });
        vertices.push_back({ BLOCK_BACK_BOTTOMLEFT(x, y, z), BLOCK_NORMAL_BACK, texture_atlas_base_coords + TEXTCOORD_BOTTOMLEFT });
        break;

    case Face::RIGHT: 
        vertices.push_back({ BLOCK_RIGHT_BOTTOMLEFT(x, y, z), BLOCK_NORMAL_RIGHT, texture_atlas_base_coords + TEXTCOORD_BOTTOMLEFT });
        vertices.push_back({ BLOCK_RIGHT_BOTTOMRIGHT(x, y, z), BLOCK_NORMAL_RIGHT, texture_atlas_base_coords + TEXTCOORD_BOTTOMRIGHT });
        vertices.push_back({ BLOCK_RIGHT_TOPRIGHT(x, y, z),   BLOCK_NORMAL_RIGHT,  texture_atlas_base_coords + TEXTCOORD_TOPRIGHT });
        vertices.push_back({ BLOCK_RIGHT_TOPLEFT(x, y, z),    BLOCK_NORMAL_RIGHT,  texture_atlas_base_coords + TEXTCOORD_TOPLEFT });
        break;

    case Face::LEFT:
        vertices.push_back({ BLOCK_LEFT_BOTTOMLEFT(x, y, z), BLOCK_NORMAL_LEFT, texture_atlas_base_coords + TEXTCOORD_BOTTOMLEFT });
        vertices.push_back({ BLOCK_LEFT_BOTTOMRIGHT(x, y, z), BLOCK_NORMAL_LEFT, texture_atlas_base_coords + TEXTCOORD_BOTTOMRIGHT });
        vertices.push_back({ BLOCK_LEFT_TOPRIGHT(x, y, z),   BLOCK_NORMAL_LEFT, texture_atlas_base_coords + TEXTCOORD_TOPRIGHT });
        vertices.push_back({ BLOCK_LEFT_TOPLEFT(x, y, z),    BLOCK_NORMAL_LEFT, texture_atlas_base_coords + TEXTCOORD_TOPLEFT });
        break;

    case Face::TOP: 
        vertices.push_back({ BLOCK_TOP_BOTTOMLEFT(x, y, z), BLOCK_NORMAL_TOP,    texture_atlas_base_coords + TEXTCOORD_BOTTOMLEFT });
        vertices.push_back({ BLOCK_TOP_BOTTOMRIGHT(x, y, z), BLOCK_NORMAL_TOP,   texture_atlas_base_coords + TEXTCOORD_BOTTOMRIGHT });
        vertices.push_back({ BLOCK_TOP_TOPRIGHT(x, y, z),    BLOCK_NORMAL_TOP,    texture_atlas_base_coords + TEXTCOORD_TOPRIGHT });
        vertices.push_back({ BLOCK_TOP_TOPLEFT(x, y, z),     BLOCK_NORMAL_TOP,    texture_atlas_base_coords + TEXTCOORD_TOPLEFT });
        break;

    case Face::BOTTOM: 
        vertices.push_back({ BLOCK_BOTTOM_BOTTOMLEFT(x, y, z), BLOCK_NORMAL_BOTTOM, texture_atlas_base_coords + TEXTCOORD_BOTTOMLEFT });
        vertices.push_back({ BLOCK_BOTTOM_BOTTOMRIGHT(x, y, z), BLOCK_NORMAL_BOTTOM, texture_atlas_base_coords + TEXTCOORD_BOTTOMRIGHT });
        vertices.push_back({ BLOCK_BOTTOM_TOPRIGHT(x, y, z),   BLOCK_NORMAL_BOTTOM, texture_atlas_base_coords + TEXTCOORD_TOPRIGHT });  
        vertices.push_back({ BLOCK_BOTTOM_TOPLEFT(x, y, z),    BLOCK_NORMAL_BOTTOM, texture_atlas_base_coords + TEXTCOORD_TOPLEFT });
        break;
    }
    return vertices;
}
