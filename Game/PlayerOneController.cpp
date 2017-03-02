#include "PlayerOneController.h"
#include "GameObject.h"



PlayerOneController::PlayerOneController(GameObject* gob) : ShipControllerComponent(gob)
{
}


PlayerOneController::~PlayerOneController()
{
}

void PlayerOneController::OnKeyPress(int key, bool down)
{
	switch (key)
	{
	case 37: // Left
		_leftPressed = down;
		break;
	case 39: // Right
		_rightPressed = down;
		break;
	case 38: // Up
		_upPressed = down;
		break;
	case 40: // Up
		_downPressed = down;
		break;
	case 17: // Ctrl
		break;
	case 32: // Space
		break;
	case 71: // G
		break;
	}
}

void PlayerOneController::OnMouseMove(glm::vec3 mousePosition)
{
	mousePosition *= _gameObject->GetPosition().z;
	mousePosition.z = _gameObject->GetPosition().z;
	_target = mousePosition;
}
