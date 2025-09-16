#include "InputManager.h"
#include "../Objects/Camera.h"


InputManager::InputManager()
{
	glfwSetInputMode(WINDOW_MANAGER->getWindow(), GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
	int windowHeight = WINDOW_MANAGER->getWindowSize().height;
	int windowWidth = WINDOW_MANAGER->getWindowSize().width;
	glfwSetCursorPos(WINDOW_MANAGER->getWindow(), windowWidth / 2.0, windowHeight / 2.0);
	m_mousePos.x = windowWidth / 2.0;
	m_mousePos.y = windowHeight / 2.0;
	m_previewLastTimeMouseAtEdge = -1.0f;
	m_isMouseAtEdge = false;
	m_edgeDirection = EdgeDirection::None;
}

InputManager::~InputManager()
{
}

void InputManager::handleEvent()
{
	glfwPollEvents();
}

void InputManager::update(float deltaTime)
{
}

void InputManager::processInput(float deltaTime)
{
	GLFWwindow* window = WINDOW_MANAGER->getWindow();
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS)
	{
		if (WINDOW_MANAGER->isFullScreen() == false) {
			WINDOW_MANAGER->setFullScreen(true);
		}
		else
			WINDOW_MANAGER->setFullScreen(false);
	}
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		CM->getCamera()->processKeyboard(Direction::Forward, deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		CM->getCamera()->processKeyboard(Backward, deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		CM->getCamera()->processKeyboard(Left, deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		CM->getCamera()->processKeyboard(Right, deltaTime);
	}

	if (m_isMouseAtEdge && m_previewLastTimeMouseAtEdge != -1.0f) {
		float deltaTime = (float)glfwGetTime() - m_previewLastTimeMouseAtEdge;
		m_previewLastTimeMouseAtEdge = (float)glfwGetTime();
		float xoffset = 0, yoffset = 0;
		switch (m_edgeDirection) {
		case EdgeDirection::Left:  xoffset = deltaTime; break;
		case EdgeDirection::Right: xoffset = -deltaTime; break;
		case EdgeDirection::Top:   yoffset = -deltaTime; break;
		case EdgeDirection::Bottom:yoffset = deltaTime; break;
		default: break;
		}
		CM->getCamera()->processMouseMovement(xoffset, yoffset, true);
	}
}
