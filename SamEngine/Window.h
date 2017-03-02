#pragma once
#include <stdlib.h>
#include <time.h>

class Game;
class Renderer;

class Window
{
public:
	Window(Game* game, int width, int height);
	virtual ~Window();

	Game* _game;
	Renderer* _renderer;
	int _width, _height;

	Game* GetGame() const { return _game; }
	Renderer* GetRenderer() const { return _renderer; }

	virtual void Initialise() = 0;


	static Window* TheWindow;
};

