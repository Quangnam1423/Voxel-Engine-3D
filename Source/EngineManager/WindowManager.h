#pragma once
#include <glad/glad.h>	
#include <GLFW/glfw3.h>

#include "../WindowConfig.h"
#include "../Singleton.h"

#define WINDOW_MANAGER WindowManager::getInstance()

class WindowManager : public Singleton<WindowManager>
{
	friend class Singleton<WindowManager>;
public:
	WindowManager();
	~WindowManager();
	void render();
	WindowSize getWindowSize();

	void setWindow(GLFWwindow* window);
	GLFWwindow* getWindow();
	void onFramebufferResized(int width, int height);
	bool isFullScreen() { return m_isFullScreen; };
	void setFullScreen(bool value);

private:
	GLFWwindow* m_window;
	bool m_isFullScreen;

	WindowSize m_windowSize;
	WindowPosition m_windowPosition;
};