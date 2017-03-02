#pragma once
#if BUILD_GL
#include "Window.h"
class Window_GL :
	public Window
{
public:
	Window_GL(Game* game, int width, int height);
	virtual ~Window_GL();

	virtual void Initialise() {}
};

#endif