#pragma once
#include "CircleColliderComponent.h"
class InverseCircleColliderComponent :
	public CircleColliderComponent
{
public:

	InverseCircleColliderComponent(GameObject* gob);
	InverseCircleColliderComponent(GameObject* gob, float radius);

	virtual ~InverseCircleColliderComponent();

	virtual bool CollideWith(BoxColliderComponent*);
	virtual bool CollideWith(CircleColliderComponent*);
	virtual bool CollideWith(InverseCircleColliderComponent*);
};

