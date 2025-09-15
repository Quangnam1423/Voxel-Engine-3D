#include "ChunkManager.h"

//#include "ChunkManager.h"
//#include "Shader.h"
//#include "Chunk.h"
//#include "../EngineManager/CameraManager.h"
//#include "../EngineManager/WindowManager.h"
//#include "Camera.h"
//
//#include <unordered_set>
#include "../EngineManager/ResourceManager.h"
#include "Chunk.h"
#include "Shader.h"

ChunkManager::ChunkManager()
{
	m_shader = NULL;
	m_running = true;
	// initialize thread to load chunks and unload chunks.
	// for now, we will not use multithreading to load chunks.
	m_running = true;
	std::thread loadChunkThread([this] {
		std::unique_lock<std::mutex> lock(m_loadQueueMutex);
		while (true)
		{
			m_cvLoadChunk.wait(lock, [this] {return !m_chunkLoadQueue.empty() || !m_running;} );
			if (!m_running) {
				break;
			}

			while (!m_chunkLoadQueue.empty())
			{
				std::tuple<int, int, int> chunkPos = m_chunkLoadQueue.front();
				m_chunkLoadQueue.pop();

				Chunk* newChunk = nullptr;
				{
					newChunk = new Chunk();
					newChunk->setShader(m_shader);
					newChunk->setPosition(
						glm::vec3(std::get<0>(chunkPos) * 16.0f,
							std::get<1>(chunkPos) * 16.0f,
							std::get<2>(chunkPos) * 16.0f)
					);
				}
				// load chunk data before insert into map.
				std::thread setupThread([newChunk]() {
					newChunk->setupChunk();
				});
				setupThread.join(); // wait until chunk data is prepared.

				// insert new chunk to map
				{
					std::lock_guard<std::mutex> chunksLock(m_chunksMapMutex);
					m_chunks[chunkPos] = newChunk;
				}
			}
		}
	});
	loadChunkThread.detach();

	//--------------------------UNLOAD_CHUNKS__THREAD------------------------------

	std::thread unloadChunkThread([this] {
		std::unique_lock<std::mutex> lock(m_unloadQueueMutex);
		while (true)
		{
			m_cvUnloadChunk.wait(lock, [this] {return !m_chunkUnloadQueue.empty() || !m_running;  });
			if (!m_running) {
				break;
			}

			while (!m_chunkUnloadQueue.empty())
			{
				std::tuple<int, int, int> chunkPos = m_chunkUnloadQueue.front();
				m_chunkUnloadQueue.pop();

				{
					std::lock_guard<std::mutex> chunkLock(m_chunksMapMutex);
					if (m_chunks.find(chunkPos) != m_chunks.end()) {
						Chunk* chunk = m_chunks[chunkPos];
						delete chunk;
						m_chunks.erase(chunkPos);
					}
				}
			}
		}
	});
	unloadChunkThread.detach();
}

ChunkManager::~ChunkManager()
{
	Stop();
	for (auto& pair : m_chunks) {
		delete pair.second;
	}
	m_chunks.clear();

	if (m_shader != NULL) {
		delete m_shader;
		m_shader = nullptr;
	}
}

