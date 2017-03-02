#pragma once
#include "Scene.h"
#include <vector>
#include <string>


class ScoresScene :
	public Scene
{
public:
	ScoresScene();
	ScoresScene(std::vector<std::pair<std::string, int>> scores);
	virtual ~ScoresScene();

	virtual void Initialise();
	virtual void OnKeyboard(int key, bool down);
	virtual void OnMessage(Message* msg);
	virtual void Update(double deltaTime);
	virtual void Render(RenderSystem* renderer);
	void Reset();

protected:
	std::vector<std::pair<std::string, int>> _scores;
};

