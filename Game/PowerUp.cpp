#include "PowerUp.h"
#include "Game.h"
#include "CollisionMatrix.h"
#include <stdlib.h>

PowerUp::PowerUp(GameObject* parent) : GameObject("powerUp")
{
	_parent = parent;

	_position = glm::vec3(0, 0, -10);

	rc = new RenderComponent(this);
	rc->SetMesh(Game::TheGame->GetMesh("powerUp"));
	rc->SetTexture(Game::TheGame->GetTexture("powerUp"));
	rc->ShouldDraw(true);

	bc = new BoxColliderComponent(this, 0.085f, 0.1f, 0.089f);
	bc->Size(bc->Size() * GetScale());
	bc->SetCollisionID(CollisionID::Power_Up);
	bc->SetCollisionMatrixFlag(CollisionID::Ship_ID);

	Reset();
}


PowerUp::~PowerUp()
{
}

void PowerUp::Update(double deltaTime)
{
}

void PowerUp::OnMessage(Message * msg)
{
}

void PowerUp::Reset()
{
	Enable();

	int random = rand() % 100;
	if (random < 20) _powerUpType = PowerUpType::scoreMultiplier;
	else if (random < 40) _powerUpType = PowerUpType::speedReset;
	else _powerUpType = PowerUpType::Empty;

	glm::vec3 s = GetScale();
	bc->Size(glm::vec3(0.085f, 0.1f, 0.089f) * s);

	switch (_powerUpType)
	{
	case PowerUpType::speedReset:
		rc->SetTexture(Game::TheGame->GetTexture("powerUp"));
		break;
	case PowerUpType::scoreMultiplier:
		rc->SetTexture(Game::TheGame->GetTexture("obstacle"));
		break;
	case PowerUpType::Empty:
		Disable();
		break;
	default:
		break;
	}
}
