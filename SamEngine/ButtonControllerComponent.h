#pragma once
#include "InputComponent.h"
#include "Button.h"

class ButtonControllerComponent :
	public InputComponent
{
public:
	ButtonControllerComponent(Button* gob);
	virtual ~ButtonControllerComponent();

	virtual void OnKeyPress(int key, bool down) {}
	virtual void OnMouseMove(glm::vec3 mousePosition) {}
	virtual void OnMouseDown(glm::vec2 position, int button);
};

