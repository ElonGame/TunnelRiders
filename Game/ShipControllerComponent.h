#pragma once
#include "InputComponent.h"
// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"
#include <map>

enum ControlScheme
{
	Keyboard1,
	Keyboard2,
	Mouse
};

class ShipControllerComponent :
	public InputComponent
{
public:
	ShipControllerComponent(ControlScheme controlScheme, GameObject* gob);
	virtual ~ShipControllerComponent();

	virtual void Update(double deltaTime);

	virtual void OnKeyPress(int key, bool down);
	virtual void OnMouseMove(glm::vec3 mousePosition);
	virtual void OnMouseDown(glm::vec2 position, int button) { }

	void KeyboardOne(int key, bool down);
	void KeyboardTwo(int key, bool down);

	void MoveTo(glm::vec3, double deltaTime);

	void SetSpeed(float speed) { _speed = speed; }
	float GetSpeed() const { return _speed; }

protected:
	bool _leftPressed;
	bool _rightPressed;
	bool _upPressed;
	bool _downPressed;

	float _speed;
	glm::vec3 _target;
	ControlScheme _controlScheme;
};

