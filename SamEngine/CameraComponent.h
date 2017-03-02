#pragma once
#include "GameObjectComponent.h"
#include "GameObject.h"

// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"
#include "GL\GLM\gtx\rotate_vector.hpp"
#include "GL\GLM\gtx\transform.hpp"

class CameraComponent :
	public GameObjectComponent
{
public:
	CameraComponent(GameObject* parent);
	~CameraComponent();

	virtual void Start();
	virtual void Update(double deltaTime);
	virtual void End();
	virtual void OnMessage(Message* message);

	glm::mat4 ViewProjectionMatrix();

	void SetPerspective(float fov, float width, float height, float near_plane, float far_plane);
	glm::mat4 Perspective() const { return _perspective; }
	void SetView(glm::vec3 forward, glm::vec3 up);
	glm::mat4 View() const { return _view; }
	void SetOrtho(float width, float height);
	glm::mat4 Orthographic() const { return _orthographic; }

	void SetFov(float fov) { SetPerspective(_fov, _width, _height, _near, _far); }
	float Fov() const { return _fov; }
	void SetDimensions(float width, float height) { SetPerspective(_fov, width, height, _near, _far); SetOrtho(width, height); }
	float Width() const { return _width; }
	float Height() const { return _height; }
	void SetClippingPlanes(float near_plane, float far_plane) { SetPerspective(_fov, _width, _height, near_plane, far_plane); }
	float Near() const { return _near; }
	float Far() const { return _far; }

	void LookAt(glm::vec3 lookAt) { _forward = lookAt; _lookAt = lookAt; SetView(_forward, _up); }
	glm::vec3 LookingAt() const { return _lookAt; }
	void Up(glm::vec3 up) { _up = up; SetView(_lookAt, _up); }
	glm::vec3 GetUp() const { return _up; }

protected:
	glm::mat4 _projectionViewMatrix;
	glm::mat4 _perspective;
	glm::mat4 _view;
	glm::mat4 _orthographic;

	float _fov;
	float _width;
	float _height;
	float _near;
	float _far;

	glm::vec3 _forward;
	glm::vec3 _lookAt;
	glm::vec3 _up;

	glm::vec3 _position;
	glm::vec3 _angle;

private:
	bool _changed;
};

