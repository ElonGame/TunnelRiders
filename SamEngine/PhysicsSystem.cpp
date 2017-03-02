#pragma once
#include "PhysicsSystem.h"
#include "GameObject.h"
#include "PhysicsComponent.h"


PhysicsSystem::PhysicsSystem()
{
}


PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::Process(std::vector<GameObject*>& list, double deltaTime)
{
	for (GameObject* obj : list)
	{
		if (PhysicsComponent* physicsComponent = (PhysicsComponent*)(obj->GetComponent("physics")))
		{
			physicsComponent->SetVelocity(physicsComponent->GetVelocity() + 
										  ((physicsComponent->GetAcceleration() - 
											  (physicsComponent->GetVelocity() * physicsComponent->GetFriction()))
											  * (float)deltaTime));

			physicsComponent->SetObjectPosition(physicsComponent->GetObjectPosition() + 
												(physicsComponent->GetVelocity() * (float)deltaTime));

			physicsComponent->LimitToMaximumSpeed(physicsComponent->GetMaxSpeed());
		}
	}
}
