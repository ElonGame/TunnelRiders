#include "Camera.h"


Camera::Camera() : GameObject("camera")
{
	_camera = new CameraComponent(this);
}

Camera::Camera(float fov, float width, float height, float near, float far, glm::vec3 forward, glm::vec3 up)
	: GameObject("camera")
{
	_camera = new CameraComponent(this);
	_forward = forward;
	_camera->SetPerspective(fov, width, height, near, far);
	_camera->SetView(forward, up);
}


Camera::~Camera()
{
}

void Camera::Start()
{
	GameObject::Start();
}

void Camera::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}

void Camera::End()
{
	GameObject::End();
}

void Camera::Reset()
{
	GameObject::Reset();
}
