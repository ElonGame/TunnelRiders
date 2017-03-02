#include "stdafx.h"
#include "MouseDownMessage.h"


MouseDownMessage::MouseDownMessage(float x, float y, int button) : Message("mousedown"), _position(glm::vec2(x, y)) ,_button(button)
{
}


MouseDownMessage::~MouseDownMessage()
{
}
