#include "CollisionMessage.h"
#include "GameObject.h"


CollisionMessage::CollisionMessage(GameObject* collider, GameObject* collidee)
	: Message("collision"),
	_collider(collider),
	_collidee(collidee),
	_handled(false)
{
}


CollisionMessage::~CollisionMessage()
{
}
