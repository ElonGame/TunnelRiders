#pragma once
#include "Game.h"
// Engine classes
#include "Renderer.h"
#include "Window.h"
#include <vector>

// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"


class TunnelGame :
	public Game
{
public:
	TunnelGame();
	virtual ~TunnelGame();

	virtual void Initialise(Window* w);
	virtual void OnKeyboard(int key, bool down);
	virtual void Render();
	virtual void Run();

	void InitialiseSettings(const std::string& filePath);
};

