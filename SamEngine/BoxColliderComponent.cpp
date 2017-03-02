#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "CircleColliderComponent.h"

BoxColliderComponent::BoxColliderComponent(GameObject* gob) : CollisionComponent(gob)
{
	_colliderType = ColliderType::Box;
}

BoxColliderComponent::BoxColliderComponent(GameObject* gob, float width, float height, float depth) : BoxColliderComponent(gob)
{
	_size = glm::vec3(width, height, depth);
}


BoxColliderComponent::~BoxColliderComponent()
{
}

glm::vec3 BoxColliderComponent::Center() const
{
	return _gameObject->GetPosition();
}

bool BoxColliderComponent::CollideWith(BoxColliderComponent * other)
{
	return BoxBoxCollision(this, other);
}

bool BoxColliderComponent::CollideWith(CircleColliderComponent* other)
{
	return BoxCircleCollision(this, other);
}

bool BoxColliderComponent::CollideWith(InverseCircleColliderComponent * other)
{
	return !BoxCircleCollision(this, (CircleColliderComponent*)other);
}


