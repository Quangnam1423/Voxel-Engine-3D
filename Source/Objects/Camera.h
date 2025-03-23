#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Singleton.h"

enum class Direction
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

#define YAW -90.0f
#define PITCH 0.0f
#define SPEED 2.5f
#define SENSITIVITY 0.1f
#define ZOOM 45.0f

class Camera : public Singleton<Camera>
{
	friend class Singleton<Camera>;	
public:
	Camera();
	~Camera();

	glm::mat4 getViewMatrix();
	void processKeyboard(Direction direction, float deltaTime);
	void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void processMouseScroll(float yoffset);
	float getZoom();

	// Getters and Setters
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);

	glm::vec3 getTarget();
	void setTarget(glm::vec3 target);

	glm::vec3 getWorldUp();
	void setWorldUp(glm::vec3 worldUp);
private:
	glm::vec3 m_position;
	glm::vec3 m_target;
	glm::vec3 m_direction;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	float m_yaw;
	float m_pitch;
	float m_movementSpeed;
	float m_mouseSensitivity;
	float m_zoom;

private:
	void updateCameraVectors();
};

