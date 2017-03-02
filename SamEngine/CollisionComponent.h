#pragma once
#include "GameObjectComponent.h"
// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"

class BoxColliderComponent;
class CircleColliderComponent;
class InverseCircleColliderComponent;

enum ColliderType
{
	Circle,
	InverseCircle,
	Box
};

class CollisionComponent :
	public GameObjectComponent
{
public:
	CollisionComponent(GameObject* gob);
	virtual ~CollisionComponent();

	void SetCollisionMatrixFlag(int flag) { _collisionMatrix |= flag; }
	void UnsetCollisionMatrixFlag(int flag) { _collisionMatrix &= ~flag; }
	bool CheckCollisionMatrixFlag(int flag)	const { return (_collisionMatrix & flag) != 0; }
	int GetCollisionMatrix() const { return _collisionMatrix; }

	int GetCollisionID() const { return _collisionID; }
	void SetCollisionID(int id) { _collisionID = id; }

	ColliderType GetColliderType() const { return _colliderType; }

	virtual void Start();
	virtual void Update(double deltaTime);
	virtual void OnMessage(Message* msg);
	virtual void End();

	virtual bool CollideWith(BoxColliderComponent*) = 0;
	virtual bool CollideWith(CircleColliderComponent*) = 0;
	virtual bool CollideWith(InverseCircleColliderComponent*) = 0;

	void Enable(bool enable) { _enabled = enable; }
	bool Enabled() const { return _enabled; }

protected:
	int	_collisionMatrix;
	int	_collisionID;

	ColliderType _colliderType;

	bool BoxCircleCollision(BoxColliderComponent*, CircleColliderComponent*);
	bool BoxBoxCollision(BoxColliderComponent*, BoxColliderComponent*);
	bool CircleCircleCollision(CircleColliderComponent*, CircleColliderComponent*);

	bool _enabled;
};

