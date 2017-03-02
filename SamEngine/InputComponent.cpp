#pragma once
#include "InputComponent.h"
#include "GameObject.h"
#include "Message.h"
#include "KeyPressMessage.h"
#include "MouseMoveMessage.h"
#include "MouseDownMessage.h"


InputComponent::InputComponent(GameObject* gob) : GameObjectComponent("input", gob)
{

}


InputComponent::~InputComponent()
{
}

void InputComponent::Start()
{
	_gameObject->RegisterListener("keypress", this);
	_gameObject->RegisterListener("mousemove", this);
	_gameObject->RegisterListener("mousedown", this);
}

void InputComponent::Update(double deltaTime)
{
}

void InputComponent::OnMessage(Message * msg)
{
	if (msg->GetMessageType() == "keypress")
	{
		// Respond to this keypress somehow
		KeyPressMessage* kpm = (KeyPressMessage*)msg;
		OnKeyPress(kpm->GetKey(), kpm->GetDown());
	}
	if (msg->GetMessageType() == "mousemove")
	{
		MouseMoveMessage* mmm = (MouseMoveMessage*)msg;
		OnMouseMove(mmm->GetPosition());
	}
	if (msg->GetMessageType() == "mousedown")
	{
		MouseDownMessage* mdm = (MouseDownMessage*)msg;
		OnMouseDown(mdm->GetPosition(), mdm->GetButton());
	}
}

void InputComponent::End()
{
	_gameObject->UnregisterListener("keypress", this);
}
