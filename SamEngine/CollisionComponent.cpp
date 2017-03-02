#pragma once
#include "CollisionComponent.h"
#include "BoxColliderComponent.h"
#include "CircleColliderComponent.h"
#include "GameObject.h"


CollisionComponent::CollisionComponent(GameObject* gob) 
	: GameObjectComponent("collision", gob),
	_collisionMatrix(0),
	_collisionID(0),
	_enabled(true)
{

}


CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::Start()
{

}

void CollisionComponent::Update(double deltaTime)
{

}

void CollisionComponent::OnMessage(Message* msg)
{

}

void CollisionComponent::End()
{

}

bool CollisionComponent::BoxCircleCollision(BoxColliderComponent * a , CircleColliderComponent * b)
{
	float closestX = glm::clamp(b->Center().x, a->Center().x - (a->Size().x / 2.0f), a->Center().x + (a->Size().x / 2.0f));
	float closestY = glm::clamp(b->Center().y, a->Center().y + (a->Size().y / 2.0f), a->Center().y - (a->Size().y / 2.0f));

	float distanceX = b->Center().x - closestX;
	float distanceY = b->Center().y - closestY;

	float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
	return distanceSquared < (b->Radius() * b->Radius());
}

bool CollisionComponent::BoxBoxCollision(BoxColliderComponent * a, BoxColliderComponent * b)
{
	float a_xMax = a->Center().x + (a->Size().x / 2.0f);
	float b_xMax = b->Center().x + (b->Size().x / 2.0f);
	float a_xMin = a->Center().x - (a->Size().x / 2.0f);
	float b_xMin = b->Center().x - (b->Size().x / 2.0f);

	if (a_xMax < b_xMin) return false;
	if (a_xMin > b_xMax) return false;

	float a_yMax = a->Center().y + (a->Size().y / 2.0f);
	float b_yMax = b->Center().y + (b->Size().y / 2.0f);
	float a_yMin = a->Center().y - (a->Size().y / 2.0f);
	float b_yMin = b->Center().y - (b->Size().y / 2.0f);

	if (a_yMax < b_yMin) return false;
	if (a_yMin > b_yMax) return false;

	float a_zMax = a->Center().z + (a->Size().z / 2.0f);
	float b_zMax = b->Center().z + (b->Size().z / 2.0f);
	float a_zMin = a->Center().z - (a->Size().z / 2.0f);
	float b_zMin = b->Center().z - (b->Size().z / 2.0f);

	if (a_zMax < b_zMin) return false;
	if (a_zMin > b_zMax) return false;

	return true;
}

bool CollisionComponent::CircleCircleCollision(CircleColliderComponent * a, CircleColliderComponent * b)
{
	return (glm::distance(a->Center(), b->Center()) < (a->Radius() + b->Radius()));
}
