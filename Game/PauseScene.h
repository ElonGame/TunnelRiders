#pragma once
#include "Scene.h"

class PauseScene :
	public Scene
{
public:
	PauseScene();
	virtual ~PauseScene();

	virtual void Initialise();
	virtual void OnKeyboard(int key, bool down);
	virtual void OnMessage(Message* msg);
	virtual void Update(double deltaTime);
	virtual void Render(RenderSystem* renderer);
	void Reset();

protected:
	GameObject* _ship;
	GameObject* _ship2;
	float _yPos;
};

