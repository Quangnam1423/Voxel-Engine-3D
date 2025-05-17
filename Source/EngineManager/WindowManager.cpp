#include "WindowManager.h"

WindowManager::WindowManager()
{
	m_window = nullptr;
	m_isFullScreen = false;
	m_windowSize = { 0 , 0 };
	m_windowPosition = { 0, 0 };
}

WindowManager::~WindowManager()
{
	if (m_window != nullptr)
	{
		delete m_window;
	}
	m_window = nullptr;
}

void WindowManager::render()
{
	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glfwSwapBuffers(m_window);
}

WindowSize WindowManager::getWindowSize()
{
	if (m_isFullScreen) {
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		return { mode->width, mode->height };
	} 
	else 
		return m_windowSize;
}

void WindowManager::setWindow(GLFWwindow* window)
{
	m_window = window;
	glfwMakeContextCurrent(m_window);
	glfwGetWindowSize(m_window, &m_windowSize.width, &m_windowSize.height);
	glfwGetWindowPos(m_window, &m_windowPosition.x, &m_windowPosition.y);
}

GLFWwindow* WindowManager::getWindow()
{
	return m_window;
}

void WindowManager::onFramebufferResized(int width, int height)
{
	glViewport(0, 0, width, height);
	glfwGetWindowSize(m_window, &m_windowSize.width, &m_windowSize.height);
}

void WindowManager::setFullScreen(bool value)
{
	if (value) {
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(   //
			m_window,			//
			monitor,			//
			0,					//  set window full screen
			0,					//
			mode->width,		//
			mode->height,		//
			mode->refreshRate	//
		);
		glViewport(0, 0, mode->width, mode->height);
	}
	else {
		glfwSetWindowMonitor(m_window, nullptr,         //
			m_windowPosition.x, m_windowPosition.y,		//  set window size back
			m_windowSize.width, m_windowSize.height,	//
			0
		);
	}
	m_isFullScreen = value;
}
