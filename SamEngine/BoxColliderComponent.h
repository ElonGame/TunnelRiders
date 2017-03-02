#pragma once
#include "CollisionComponent.h"

// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"

class BoxColliderComponent :
	public CollisionComponent
{
public:
	BoxColliderComponent(GameObject* gob);
	BoxColliderComponent(GameObject* gob, float width, float height, float depth);
	virtual ~BoxColliderComponent();

	glm::vec3 Size() const { return _size; }
	void Size(glm::vec3 s) { _size = s; }
	glm::vec3 Center() const;

	virtual bool CollideWith(BoxColliderComponent*);
	virtual bool CollideWith(CircleColliderComponent*);
	virtual bool CollideWith(InverseCircleColliderComponent*);	

protected:
	glm::vec3 _size;
};

