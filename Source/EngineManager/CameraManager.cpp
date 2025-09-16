#include "CameraManager.h"
#include "../Objects/Camera.h"

CameraManager::CameraManager()
{
	m_camera = nullptr;
}

CameraManager::~CameraManager()
{
	if (m_camera != nullptr)
	{
		delete m_camera;
		m_camera = nullptr;
	}
}
