#pragma once
#include "Ship.h"
#include "RenderComponent.h"
#include "Game.h"
#include "ShipControllerComponent.h"
#include "PlayerTwoController.h"
#include "PhysicsComponent.h"
#include "BoxColliderComponent.h"
#include "CollisionMatrix.h"
#include "CollisionMessage.h"
#include "PowerUp.h"
#include "TunnelSpeedMessage.h"

float lerp(float v0, float v1, float t) {
	return (1 - t)*v0 + t*v1;
}

Ship::Ship(glm::vec3 position, ControlScheme controlsScheme, bool playerTwo) : GameObject("ship"), _speed(5.0f), _score(0), _scorePerSecond(1.0f), _dead(false), _scoreMultiplier(1.0f), _scoreMultTimer(0.0f)
{
	_mesh = Game::TheGame->GetMesh("ship");
	if (playerTwo) _texture = Game::TheGame->GetTexture("ship_red");
	else _texture = Game::TheGame->GetTexture("ship_yellow");

	ShipControllerComponent* sc = new ShipControllerComponent(controlsScheme, this);
	sc->SetSpeed(_speed);

	RenderComponent* rc = new RenderComponent(this);
	rc->SetMesh(_mesh);
	rc->SetTexture(_texture);
	rc->ShouldDraw(true);

	BoxColliderComponent* bc = new BoxColliderComponent(this, 0.8f, 0.35f, 1.0f);
	bc->SetCollisionID(CollisionID::Ship_ID);
	bc->SetCollisionMatrixFlag(CollisionID::Tunnel_ID);
	bc->SetCollisionMatrixFlag(CollisionID::Obstacle_ID);
	bc->SetCollisionMatrixFlag(CollisionID::Power_Up);

	_pc = new PhysicsComponent(this);
	_pc->SetFriction(1.0f);
	_pc->SetMaxSpeed(_speed);

	_scale = glm::vec3(0.25f, 0.25f, 0.25f);
	_position = position;
}


Ship::~Ship()
{
}

void Ship::Update(double deltaTime)
{
	GameObject::Update(deltaTime);

	_previousPosition = _position;

	if (!_dead)
	{
		glm::vec3 vel = _pc->GetVelocity();
		_angle.z = lerp(0.0f, 30.0f, vel.x / _speed);
		_angle.x = lerp(0.0f, 30.0f, vel.y / _speed);

		if (_scoreMultiplier > 1)
		{
			_scoreMultTimer -= (float)deltaTime;
			if (_scoreMultTimer <= 0)
			{
				_scoreMultiplier = 1.0f;
				_scoreMultTimer = 0.0f;
			}
		}

		_score += _scorePerSecond * deltaTime * _scoreMultiplier;
	}
	else
	{
		_angle.x += 15.0f * deltaTime;
		_angle.z += 3.0f * deltaTime;
	}
}

void Ship::OnMessage(Message * msg)
{
	if (msg->GetMessageType() == "collision")
	{
		CollisionMessage* col = (CollisionMessage*)msg;
		if (!col->Handled())
		{
			if (col->GetCollidee() == this ||
				col->GetCollider() == this)
			{
				// Send out death message
				//DeadObjectMessage dom(this);
				//OnMessage(&dom);
				//RenderComponent* rc = (RenderComponent*)GetComponent("render");
				//rc->ShouldDraw(false);
				//_alive = false;
				GameObject* collidedWith = col->GetOtherCollisionObject(this);
				CollisionComponent* cc = (CollisionComponent*)collidedWith->GetComponent("collision");
				if (cc->GetCollisionID() == CollisionID::Tunnel_ID)
				{
					glm::vec3 collisionNormal = collidedWith->GetPosition() - GetPosition();
					collisionNormal.z = 0;
					glm::vec3 newVel = glm::reflect(_pc->GetVelocity(), collisionNormal);
					_pc->SetVelocity(newVel);
					col->SetHandled();
				}
				else if (cc->GetCollisionID() == CollisionID::Ship_ID)
				{
					glm::vec3 collisionNormal = collidedWith->GetPosition() - GetPosition();
					collisionNormal.z = 0;
					glm::vec3 newVelThat = glm::reflect(_pc->GetVelocity(), collisionNormal);
					PhysicsComponent* collideePC = (PhysicsComponent*)collidedWith->GetComponent("physics");
					glm::vec3 newVelThis = glm::reflect(collideePC->GetVelocity(), collisionNormal);

					((Ship*)collidedWith)->RevertToPreviousPosition();
					RevertToPreviousPosition();

					collideePC->SetVelocity(newVelThat);
					_pc->SetVelocity(newVelThis);
					col->SetHandled();
				}
				else if (cc->GetCollisionID() == CollisionID::Obstacle_ID)
				{
					PhysicsComponent* collideePC = (PhysicsComponent*)collidedWith->Parent()->GetComponent("physics");
					_pc->SetMaxSpeed(100.0f);
					_pc->SetVelocity(glm::vec3(_pc->GetVelocity().x, _pc->GetVelocity().y, collideePC->GetVelocity().z * 3.0f));
					col->SetHandled();
					_scorePerSecond = 0;
					_dead = true;
					
				}
				else if (cc->GetCollisionID() == CollisionID::Power_Up)
				{
					PowerUp* powerUp = (PowerUp*)collidedWith;
					if (powerUp->GetPowerUpType() == PowerUpType::scoreMultiplier)
					{
						_scoreMultiplier = 2.0f;
						_scoreMultTimer = 5.0f;
					}
					else if (powerUp->GetPowerUpType() == PowerUpType::speedReset)
					{
						TunnelSpeedMessage tunMessage = TunnelSpeedMessage();
						Game::TheGame->BroadcastMessage(&tunMessage);
					}
					powerUp->Disable();
					col->SetHandled();
				}
			}
		}
	}

	GameObject::OnMessage(msg);
}

void Ship::Reset()
{
	_alive = true;
	RenderComponent* rc = (RenderComponent*)GetComponent("render");
	rc->ShouldDraw(true);
}
