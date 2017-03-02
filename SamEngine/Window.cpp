#pragma once
#include "Window.h"

Window*	Window::TheWindow = 0;

Window::Window(Game* game, int width, int height) :
	_game(game),
	_renderer(0),
	_width(width),
	_height(height)
{
	TheWindow = this;
	srand(time(NULL));
}


Window::~Window()
{
}
