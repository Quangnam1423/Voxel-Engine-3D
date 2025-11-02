#pragma once


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <queue>
#include <future>
#include <unordered_map>

#define DISTANCE_TO_LOAD 10

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
    ChunkManager();
	~ChunkManager();

	void Update(float detlaTime, const glm::vec3& cameraPosition);
    void DrawVisibleChunks(const glm::mat4& view, const glm::mat4& projection);
    void Stop();
	void setShader(Shader* shader) { m_shader = shader; }
private:
    void initWorkerThread();
    void updateChunkMap();
private:
    // map to manage chunks
	std::unordered_map<std::tuple<int, int, int>, Chunk*, Tuple3DHasher> m_chunks;
    // modify std::mutex -> std::shared_mutex for now
	std::shared_mutex m_chunksMapMutex; 
    // chunk load queue and mutex
    std::queue <std::tuple<int, int, int> > m_chunkLoadQueue;
	std::mutex m_loadQueueMutex;
    // chunk unload queue and mutex
    std::queue <std::tuple<int, int, int> > m_chunkUnloadQueue;
	std::mutex m_unloadQueueMutex;

    std::condition_variable m_cvLoadChunk;
	std::condition_variable m_cvUnloadChunk;
    std::atomic<bool> m_running;

    // shader and 
    Shader* m_shader;
	glm::vec3 m_lastCameraPos;
};