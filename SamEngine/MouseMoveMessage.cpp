#include "stdafx.h"
#include "MouseMoveMessage.h"


MouseMoveMessage::MouseMoveMessage(glm::vec3 position) : Message("mousemove"), _position(position)
{
}


MouseMoveMessage::~MouseMoveMessage()
{
}
