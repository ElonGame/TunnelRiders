#pragma once
#include "Scene.h"
#include "Button.h"
#include "GameObject.h"
#include "ShipControllerComponent.h"
#include <vector>

class ControlSelectScene :
	public Scene
{
public:
	ControlSelectScene(bool twoPlayers);
	virtual ~ControlSelectScene();

	virtual void Initialise();
	virtual void OnKeyboard(int key, bool down);
	virtual void OnMessage(Message* msg);
	virtual void Update(double deltaTime);
	virtual void Render(RenderSystem* renderer);
	void Reset();

protected:
	bool _twoPlayers;

	GameObject* _ship;
	GameObject* _ship2;
	float _yPos;

	Button* _playButton;

	Button* _p1Key1;
	Button* _p1Key2;
	Button* _p1Mouse;

	Button* _p2Key1;
	Button* _p2Key2;
	Button* _p2Mouse;

	std::vector<bool> _buttonStates;

	ControlScheme _p1Controls;
	ControlScheme _p2Controls;
};

