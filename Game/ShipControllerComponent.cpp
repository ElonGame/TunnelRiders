#include "ShipControllerComponent.h"
#include "GameObject.h"
#include "MoveMessage.h"
#include "PhysicsComponent.h"
#include "Controls.h"
#include "SettingsFile.h"


ShipControllerComponent::ShipControllerComponent(ControlScheme controlScheme, GameObject* gob) : InputComponent(gob),
					_leftPressed(false), _rightPressed(false), _upPressed(false), _downPressed(false), _controlScheme(controlScheme)
{
	KeyBindings["p1_up"] = atoi(SettingsFile::Instance().GetValue("p1_up").c_str());
	KeyBindings["p1_down"] = atoi(SettingsFile::Instance().GetValue("p1_down").c_str());
	KeyBindings["p1_left"] = atoi(SettingsFile::Instance().GetValue("p1_left").c_str());
	KeyBindings["p1_right"] = atoi(SettingsFile::Instance().GetValue("p1_right").c_str());

	KeyBindings["p2_up"] = atoi(SettingsFile::Instance().GetValue("p2_up").c_str());
	KeyBindings["p2_down"] = atoi(SettingsFile::Instance().GetValue("p2_down").c_str());
	KeyBindings["p2_left"] = atoi(SettingsFile::Instance().GetValue("p2_left").c_str());
	KeyBindings["p2_right"] = atoi(SettingsFile::Instance().GetValue("p2_right").c_str());
}


ShipControllerComponent::~ShipControllerComponent()
{
}

void ShipControllerComponent::Update(double deltaTime)
{
	InputComponent::Update(deltaTime);

	if (_controlScheme == ControlScheme::Keyboard1 ||
		_controlScheme == ControlScheme::Keyboard2)
	{
		// move direction
		if (_leftPressed)
		{
			MoveMessage msg(glm::vec3(1, 0, 0), _speed);
			_gameObject->OnMessage(&msg);
		}
		if (_rightPressed)
		{
			MoveMessage msg(glm::vec3(-1, 0, 0), _speed);
			_gameObject->OnMessage(&msg);
		}
		if (_upPressed)
		{
			MoveMessage msg(glm::vec3(0, 1, 0), _speed);
			_gameObject->OnMessage(&msg);
		}
		if (_downPressed)
		{
			MoveMessage msg(glm::vec3(0, -1, 0), _speed);
			_gameObject->OnMessage(&msg);
		}
		// no key press
		if (!_leftPressed && !_rightPressed)
		{
			MoveMessage msg(glm::vec3(1, 0, 0), 0);
			_gameObject->OnMessage(&msg);
		}
		if (!_downPressed && !_upPressed)
		{
			MoveMessage msg(glm::vec3(0, 1, 0), 0);
			_gameObject->OnMessage(&msg);
		}
	}
	else if (_controlScheme == ControlScheme::Mouse)
		MoveTo(_target, deltaTime);
}

void ShipControllerComponent::OnKeyPress(int key, bool down)
{
	std::string prefix = "";
	if (_controlScheme == ControlScheme::Keyboard1) prefix = "p1_";
	else if (_controlScheme == ControlScheme::Keyboard2) prefix = "p2_";

	std::string left = prefix + "left";
	std::string right = prefix + "right";
	std::string up = prefix + "up";
	std::string downs = prefix + "down";

	if (key == KeyBindings[left]) _leftPressed = down;
	else if (key == KeyBindings[right]) _rightPressed = down;
	else if (key == KeyBindings[up]) _upPressed = down;
	else if (key == KeyBindings[downs]) _downPressed = down;
}

void ShipControllerComponent::OnMouseMove(glm::vec3 mousePosition)
{
	mousePosition *= _gameObject->GetPosition().z;
	mousePosition.z = _gameObject->GetPosition().z;
	_target = mousePosition;
}

void ShipControllerComponent::MoveTo(glm::vec3 target, double deltaTime)
{
	target.y -= 0.5f;
	PhysicsComponent* pc = (PhysicsComponent*)_gameObject->GetComponent("physics");
	glm::vec3 direction = glm::vec3(target.x, target.y, _gameObject->GetPosition().z) - _gameObject->GetPosition();
	if (glm::length(direction) > 0.5f)
		pc->SetAcceleration(glm::normalize(direction) * 3.0f);
	else if (glm::length(direction) < 0.5f)
		pc->SetAcceleration(glm::vec3(0,0,0));
}
