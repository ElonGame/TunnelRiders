#pragma once
#include "CollisionComponent.h"

// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"

class CircleColliderComponent :
	public CollisionComponent
{
public:
	CircleColliderComponent(GameObject* gob);
	CircleColliderComponent(GameObject* gob, float radius);
	virtual ~CircleColliderComponent();

	float Radius() const { return _radius; }
	void Radius(float r) { _radius = r; }
	glm::vec3 Center() const;

	virtual bool CollideWith(BoxColliderComponent*);
	virtual bool CollideWith(CircleColliderComponent*);
	virtual bool CollideWith(InverseCircleColliderComponent*);


protected:
	float _radius;
};

