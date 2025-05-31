#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowConfig.h"
#include "Singleton.h"

#define ENGINE Engine::getInstance()

//void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Triangle;
class Rectangle;
class LightCube;
class ColorCube;
class WoodBox;
class Cube;
class Shader;
class Model;

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
	Model* m_model;
	Model* m_model2;
	Shader* m_shader;
	Cube* m_normalCube;
	LightCube* m_lightCube;
	ColorCube* m_colorCube;
	WoodBox* m_woodBox;
	float m_elapseTime;
};