#pragma once
#include "Scene.h"
#include "Button.h"

class MainMenuScene :
	public Scene
{
public:
	MainMenuScene();
	virtual ~MainMenuScene();

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

	Button* _playButton;
	Button* _versusButton;
	Button* _scoresButton;
	Button* _exitButton;
};

