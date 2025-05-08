#include "WindowManager.h"

WindowManager::WindowManager()
{
	m_window = nullptr;
}

WindowManager::~WindowManager()
{
}

void WindowManager::render()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glfwSwapBuffers(m_window);
}

void WindowManager::setWindow(GLFWwindow* window)
{
	m_window = window;
	glfwMakeContextCurrent(m_window);
}

GLFWwindow* WindowManager::getWindow()
{
	return m_window;
}
