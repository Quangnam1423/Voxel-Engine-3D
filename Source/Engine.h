#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowConfig.h"
#include "Singleton.h"

#define ENGINE Engine::getInstance()

//void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Triangle;
class Rectangle;
class Cube;

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
	Cube* m_cube;
	float m_elapseTime;
};