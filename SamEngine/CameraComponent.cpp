#pragma once
#include "CameraComponent.h"


CameraComponent::CameraComponent(GameObject* parent) : GameObjectComponent("camera", parent)
{
	SetPerspective(75.0f, 1280.0f, 720.0f, 0.01f, 10000.0f);
	SetView(glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
	SetOrtho(1280.0f, 720.0f);
}


CameraComponent::~CameraComponent()
{
}

glm::mat4 CameraComponent::ViewProjectionMatrix()
{
	if (_changed)
		_projectionViewMatrix =  _perspective * _view;
	return _projectionViewMatrix;
}

void CameraComponent::SetPerspective(float fov, float width, float height, float near_plane, float far_plane)
{
	_fov = fov;
	_width = width;
	_height = height;
	_near = near_plane;
	_far = far_plane;
	_perspective = glm::perspective(_fov, _width / _height, _near, _far);
	_changed = true;
}

void CameraComponent::SetView(glm::vec3 forward, glm::vec3 up)
{
	_forward = forward;
	_up = up;

	_position = _gameObject->GetPosition();
	_angle = _gameObject->GetAngle();

	glm::mat4 rotation = glm::rotate(_angle.x, glm::vec3(1, 0, 0)) *
						glm::rotate(_angle.y, glm::vec3(0, 1, 0)) *
						glm::rotate(_angle.z, glm::vec3(0, 0, 1));
	_lookAt = glm::vec3(rotation * glm::vec4(_forward, 1));

	_lookAt = _position + _lookAt;
	
	_view = glm::lookAt(_position, _lookAt, _up);
	_changed = true;
}

void CameraComponent::SetOrtho(float width, float height)
{
	_width = width;
	_height = height;
	_orthographic = glm::ortho(0.0f, _width, _height, 0.0f, 0.1f, 1.1f);
}

void CameraComponent::Start()
{
	
}

void CameraComponent::Update(double deltaTime)
{
	if (_position != _gameObject->GetPosition() ||
		_angle != _gameObject->GetAngle())
	{
		SetView(_forward, _up);
	}
}

void CameraComponent::End()
{
	
}

void CameraComponent::OnMessage(Message* message)
{
	
}
