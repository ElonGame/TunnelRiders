#pragma once
#include "GameObjectComponent.h"
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"


class InputComponent :
	public GameObjectComponent
{
public:
	InputComponent(GameObject* gob);
	virtual ~InputComponent();

	virtual void Start();
	virtual void Update(double deltaTime);
	virtual void OnMessage(Message* msg);
	virtual void End();

	virtual void OnKeyPress(int key, bool down) = 0;
	virtual void OnMouseMove(glm::vec3 mousePosition) = 0;
	virtual void OnMouseDown(glm::vec2 position, int button) = 0;
};

