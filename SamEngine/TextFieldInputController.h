#pragma once
#include "InputComponent.h"
#include "Text.h"

class TextFieldInputController :
	public InputComponent
{
public:
	TextFieldInputController(Text* textObject);
	virtual ~TextFieldInputController();

	virtual void OnKeyPress(int key, bool down);
	virtual void OnMouseMove(glm::vec3 mousePosition) {}
	virtual void OnMouseDown(glm::vec2 position, int button) {}
};

