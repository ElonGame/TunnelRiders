#pragma once
#include "Scene.h"
#include "Tunnel.h"
#include "TunnelLevel.h"
#include "PhysicsSystem.h"
#include "CollisionSystem.h"
#include "Ship.h"
#include "Font.h"
#include "RenderComponent.h"
#include "Text.h"

class GameScene :
	public Scene
{
public:
	GameScene(bool twoPlayers, ControlScheme p1 = ControlScheme::Keyboard1, ControlScheme p2 = ControlScheme::Keyboard2);
	virtual ~GameScene();

	virtual void Initialise();
	virtual void OnKeyboard(int key, bool down);
	virtual void OnMessage(Message* msg);
	virtual void Update(double deltaTime);
	virtual void Render(RenderSystem* renderer);
	void Reset();

protected:

	PhysicsSystem _physicsSystem;
	CollisionSystem _collisionSystem;

	Ship* _ship;
	Ship* _ship2;

	GameObject* _tunnelCollider;

	TunnelLevel* _level;
	float _startingAngle;

	bool _twoPlayers;
	ControlScheme _p1;
	ControlScheme _p2;
};

