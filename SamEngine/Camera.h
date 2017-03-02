#pragma once
#include "GameObject.h"
#pragma once
#include "Components.h"

// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"
#include "GL\GLM\gtx\rotate_vector.hpp"

class Camera :
	public GameObject
{
public:
	Camera();
	Camera(float fov, float width, float height, float near, float far, glm::vec3 forward, glm::vec3 up);
	virtual ~Camera();

	virtual void Start();
	virtual void Update(double deltaTime);
	virtual void OnMessage(Message* msg) { BroadcastMessage(msg); }
	virtual void End();
	virtual void Reset();

	glm::mat4 GetViewProjectionMatrix() const { return _camera->ViewProjectionMatrix(); }
	glm::mat4 GetViewMatrix() const { return _camera->View(); }
	glm::mat4 GetProjectionMatrix() const { return _camera->Perspective(); }
	glm::mat4 GetOrthoMatrix() const { return _camera->Orthographic(); }

protected:
	CameraComponent* _camera;
	glm::vec3 _forward;
};

