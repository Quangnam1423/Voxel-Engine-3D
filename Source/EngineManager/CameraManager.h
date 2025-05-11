#pragma once

#include "../Singleton.h"

#define CM CameraManager::getInstance()

class Camera;

class CameraManager : public Singleton<CameraManager>
{
	friend class Singleton<CameraManager>;
public:
	CameraManager();
	~CameraManager();
	
	void setCamera(Camera* camera) { m_camera = camera; };
	Camera* getCamera() { return m_camera; };
private:
	Camera* m_camera;
};

