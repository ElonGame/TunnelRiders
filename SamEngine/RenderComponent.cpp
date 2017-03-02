#pragma once
#include "RenderComponent.h"
#include "GameObject.h"
#include "Message.h"


RenderComponent::RenderComponent(GameObject* gob)
	: GameObjectComponent("render", gob),
	_colour(1.0f, 1.0f, 1.0f, 1.0f),
	_mesh(NULL),
	_shouldDraw(true)
{

}


RenderComponent::~RenderComponent()
{
}

void RenderComponent::Start()
{

}

void RenderComponent::Update(double deltaTime)
{

}

void RenderComponent::OnMessage(Message* msg)
{

}

void RenderComponent::End()
{

}
