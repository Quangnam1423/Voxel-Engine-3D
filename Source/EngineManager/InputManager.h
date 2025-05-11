#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "CameraManager.h"
#include "../Objects/Camera.h"
#include "WindowManager.h"
#include "../Singleton.h"
#include "../movement.h"

enum class EdgeDirection {
	None,
	Left,
	Right,
	Top,
	Bottom
};

#define INPUT_MANAGER InputManager::getInstance()

class InputManager : public Singleton<InputManager>
{
friend class Singleton<InputManager>;
public:	
	InputManager();
	~InputManager();

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
		WINDOW_MANAGER->onFramebufferResized(width, height);
	};

	static void mouseCallback(GLFWwindow* window, double xPos, double yPos) {
		float xpos = static_cast<float> (xPos);
		float ypos = static_cast<float>(yPos);

		float windowHeight = (float)WINDOW_MANAGER->getWindowSize().height;
		float windowWidth = (float)WINDOW_MANAGER->getWindowSize().width;
		
		const float EDGE_THRESHOLD = 10.0f;

		bool atLeft = xpos <= EDGE_THRESHOLD;
		bool atRight = xpos >= windowWidth - EDGE_THRESHOLD;
		bool atTop = ypos <= EDGE_THRESHOLD;
		bool atBottom = ypos >= windowHeight - EDGE_THRESHOLD;

		EdgeDirection dir = EdgeDirection::None;
		if (xPos <= EDGE_THRESHOLD) dir = EdgeDirection::Left;
		else if (xPos >= windowWidth - EDGE_THRESHOLD) dir = EdgeDirection::Right;
		else if (yPos <= EDGE_THRESHOLD) dir = EdgeDirection::Top;
		else if (yPos >= windowHeight - EDGE_THRESHOLD) dir = EdgeDirection::Bottom;

		if ((atLeft || atRight || atTop || atBottom)) {
			INPUT_MANAGER->setMouseAtEdge(true);
			INPUT_MANAGER->setPreviewAtEdge((float)glfwGetTime());
			INPUT_MANAGER->setEdgeDirection(dir);
		}
		else {
			INPUT_MANAGER->setMouseAtEdge(false);
			INPUT_MANAGER->setPreviewAtEdge(-1.0f);
			INPUT_MANAGER->setEdgeDirection(EdgeDirection::None);
		}
	};

	void handleEvent();
	void update(float deltaTime);
	void processInput(float deltaTime);
	bool isMouseAtEdge() { return m_isMouseAtEdge; };
	void setMouseAtEdge(bool value) { m_isMouseAtEdge = value; };
	void setPreviewAtEdge(float previewTime) { m_previewLastTimeMouseAtEdge = previewTime; };
	float getPreviewTime() { return m_previewLastTimeMouseAtEdge; };
	EdgeDirection getEdgeDirection() const { return m_edgeDirection; }
	void setEdgeDirection(EdgeDirection dir) { m_edgeDirection = dir; }
private:
	MousePosition m_mousePos;
	bool m_isMouseAtEdge;
	float m_previewLastTimeMouseAtEdge;
	EdgeDirection m_edgeDirection;

};