#pragma once
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "RenderComponent.h"

namespace PowerUpType
{
	enum PowerUpType
	{
		speedReset,
		scoreMultiplier,
		Empty
	};
}

class PowerUp :
	public GameObject
{
public:
	PowerUp(GameObject* parent);
	virtual ~PowerUp();

	virtual void Update(double deltaTime);
	virtual void OnMessage(Message* msg);
	virtual void Reset();

	void Disable() { bc->Enable(false); rc->ShouldDraw(false); }
	void Enable() { bc->Enable(true); rc->ShouldDraw(true); }

	PowerUpType::PowerUpType GetPowerUpType() const { return _powerUpType; }

protected:
	PowerUpType::PowerUpType _powerUpType;

	RenderComponent* rc;
	BoxColliderComponent* bc;
};

