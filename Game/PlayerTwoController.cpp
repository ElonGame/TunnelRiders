#include "PlayerTwoController.h"



PlayerTwoController::PlayerTwoController(GameObject* gob) : ShipControllerComponent(gob)
{
}


PlayerTwoController::~PlayerTwoController()
{
}

void PlayerTwoController::OnKeyPress(int key, bool down)
{
	switch (key)
	{
	case 65: // Left
		_leftPressed = down;
		break;
	case 68: // Right
		_rightPressed = down;
		break;
	case 87: // Up
		_upPressed = down;
		break;
	case 83: // Up
		_downPressed = down;
	case 17: // Ctrl
		break;
	case 32: // Space
		break;
	case 71: // G
		break;
	}
}
