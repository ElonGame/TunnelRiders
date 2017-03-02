#pragma once
#include "Message.h"

// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"

class MouseDownMessage :
	public Message
{
public:
	MouseDownMessage(float x, float y, int button);
	virtual ~MouseDownMessage();

	glm::vec2 GetPosition() const { return _position; }
	int GetButton() const { return _button; }

protected:
	glm::vec2 _position;
	int _button;
};

