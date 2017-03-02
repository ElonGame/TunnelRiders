#include "InverseCircleColliderComponent.h"


InverseCircleColliderComponent::InverseCircleColliderComponent(GameObject* gob) : CircleColliderComponent(gob)
{
	_colliderType = ColliderType::InverseCircle;
}

InverseCircleColliderComponent::InverseCircleColliderComponent(GameObject* gob, float radius) : InverseCircleColliderComponent(gob)
{
	_radius = radius;
}

InverseCircleColliderComponent::~InverseCircleColliderComponent()
{
}

bool InverseCircleColliderComponent::CollideWith(BoxColliderComponent * other)
{
	return !BoxCircleCollision(other, this);
}

bool InverseCircleColliderComponent::CollideWith(CircleColliderComponent* other)
{
	return !CircleCircleCollision(this, other);
}

bool InverseCircleColliderComponent::CollideWith(InverseCircleColliderComponent * other)
{
	return true;
}
