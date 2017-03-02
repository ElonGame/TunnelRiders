#pragma once
#include "UIObject.h"
#include "RenderComponent.h"

class Button :
	public UIObject
{
public:
	Button(Mesh* mesh, Texture* texture, glm::vec3 position, glm::vec3 scale);
	Button(Mesh* mesh, Texture* texture, Texture* pressedTexture, glm::vec3 position, glm::vec3 scale);
	virtual ~Button();

	bool IsPressed() const { return _pressed; }
	void Press(bool pressed);

protected:
	bool _pressed;

	RenderComponent* _rc;

	Texture* _texture;
	Texture* _pressedTexture;
};

