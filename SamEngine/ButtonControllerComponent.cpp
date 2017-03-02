#include "stdafx.h"
#include "ButtonControllerComponent.h"


ButtonControllerComponent::ButtonControllerComponent(Button* gob) : InputComponent(gob)
{
}


ButtonControllerComponent::~ButtonControllerComponent()
{
}

void ButtonControllerComponent::OnMouseDown(glm::vec2 position, int button)
{
	if (button == 1)
	{
		if (position.x < _gameObject->GetPosition().x + (_gameObject->GetScale().x / 2.0f) &&
			position.x > _gameObject->GetPosition().x - (_gameObject->GetScale().x / 2.0f) &&
			position.y < _gameObject->GetPosition().y + (_gameObject->GetScale().y / 2.0f) &&
			position.y > _gameObject->GetPosition().y - (_gameObject->GetScale().y / 2.0f))
		{
			Button* b = (Button*)_gameObject;
			b->Press(true);
		}
	}
}
