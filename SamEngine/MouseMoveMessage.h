#pragma once
#include "Message.h"

// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"

class MouseMoveMessage :
	public Message
{
public:
	MouseMoveMessage(glm::vec3 position);
	virtual ~MouseMoveMessage();

	glm::vec3 GetPosition() const { return _position; }

protected:
	glm::vec3 _position;
};

