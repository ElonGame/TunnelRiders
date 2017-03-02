#include "stdafx.h"
#include "CircleColliderComponent.h"
#include "GameObject.h"


CircleColliderComponent::CircleColliderComponent(GameObject* gob) : CollisionComponent(gob)
{
	_colliderType = ColliderType::Circle;
}

CircleColliderComponent::CircleColliderComponent(GameObject* gob, float radius) : CircleColliderComponent(gob)
{
	_radius = radius;
}


CircleColliderComponent::~CircleColliderComponent()
{
}

glm::vec3 CircleColliderComponent::Center() const
{
	return _gameObject->GetPosition();
}

bool CircleColliderComponent::CollideWith(BoxColliderComponent * other)
{
	return BoxCircleCollision(other, this);
}

bool CircleColliderComponent::CollideWith(CircleColliderComponent* other)
{
	return CircleCircleCollision(this, other);
}

bool CircleColliderComponent::CollideWith(InverseCircleColliderComponent * other)
{
	return !CircleCircleCollision(this, (CircleColliderComponent*)other);
}