void ChunkManager::Update(float deltaTime, const glm::vec3& cameraPosition)
{
	float x = cameraPosition.x - m_lastCameraPos.x;
	float y = cameraPosition.y - m_lastCameraPos.y;
	float z = cameraPosition.z - m_lastCameraPos.z;
	if (sqrt(x * x + y * y + z * z) > 1.0f) {
		// init new chunk load around the camera position
		int r2 = DISTANCE_TO_LOAD * DISTANCE_TO_LOAD;
		for (int dx = -DISTANCE_TO_LOAD; dx <= DISTANCE_TO_LOAD; dx++)
		{
			int dx2 = dx * dx;
			int dzMax = static_cast<int>(std::floor(std::sqrt((double)r2 - dx2)));

			for (int dz = -dzMax; dz <= dzMax; dz++)
			{
				std::tuple<int, int, int> chunkPos = std::make_tuple(
					static_cast<int>(std::floor(cameraPosition.x / 16.0f)) + dx,
					0, // y is always 0 for now.
					static_cast<int>(std::floor(cameraPosition.z / 16.0f)) + dz
				);
				// if chunk not exist, add to load queue
				{
					std::lock_guard<std::mutex> lock(m_chunksMapMutex);
					if (m_chunks.find(chunkPos) != m_chunks.end()) {
						continue;
					}
				}
				// add to load queue
				{
					std::lock_guard<std::mutex> lock(m_loadQueueMutex);
					m_chunkLoadQueue.push(chunkPos);
				}
			}
		}
		m_cvLoadChunk.notify_one();
//---------------------------------------END_LOAD_NEW_CHUNKS---------------------------------



		// get current chunk positions in chunks map
		std::vector<std::tuple<int, int, int>> CurrentChunkPosition;
		{
			std::lock_guard<std::mutex> chunksMapLock(m_chunksMapMutex);
			CurrentChunkPosition.reserve(m_chunks.size());
			for (auto& pair : m_chunks)
			{
				CurrentChunkPosition.push_back(pair.first);
			}
		}
		// check which chunk need to unload
		{
			for (auto& chunkPos : CurrentChunkPosition)
			{
				int cx = std::get<0>(chunkPos);
				int cz = std::get<2>(chunkPos);
				int camChunkX = static_cast<int>(std::floor(cameraPosition.x / 16.0f));
				int camChunkZ = static_cast<int>(std::floor(cameraPosition.z / 16.0f));
				int dx = cx - camChunkX;
				int dz = cz - camChunkZ;
				if (dx * dx + dz * dz > r2)
				{
					// add to unload queue
					{
						std::lock_guard<std::mutex> lock(m_unloadQueueMutex);
						m_chunkUnloadQueue.push(chunkPos);
					}
				}
			}
			m_cvUnloadChunk.notify_one();
		} // end if stage of update chunks in case that camera moved too far.
	}
	// ----------------------------------------END_UNLOAD_FAR_CHUNKS---------------------------------

	// lock m_chunks and load chunk.
	{
		std::lock_guard<std::mutex> lock(m_chunksMapMutex);
		for (auto& pair : m_chunks)
		{
			Chunk* chunk = pair.second;
			if (chunk->isMeshReady() && !chunk->isReadyToDraw()) {
				if (chunk->getTexture() == -1) {
					chunk->setTexture(DATA->getTexture("Resource/Texture/blocks4.png"));
				}
				chunk->setupMesh();
			}
		}
	}
	// end the function
	return;
}

void ChunkManager::DrawVisibleChunks(const glm::mat4& view, const glm::mat4& projection)
{
	// draw all chunks that are ready to draw
	{
		std::lock_guard<std::mutex> lock(m_chunksMapMutex);
		for (auto& pair : m_chunks)
		{
			Chunk* chunk = pair.second;
			if (chunk->isReadyToDraw())
			{
				chunk->draw(view, projection);
			}
		}
	}
}


/// <summary>
/// - Load chunk when the first time init the chunk manager.
/// first time init, we will load chunks around the camera position.
/// </summary>
/// <param name="cameraPosition"></param>
void ChunkManager::Init(const glm::vec3& cameraPosition)
{
	// for now, we are loading chunks that has depth = 0.
	// that mean y default = 0.
	int x = static_cast<int>(floor(cameraPosition.x)) / 16;
	int y = static_cast<int>(floor(cameraPosition.y)) / 16;
	int z = static_cast<int>(floor(cameraPosition.z)) / 16;

	int r2 = DISTANCE_TO_LOAD * DISTANCE_TO_LOAD;
	for (int dx = -DISTANCE_TO_LOAD; dx <= DISTANCE_TO_LOAD; dx++)
	{
		int dx2 = dx * dx;
		int dzMax = static_cast<int>(std::floor(std::sqrt((double)r2 - dx2)));

		for (int dz = -dzMax; dz <= dzMax; dz++)
		{
			std::tuple<int, int, int> chunkPos = std::make_tuple(
				static_cast<int>(std::floor(cameraPosition.x / 16.0f)) + dx,
				0, // y is always 0 for now.
				static_cast<int>(std::floor(cameraPosition.z / 16.0f)) + dz
			);

			// add new chunk pos into the loadChunkQueue
			{
				std::lock_guard<std::mutex> lock(m_loadQueueMutex);
				m_chunkLoadQueue.push(chunkPos);
			}
		}
	}
	m_cvLoadChunk.notify_one();

	//for (int i = -DISTANCE_TO_LOAD; i <= DISTANCE_TO_LOAD; i++)
	//{
	//	for (int j = -DISTANCE_TO_LOAD; j <= DISTANCE_TO_LOAD; j++)
	//	{
	//		int chunkX = x + i;
	//		int chunkY = 0; // y is always 0 for now.
	//		int chunkZ = z + j;
	//		std::tuple<int, int, int> chunkPos = std::make_tuple(chunkX, chunkY, chunkZ);
	//		{
	//			std::lock_guard<std::mutex> lock(m_loadQueueMutex);
	//			m_chunkLoadQueue.push(chunkPos);
	//		}
	//	}
	//}
	//m_cvLoadChunk.notify_one();
	return;
}

void ChunkManager::Stop()
{
	m_running = false;
}
