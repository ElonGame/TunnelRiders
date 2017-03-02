#pragma once
#include "Scene.h"
#include <vector>
#include <string>
#include "Text.h"

class NameEntryScene :
	public Scene
{
public:
	NameEntryScene(int score1, int score2 = 0);
	virtual ~NameEntryScene();

	virtual void Initialise();
	virtual void OnKeyboard(int key, bool down);
	virtual void OnMessage(Message* msg);
	virtual void Update(double deltaTime);
	virtual void Render(RenderSystem* renderer);
	void Reset();

protected:
	int _p1Score;
	int _p2Score;

	Text* _prompt;
	Text* _input;

	std::string _player1Name;
	std::string _player2Name;

	std::vector<std::pair<std::string, int>> _scores;
};

