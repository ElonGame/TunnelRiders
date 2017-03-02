#pragma once
#include "System.h"
#include <vector>

// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"

class CollisionComponent;


class CollisionSystem :
	public System
{
public:
	CollisionSystem();
	virtual ~CollisionSystem();

	virtual void Process(std::vector<GameObject*>& list, double deltaTime);

};

