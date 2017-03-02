#pragma once
#include <string>
#include "Observer.h"

// Forward references
class GameObject;
class Message;

class GameObjectComponent
	: public Observer
{
public:
	GameObjectComponent(std::string type, GameObject* parent);
	virtual ~GameObjectComponent();

	GameObject* GetGameObject()	const { return _gameObject; }
	std::string GetComponentType() const { return _componentType; }

	virtual void Start() = 0;
	virtual void Update(double deltaTime) = 0;
	virtual void End() = 0;

	// Broadcast a message to all objects
	void BroadcastMessage(Message* msg);

protected:
	GameObject* _gameObject;
	std::string _componentType;

private:
	GameObjectComponent(const GameObjectComponent&);
	GameObjectComponent& operator=(const GameObjectComponent&);
};

