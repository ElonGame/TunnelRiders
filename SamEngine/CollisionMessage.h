#pragma once
#include "Message.h"
class GameObject;


class CollisionMessage :
	public Message
{
public:
	CollisionMessage(GameObject* collider, GameObject* collidee);
	virtual ~CollisionMessage();

	GameObject* GetCollider() const { return _collider; }
	GameObject* GetCollidee() const { return _collidee; }
	GameObject* GetOtherCollisionObject(GameObject* obj) const { return _collider == obj ? _collidee : _collider; }

	bool Handled() const { return _handled; }
	void SetHandled(bool handled = true) { _handled = handled; }

protected:
	GameObject* _collider;
	GameObject* _collidee;
	bool _handled;
};

