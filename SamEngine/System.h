#pragma once
#include "GameObjectComponent.h"
#include <vector>


class System
{
public:
	System();
	virtual ~System();

	virtual void Process(std::vector<GameObject*>& list, double deltaTime) = 0;
};

