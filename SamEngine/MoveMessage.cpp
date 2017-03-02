#include "stdafx.h"
#include "MoveMessage.h"


MoveMessage::MoveMessage(glm::vec3 direction, float speed) :
	Message("move"),
	_direction(direction),
	_speed(speed)
{
}


MoveMessage::~MoveMessage()
{
}
