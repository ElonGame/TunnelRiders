#include "Button.h"
#include "ButtonControllerComponent.h"
#include "RenderComponent.h"


Button::Button(Mesh* mesh, Texture* texture, glm::vec3 position, glm::vec3 scale) : UIObject(mesh, texture, position, scale), _texture(texture), _pressedTexture(NULL)
{
	ButtonControllerComponent* bcc = new ButtonControllerComponent(this);
	_rc = (RenderComponent*)GetComponent("render");
}

Button::Button(Mesh* mesh, Texture* texture, Texture* pressedTexture, glm::vec3 position, glm::vec3 scale) : Button(mesh, texture, position, scale)
{
	_pressedTexture = pressedTexture;
}


Button::~Button()
{
}

void Button::Press(bool pressed)
{
	_pressed = pressed;
	if (_pressedTexture != NULL)
	{
		if (pressed) _rc->SetTexture(_pressedTexture);
		else _rc->SetTexture(_texture);
	}
}
