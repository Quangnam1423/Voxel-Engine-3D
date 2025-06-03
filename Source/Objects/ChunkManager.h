#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <future> 

#define DISTANCE_TO_LOAD 8

class Chunk;
class Shader;

struct Tuple3DHasher {
    size_t operator()(const std::tuple<int, int, int>& t) const noexcept {
        size_t h1 = std::hash<int>{}(std::get<0>(t));
        size_t h2 = std::hash<int>{}(std::get<1>(t));
        size_t h3 = std::hash<int>{}(std::get<2>(t));

        size_t seed = 0;
        seed ^= h1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= h3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

class ChunkManager
{
public:

	ChunkManager(Shader* shader, GLuint textureID);
	~ChunkManager();
	std::tuple<int, int, int> worldToChunkCoord(const glm::vec3& pos) const;
	glm::vec3 chunkCoordToWorldPos(const std::tuple<int, int, int>& coord) const;
    void drawVisibleChunks();
	void updateVisibleChunks();
	void update(float delaTime);

private:
    void backgroundThread();

private:
	std::queue<std::tuple<int, int, int>> m_chunksToLoad;
	std::queue<std::tuple<int, int, int>> m_chunksToUnload;
	std::mutex m_mutex;
    std::mutex m_queueMutex;

	std::thread m_workerThread;

	bool m_running;

    std::unordered_map<std::tuple<int, int, int>, Chunk*, Tuple3DHasher> m_chunks;

    Shader* m_shader;
	GLuint m_textureID;
};

