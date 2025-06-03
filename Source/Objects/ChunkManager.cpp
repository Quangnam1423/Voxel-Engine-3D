#include "ChunkManager.h"
#include "Shader.h"
#include "Chunk.h"
#include "../EngineManager/CameraManager.h"
#include "../EngineManager/WindowManager.h"
#include "Camera.h"

#include <unordered_set>


ChunkManager::ChunkManager(Shader* shader, GLuint textureID)
{
	m_shader = shader;
	m_textureID = textureID;
	m_running = true;
	m_workerThread = std::thread(&ChunkManager::backgroundThread, this);
}

ChunkManager::~ChunkManager()
{
	m_running = false;
	if (m_workerThread.joinable())
		m_workerThread.join();

	for (auto& pair : m_chunks) {
		delete pair.second;
	}
	m_chunks.clear();
}

std::tuple<int, int, int> ChunkManager::worldToChunkCoord(const glm::vec3& pos) const {
	return {
		static_cast<int>(std::floor(pos.x / CHUNK_SIZE)),
		static_cast<int>(std::floor(pos.y / CHUNK_SIZE)),
		static_cast<int>(std::floor(pos.z / CHUNK_SIZE))
	};
}

glm::vec3 ChunkManager::chunkCoordToWorldPos(const std::tuple<int, int, int>& coord) const {
	return glm::vec3(
		std::get<0>(coord) * CHUNK_SIZE,
		std::get<1>(coord) * CHUNK_SIZE,
		std::get<2>(coord) * CHUNK_SIZE
	);
}

void ChunkManager::update(float deltaTime)
{
	auto cameraChunkPos = worldToChunkCoord(CM->getCamera()->getPosition());
	std::unordered_set<std::tuple<int, int, int>, Tuple3DHasher> requiredChunks;

	// First gather all required chunks without locking
	for (int x = -DISTANCE_TO_LOAD; x <= DISTANCE_TO_LOAD; ++x) {
		for (int y = -DISTANCE_TO_LOAD; y <= DISTANCE_TO_LOAD; ++y) {
			auto chunkPos = std::make_tuple(
				std::get<0>(cameraChunkPos) + x,
				std::get<1>(cameraChunkPos) + y,
				0
			);
			requiredChunks.insert(chunkPos);
		}
	}

	std::vector<std::tuple<int, int, int>> chunksToLoad;
	std::vector<std::tuple<int, int, int>> chunksToUnload;

	// Then use a single lock section to check what needs to be loaded/unloaded
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		// Check what chunks need to be loaded
		for (const auto& chunkPos : requiredChunks) {
			if (m_chunks.find(chunkPos) == m_chunks.end()) {
				chunksToLoad.push_back(chunkPos);
			}
		}

		// Check what chunks need to be unloaded
		for (auto it = m_chunks.begin(); it != m_chunks.end(); ++it) {
			if (requiredChunks.find(it->first) == requiredChunks.end()) {
				chunksToUnload.push_back(it->first);
			}
		}
	}

	// Finally, lock the queue mutex to update the work queues
	{
		std::lock_guard<std::mutex> qLock(m_queueMutex);
		for (const auto& pos : chunksToLoad) {
			m_chunksToLoad.push(pos);
		}
		for (const auto& pos : chunksToUnload) {
			m_chunksToUnload.push(pos);
		}
	}
}


void ChunkManager::drawVisibleChunks()
{

	std::lock_guard<std::mutex> lock(m_mutex);
	glm::mat4 view = CM->getCamera()->getViewMatrix();
	glm::vec3 cameraPosition = CM->getCamera()->getPosition();
	float aspect = (float)WINDOW_MANAGER->getWindowSize().width / (float)WINDOW_MANAGER->getWindowSize().height;
	glm::mat4 projection = glm::perspective(glm::radians(CM->getCamera()->getZoom()), aspect, 0.1f, 500.f);

	for (auto& [pos, chunks] : m_chunks) {
		std::cout << "drawing chunk at: " << std::get<0>(pos) << ", " << std::get<1>(pos) << ", " << std::get<2>(pos) << std::endl;
		chunks->draw(view, projection);
	}
}

void ChunkManager::updateVisibleChunks()
{
}

void ChunkManager::backgroundThread()
{
	while (m_running) {
		// Process a batch of work to avoid holding locks for too long
		std::vector<std::tuple<int, int, int>> chunksToProcess;
		std::vector<std::tuple<int, int, int>> chunksToRemove;

		// First get work items from the queue with minimal locking
		{
			std::lock_guard<std::mutex> queueLock(m_queueMutex);

			// Get chunks to load (limited batch size)
			const size_t maxBatchSize = 5;  // Adjust based on performance
			size_t count = 0;
			while (!m_chunksToLoad.empty() && count < maxBatchSize) {
				chunksToProcess.push_back(m_chunksToLoad.front());
				m_chunksToLoad.pop();
				count++;
			}

			// Get chunks to unload
			count = 0;
			while (!m_chunksToUnload.empty() && count < maxBatchSize) {
				chunksToRemove.push_back(m_chunksToUnload.front());
				m_chunksToUnload.pop();
				count++;
			}
		}

		// Process new chunks outside of locks
		std::vector<std::pair<std::tuple<int, int, int>, Chunk*>> newChunks;
		for (const auto& coord : chunksToProcess) {
			Chunk* chunk = new Chunk();
			glm::vec3 worldPos = chunkCoordToWorldPos(coord);
			chunk->setPosition(worldPos);
			chunk->setShader(m_shader);
			chunk->setTexture(m_textureID);
			newChunks.emplace_back(coord, chunk);
		}

		// Now update the main chunk map
		if (!newChunks.empty() || !chunksToRemove.empty()) {
			std::lock_guard<std::mutex> mapLock(m_mutex);

			// Add newly created chunks
			for (auto& [coord, chunk] : newChunks) {
				m_chunks[coord] = chunk;
			}

			// Remove chunks scheduled for deletion
			for (const auto& coord : chunksToRemove) {
				auto it = m_chunks.find(coord);
				if (it != m_chunks.end()) {
					delete it->second;
					m_chunks.erase(it);
				}
			}
		}

		// If no work was done, sleep to avoid busy waiting
		if (chunksToProcess.empty() && chunksToRemove.empty()) {
			std::this_thread::sleep_for(std::chrono::milliseconds(50));  // Longer sleep when idle
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(5));   // Short sleep between batches
		}
	}
}
