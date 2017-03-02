#pragma once
#include "Obstacle.h"
#include "RenderComponent.h"
#include "Game.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "CollisionMatrix.h"
#include <stdlib.h>


Obstacle::Obstacle(GameObject* parent) : GameObject("Obstacle")
{
	_parent = parent;

	rc = new RenderComponent(this);
	// obstacleVert
	rc->SetMesh(Game::TheGame->GetMesh("obstacle"));
	rc->SetTexture(Game::TheGame->GetTexture("obstacle"));
	rc->ShouldDraw(true);

	_scale = glm::vec3(1, 0.3f, 1);
	glm::vec3 scale = GetScale();
	bc = new BoxColliderComponent(this, 2.6f, 0.8f, 0.2f);
	bc->Size(bc->Size() * GetScale());
	bc->SetCollisionID(CollisionID::Obstacle_ID);
	bc->SetCollisionMatrixFlag(CollisionID::Ship_ID);
	_angle.y = 90.0f;

	_moving = false;
	_vel = 1.0f;
	Reset();
}


Obstacle::~Obstacle()
{
}

void Obstacle::Update(double deltaTime)
{
	if (_moving)
	{
		glm::vec3 s = GetScale();
		if (_position.x <= -0.6f * s.x)
		{
			_vel = 1.0f;
		}
		else if (_position.x >= 0.6f * s.x)
		{
			_vel = -1.0f;
		}
		_position += glm::vec3(_vel * (float)deltaTime, 0, 0);
	}
}

void Obstacle::OnMessage(Message * msg)
{
}

void Obstacle::Reset()
{
	Enable();
	_obstacleType = (ObstacleType::ObstacleType)(rand() % 8);
	glm::vec3 s = GetScale();
	bc->Size(glm::vec3(2.6f, 0.8f, 0.2f) * s);
	_moving = false;
	//_type = ObstacleType::Moving;
	switch (_obstacleType)
	{
	case ObstacleType::Top:
		rc->SetMesh(Game::TheGame->GetMesh("obstacle"));
		_position = glm::vec3(0, 0.6f, 0) * s;
		break;
	case ObstacleType::Bottom:
		rc->SetMesh(Game::TheGame->GetMesh("obstacle"));
		_position = glm::vec3(0, -0.6f, 0) * s;
		break;
	case ObstacleType::Left:
		rc->SetMesh(Game::TheGame->GetMesh("obstacleVert"));
		bc->Size(glm::vec3(0.8f, 2.6f, 0.2f) * glm::vec3(s.y, s.x, s.z));
		_position = glm::vec3(-0.6f, 0, 0) * s;
		break;
	case ObstacleType::Right:
		rc->SetMesh(Game::TheGame->GetMesh("obstacleVert"));
		bc->Size(glm::vec3(0.8f, 2.6f, 0.2f) * glm::vec3(s.y, s.x, s.z));
		_position = glm::vec3(0.6f, 0, 0) * s;
		break;
	case ObstacleType::Horizontal:
		rc->SetMesh(Game::TheGame->GetMesh("obstacle"));
		_position = glm::vec3(0, 0, 0) * s;
		break;
	case ObstacleType::Verticle:
		rc->SetMesh(Game::TheGame->GetMesh("obstacleVert"));
		bc->Size(glm::vec3(0.8f, 2.6f, 0.2f) * glm::vec3(s.y, s.x, s.z));
		_position = glm::vec3(0, 0, 0) * s;
		break;
	case ObstacleType::Empty:
		_position = glm::vec3(0, 150, 0) * s;
		Disable();
		break;
	case ObstacleType::Moving:
		rc->SetMesh(Game::TheGame->GetMesh("obstacleVert"));
		bc->Size(glm::vec3(0.8f, 2.6f, 0.2f) * glm::vec3(s.y, s.x, s.z));
		_position = glm::vec3(-0.6f, 0, 0) * s;
		_moving = true;
		break;
	default:
		break;
	}
}
