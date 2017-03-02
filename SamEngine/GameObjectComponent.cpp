#include "GameObjectComponent.h"
#include "GameObject.h"
#include "Game.h"


GameObjectComponent::GameObjectComponent(std::string type, GameObject* parent)
	: _gameObject(parent),
	_componentType(type)
{
	// Add us to the parent component
	parent->AddComponent(this);
}

GameObjectComponent::~GameObjectComponent()
{
}

void GameObjectComponent::BroadcastMessage(Message* msg)
{
	Game::TheGame->BroadcastMessage(msg);
}