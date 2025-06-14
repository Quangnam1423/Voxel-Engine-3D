#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowConfig.h"
#include "Singleton.h"

#define ENGINE Engine::getInstance()

class World;

class Engine : public Singleton<Engine>
{
	friend class Singleton<Engine>;
public:
	Engine();
	~Engine();
	void init();
	void run();
	void cleanup();

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
private:
	World* m_world;
	float m_elapseTime;
};