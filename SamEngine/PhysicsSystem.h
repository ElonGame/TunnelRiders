#pragma once
#include "System.h"
#include <vector>
// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"

// Forward declaration
class PhysicsComponent;

class PhysicsSystem :
	public System
{
public:
	PhysicsSystem();
	virtual ~PhysicsSystem();

	virtual void Process(std::vector<GameObject*>& list, double deltaTime);
};

