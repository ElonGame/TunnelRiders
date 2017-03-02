#pragma once
#include "Message.h"

// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"

class MoveMessage :
	public Message
{
public:
	MoveMessage(glm::vec3 direction, float speed);
	virtual ~MoveMessage();

	glm::vec3 GetDirection() const { return _direction; }
	float GetSpeed() const { return _speed; }

protected:
	glm::vec3 _direction;
	float _speed;
};

