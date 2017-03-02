#include "TextFieldInputController.h"
#include "Game.h"

TextFieldInputController::TextFieldInputController(Text* textObject) : InputComponent(textObject)
{
}


TextFieldInputController::~TextFieldInputController()
{
}

void TextFieldInputController::OnKeyPress(int key, bool down)
{
	if (Game::TheGame->GetPreviousKeyState(key)) return;
	Text* text = (Text*)_gameObject;
	std::string current = text->GetText();
	if (key == 127 || key == 8)
	{
		text->SetText(current.substr(0, current.size() - 1));
	}
	if (key >= 65 && key <= 90)
	{
		char c = key;
		
		text->SetText(current + c);
	}
	if (key >= 97 && key <= 122)
	{
		char c = key - 32;
		text->SetText(current + c);
	}
	if (key >= 48 && key <= 57)
	{
		int number = key - 48;
		text->SetText(current + std::to_string(number));
	}
}
