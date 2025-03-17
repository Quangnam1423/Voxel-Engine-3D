#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Singleton.h"

#define INPUT_MANAGER InputManager::getInstance()

class InputManager : public Singleton<InputManager>
{
friend class Singleton<InputManager>;
public:	
	InputManager();
	~InputManager();

	void handleEvent();
	void processInput(GLFWwindow* window);
};