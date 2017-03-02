#pragma once
#include "GameObjectComponent.h"
#include "GameObject.h"
// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"


class PhysicsComponent
	: public GameObjectComponent
{
public:
	PhysicsComponent(GameObject* gob);
	virtual ~PhysicsComponent();

	glm::vec3 GetVelocity()	const { return _velocity; }
	void SetVelocity(glm::vec3 v) { _velocity = v; }

	glm::vec3 GetAcceleration() const { return _acceleration; }
	void SetAcceleration(glm::vec3 v) { _acceleration = v; }

	float GetMaxSpeed()	const { return _maxSpeed; }
	void SetMaxSpeed(float f) { _maxSpeed = f; }

	float GetFriction()	const { return _friction; }
	void SetFriction(float f) { _friction = f; }

	virtual void Start();

	// Main update function (called every frame)
	virtual void Update(double deltaTime);

	// Message handler (called when message occurs)
	virtual void OnMessage(Message* msg);

	// Shutdown function -- called when parent object is destroyed
	virtual void End();

	void LimitToMaximumSpeed(float max);
	glm::vec3 GetObjectPosition() { return _gameObject->GetLocalPosition(); }
	void SetObjectPosition(glm::vec3 v) { _gameObject->SetPosition(v); }


protected:
	glm::vec3 _velocity;
	glm::vec3 _acceleration;
	float _maxSpeed;
	float _friction;

};

