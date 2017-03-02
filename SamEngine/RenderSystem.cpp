#pragma once
#include "RenderSystem.h"
#include "GameObject.h"
#include "RenderComponent.h"


RenderSystem::RenderSystem()
	: _renderer(NULL)
{
	_MVM = glm::mat4(1.0f);
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::Process(std::vector<GameObject*>& list, double deltaTime)
{
	if (_renderer == NULL) return;
	for (GameObject* obj : list)
	{
		if (obj->IsAlive())
		{
			if (RenderComponent* rc = (RenderComponent*)obj->GetComponent("render"))
			{
				if (!rc->TwoDimensions())
					_renderer->Draw(rc, _MVM);
				else
					_renderer->Draw2D(rc, _MVM);
			}
		}
	}

}
