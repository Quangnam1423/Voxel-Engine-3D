#pragma once
#include <glad/glad.h>	
#include <GLFW/glfw3.h>

#include "../Singleton.h"

#define WINDOW_MANAGER WindowManager::getInstance()

class WindowManager : public Singleton<WindowManager>
{
	friend class Singleton<WindowManager>;
public:
	WindowManager();
	~WindowManager();
	void render();

	void setWindow(GLFWwindow* window);
	GLFWwindow* getWindow();
private:
	GLFWwindow* m_window;
};