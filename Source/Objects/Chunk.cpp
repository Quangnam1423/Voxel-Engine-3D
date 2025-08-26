#include "Chunk.h"

#include "Shader.h"
#include "ChunkMesh.h"
#include "Voxel.h"
#include "../EngineManager/CameraManager.h"
#include "Camera.h"

Chunk::Chunk()
	: m_position(0.0f), m_textureID(0), m_shader(nullptr), m_chunkMesh(nullptr),
	m_isReadyToDraw(false), m_isMeshReady(false)
{
	m_voxels.resize(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
}

Chunk::~Chunk()
{
	if (m_shader) {		
		delete m_shader;
		m_shader = nullptr;
	}

	if (m_chunkMesh) {
		delete m_chunkMesh;
		m_chunkMesh = nullptr;
	}

	for (auto& voxel : m_voxels) {
		delete voxel;
		voxel = nullptr;
	}
}

void Chunk::setupChunk()
{
	initChunk();
	m_chunkMesh = new ChunkMesh();

	for (int i = 0; i < m_voxels.size(); i++) {
		if (m_voxels[i] == nullptr) {
			continue;
		}
	}

	for (int z = 0; z < CHUNK_SIZE; z++)
	{
		for (int x = 0 ; x < CHUNK_SIZE; x++)
		{
			for (int y = 0; y < CHUNK_SIZE; y++)
			{
				unsigned int index = x + z * CHUNK_SIZE + y * CHUNK_SIZE * CHUNK_SIZE;
				
				if (y + 1 >= CHUNK_SIZE)
				{
					std::vector<VoxelVertex> topface = m_voxels[index]->getFace(Face::TOP);
					int count = static_cast<int>(m_vertices.size());
					m_vertices.insert(m_vertices.end(), topface.begin(), topface.end());
                    
					m_indices.push_back(count);
					m_indices.push_back(count + 1);
					m_indices.push_back(count + 2);
					m_indices.push_back(count);
					m_indices.push_back(count + 2);
					m_indices.push_back(count + 3);
				}

				if (y - 1 < 0)
				{
					std::vector<VoxelVertex> bottomface = m_voxels[index]->getFace(Face::BOTTOM);
					int count = static_cast<int>(m_vertices.size());
					m_vertices.insert(m_vertices.end(), bottomface.begin(), bottomface.end());
					m_indices.push_back(count);
					m_indices.push_back(count + 1);
					m_indices.push_back(count + 2);
					m_indices.push_back(count );
					m_indices.push_back(count + 2);
					m_indices.push_back(count + 3);
				}

				if (x + 1 >= CHUNK_SIZE) 
				{
					std::vector<VoxelVertex> bottomface = m_voxels[index]->getFace(Face::RIGHT);
					int count = static_cast<int>(m_vertices.size());
					m_vertices.insert(m_vertices.end(), bottomface.begin(), bottomface.end());
					m_indices.push_back(count);
					m_indices.push_back(count + 1);
					m_indices.push_back(count + 2);
					m_indices.push_back(count);
					m_indices.push_back(count + 2);
					m_indices.push_back(count + 3);
				}
				
				if(x - 1 < 0) 
				{
					std::vector<VoxelVertex> bottomface = m_voxels[index]->getFace(Face::LEFT);
					int count = static_cast<int>(m_vertices.size());
					m_vertices.insert(m_vertices.end(), bottomface.begin(), bottomface.end());
					m_indices.push_back(count);
					m_indices.push_back(count + 1);
					m_indices.push_back(count + 2);
					m_indices.push_back(count);
					m_indices.push_back(count + 2);
					m_indices.push_back(count + 3);
				}

				if (z + 1 >= CHUNK_SIZE) 
				{
					std::vector<VoxelVertex> bottomface = m_voxels[index]->getFace(Face::FRONT);
					int count = static_cast<int>(m_vertices.size());
					m_vertices.insert(m_vertices.end(), bottomface.begin(), bottomface.end());
					m_indices.push_back(count);
					m_indices.push_back(count + 1);
					m_indices.push_back(count + 2);
					m_indices.push_back(count);
					m_indices.push_back(count + 2);
					m_indices.push_back(count + 3);
				}

				if (z - 1 < 0) 
				{
					std::vector<VoxelVertex> bottomface = m_voxels[index]->getFace(Face::BACK);
					int count = static_cast<int>(m_vertices.size());
					m_vertices.insert(m_vertices.end(), bottomface.begin(), bottomface.end());
					m_indices.push_back(count);
					m_indices.push_back(count + 1);
					m_indices.push_back(count + 2);
					m_indices.push_back(count);
					m_indices.push_back(count + 2);
					m_indices.push_back(count + 3);
				}
			}
		}
	}
	m_isMeshReady = true;
	//m_chunkMesh->setupMesh(m_vertices, m_indices);
}

void Chunk::setupMesh()
{
	if (m_chunkMesh == nullptr)
	{
		m_chunkMesh = new ChunkMesh();
	}
	m_chunkMesh->setupMesh(m_vertices, m_indices);
	m_isReadyToDraw = true;
}

void Chunk::draw(glm::mat4 view, glm::mat4 projection) {
	if (!m_isReadyToDraw) {
		return;
	}
	glm::mat4 model(1.0f);
	model = glm::translate(model, m_position);
	m_shader->use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	m_shader->setInt("material.diffuse", 0);
	m_shader->setVec3("light.position", CM->getCamera()->getDirection());
	m_shader->setVec3("viewPos", CM->getCamera()->getPosition());
	m_shader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	m_shader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	m_shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	// material properties
	m_shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	m_shader->setFloat("material.shininess", 64.0f);
	m_chunkMesh->draw(*m_shader,model, view, projection);
}

void Chunk::initChunk()
{
	for (int z = 0; z < CHUNK_SIZE; z++)
	{
		for (int x = 0; x < CHUNK_SIZE; x++)
		{
			for (int y = 0; y < CHUNK_SIZE; y++)
			{
				unsigned int index = x + z * CHUNK_SIZE + y * CHUNK_SIZE * CHUNK_SIZE;
				m_voxels[index] = new Voxel(Type::GRASS,index);
			}
		}
	}
}