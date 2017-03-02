#pragma once
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "RenderComponent.h"

namespace ObstacleType
{
	enum ObstacleType
	{
		Top,
		Bottom,
		Left,
		Right,
		Horizontal,
		Verticle,
		Empty,
		Moving,
	};
}

class Obstacle :
	public GameObject
{
public:
	Obstacle(GameObject* parent);
	virtual ~Obstacle();

	virtual void Update(double deltaTime);
	virtual void OnMessage(Message* msg);
	virtual void Reset();

	void Disable() { bc->Enable(false); rc->ShouldDraw(false); }
	void Enable() { bc->Enable(true); rc->ShouldDraw(true); }

protected:
	ObstacleType::ObstacleType _obstacleType;
	RenderComponent* rc;
	BoxColliderComponent* bc;

	bool _moving;
	float _vel;
};

