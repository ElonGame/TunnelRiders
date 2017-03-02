#pragma once
#include "ShipControllerComponent.h"


class PlayerOneController :
	public ShipControllerComponent
{
public:
	PlayerOneController(GameObject* gob);
	virtual ~PlayerOneController();

	virtual void OnKeyPress(int key, bool down);
	virtual void OnMouseMove(glm::vec3 mousePosition);

};

