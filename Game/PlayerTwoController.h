#pragma once
#include "ShipControllerComponent.h"


class PlayerTwoController :
	public ShipControllerComponent
{
public:
	PlayerTwoController (GameObject* gob);
	virtual ~PlayerTwoController ();

	virtual void OnKeyPress(int key, bool down);
	virtual void OnMouseMove(glm::vec3 mousePosition) {}
};

