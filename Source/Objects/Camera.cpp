#include "Camera.h"

Camera::Camera()
{
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_target = glm::vec3(0.0f, 0.0f, 0.0f);
	m_direction = glm::vec3(0.0f, 0.0f, 0.0f);
	m_up = glm::vec3(0.0f, 0.0f, 0.0f);
	m_right = glm::vec3(0.0f, 0.0f, 0.0f);
	m_worldUp = glm::vec3(0.0f, 0.0f, 0.0f);
	m_yaw = YAW;
	m_pitch = PITCH;
	m_movementSpeed = SPEED;
	m_mouseSensitivity = SENSITIVITY;
	m_zoom = ZOOM;
	updateCameraVectors();
}

Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(m_position, m_target, m_up);
}

void Camera::processKeyboard(Direction direction, float deltaTime)
{

}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
}

void Camera::processMouseScroll(float yoffset)
{
	m_zoom = -(float)yoffset;
	if (m_zoom < 1.0f)
		m_zoom = 1.0f;
	else if (m_zoom > 45.0f)
		m_zoom = 45.0f;
}

float Camera::getZoom()
{
	return m_zoom;
}

glm::vec3 Camera::getPosition()
{
	return m_position;
}

void Camera::setPosition(glm::vec3 position)
{
	m_position = position;
	updateCameraVectors();
}

glm::vec3 Camera::getTarget()
{
	return m_target;
}

void Camera::setTarget(glm::vec3 target)
{
	m_target = target;
	updateCameraVectors();
}

glm::vec3 Camera::getWorldUp()
{
	return m_worldUp;
}

void Camera::setWorldUp(glm::vec3 worldUp)
{
	m_worldUp = worldUp;
	updateCameraVectors();	
}

void Camera::updateCameraVectors()
{
	glm::vec3 front(1.0f);
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_direction = glm::normalize(front);
	m_target = m_position + m_direction;
	m_right = glm::normalize(glm::cross(m_direction, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_direction));
}