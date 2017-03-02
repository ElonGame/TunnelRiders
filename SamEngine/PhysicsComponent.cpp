#include "stdafx.h"
#include "PhysicsComponent.h"
#include "GL\GLM\GTX\transform.hpp"
#include "GL\GLM\GTX\rotate_vector.hpp"
#include "Message.h"
#include "MoveMessage.h"
#include <iostream>


PhysicsComponent::PhysicsComponent(GameObject* gob) :
	GameObjectComponent("physics", gob),
	_velocity(0, 0, 0),
	_maxSpeed(9999999999),
	_friction(0)
{
}


PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Start()
{
	_gameObject->RegisterListener("move", this);
}

void PhysicsComponent::Update(double deltaTime)
{
}

void PhysicsComponent::OnMessage(Message * msg)
{
	if (msg->GetMessageType() == "move")
	{
		MoveMessage* mm = (MoveMessage*)msg;
		glm::vec3 dir = mm->GetDirection();
		float speed = mm->GetSpeed();
		if (dir.x == 1)
		{
			_acceleration.x = speed;
		}
		if (dir.x == -1)
		{
			_acceleration.x = -speed;
		}
		if (dir.y == 1)
		{
			_acceleration.y = speed;
		}
		if (dir.y == -1)
		{
			_acceleration.y = -speed;
		}
	}
}

void PhysicsComponent::End()
{
}

void PhysicsComponent::LimitToMaximumSpeed(float max)
{ 
	if (glm::length(_velocity) > max)
	{
		_velocity = glm::normalize(_velocity) * max;
	}
}
