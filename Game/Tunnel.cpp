#pragma once
#include "Tunnel.h"
#include "RenderComponent.h"
#include "GL\GLM\gtx\rotate_vector.hpp"
#include <iostream>
#include "Obstacle.h"
#include "Game.h"
#include "Scene.h"
#include <stdlib.h>

Tunnel::Tunnel(TunnelType type, Mesh *mesh, Texture *texture, Tunnel *tunnel) :
		GameObject("Tunnel"),
		_tunnelType(type),
		_mesh(mesh),
		_texture(texture),
		_previousTunnel(tunnel),
		_velocity(0, 0, -3)
{

	_leftMesh = Game::TheGame->GetMesh("curvedTunnel");
	_rightMesh = Game::TheGame->GetMesh("curvedTunnelRight");
	_straightMesh = Game::TheGame->GetMesh("tunnel");
	_curvedTexture = Game::TheGame->GetTexture("curvedTexture");
	_straightTexture = Game::TheGame->GetTexture("straightTexture");

	_rc = new RenderComponent(this);
	_rc->ShouldDraw(true);

	_pc = new PhysicsComponent(this);
	_pc->SetVelocity(_velocity);

	_scale = glm::vec3(5, 5, 5);

	_obstacle = new Obstacle(this);
	Game::TheGame->GetSceneManager()->GetCurrentScene()->AddGameObject(_obstacle);

	_powerUp = new PowerUp(this);
	Game::TheGame->GetSceneManager()->GetCurrentScene()->AddGameObject(_powerUp);

	SetupTunnelType(_tunnelType);
}

Tunnel::~Tunnel()
{
}

void Tunnel::PlaceTunnel()
{
	if (_previousTunnel == NULL) return;

	glm::vec3 positionOffset = glm::vec3(0, 0, 4 * _previousTunnel->GetScale().y);
	_angle.y = _previousTunnel->GetLocalAngle().y;
	// Adjust offset and angle based on previous type
	switch (_previousTunnel->GetTunnelType())
	{
	case TunnelType::Right:
		_angle.y += 90;
		positionOffset.x += 3.0f * _scale.x;
		positionOffset.z -= 2.0f * _scale.z;
		break;
	case TunnelType::Left:
		_angle.y -= 90;
		positionOffset.x -= 3.0f * _scale.x;
		positionOffset.z -= 2.0f * _scale.z;
		break;
	}
	// Addjust offset based on current type
	switch (_tunnelType)
	{
	case TunnelType::Left:
		positionOffset.x += 3.0f * _scale.x;
		positionOffset.z -= 2.0f * _scale.z;
		break;
	case TunnelType::Right:
		positionOffset.x -= 3.0f * _scale.x;
		positionOffset.z -= 2.0f * _scale.z;
		break;
	}
	
	positionOffset = glm::rotate(positionOffset, -_angle.y, glm::vec3(0, 1, 0));
	_position = _previousTunnel->GetPosition() + positionOffset;
}

void Tunnel::SetupTunnelType(TunnelType type)
{
	_tunnelType = type;
	_obstacle->Disable();
	_powerUp->Disable();
	switch (_tunnelType)
	{
	case Straight:
		_rc->SetMesh(_straightMesh);
		_rc->SetTexture(_straightTexture);
		if (_previousTunnel != NULL &&
			_previousTunnel->GetTunnelType() == TunnelType::Straight)
		{
			_obstacle->Enable();
			_obstacle->Reset();
			_powerUp->Enable();
			_powerUp->Reset();
		}
		break;
	case Left:
		_rc->SetMesh(_leftMesh);
		_rc->SetTexture(_curvedTexture);
		break;
	case Right:
		_rc->SetMesh(_rightMesh);
		_rc->SetTexture(_curvedTexture);
		break;
	default:
		break;
	}

	PlaceTunnel();
}

void Tunnel::Start()
{
}

void Tunnel::Update(double deltaTime)
{
	GameObject::Update(deltaTime);

	//_pc->SetVelocity(glm::rotate(_velocity, _parent->GetAngle().y, glm::vec3(0, 1, 0)));

	PlaceTunnel();
}

void Tunnel::OnMessage(Message* msg) 
{ 
	GameObject::OnMessage(msg); 
}

void Tunnel::End()
{
}

void Tunnel::Reset()
{
	TunnelType type = TunnelType::Straight;
	if (_previousTunnel->GetTunnelType() == TunnelType::Left ||
		_previousTunnel->GetTunnelType() == TunnelType::Right)
	{
		type = TunnelType::Straight;
	}
	else
	{
		int random = rand() % 100;

		if (random < 50) type = TunnelType::Straight; // 50%
		else if (random < 75) type = TunnelType::Left; // 25%
		else if (random < 100) type = TunnelType::Right; // 25%
	}
	SetupTunnelType(type);
}

void Tunnel::UpdatePhysics(glm::vec3 vel)
{
	_velocity = vel;
	_pc->SetVelocity(_velocity);
}
