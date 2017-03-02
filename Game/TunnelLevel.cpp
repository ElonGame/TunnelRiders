#include "TunnelLevel.h"
#include "Game.h"
#include "Tunnel.h"
#include "SettingsFile.h"

TunnelLevel::TunnelLevel() : _velocity(0, 0, -3), _tunnelsPastThrough(1)
{
	_leftMesh = Game::TheGame->GetMesh("curvedTunnel");
	_rightMesh = Game::TheGame->GetMesh("curvedTunnelRight");
	_straightMesh = Game::TheGame->GetMesh("tunnel");
	_curvedTexture = Game::TheGame->GetTexture("curvedTexture");
	_straightTexture = Game::TheGame->GetTexture("straightTexture");

	_scale = glm::vec3(5, 5, 5);
	_startingPosition = glm::vec3(0, 0, 15);

	// All the tunnels in order of appearence, loops infinitely
	_tunnels.push_back(new Tunnel(TunnelType::Straight, _straightMesh, _straightTexture, NULL));
	_tunnels.push_back(new Tunnel(TunnelType::Straight, _straightMesh, _straightTexture, _tunnels[0]));
	_tunnels.push_back(new Tunnel(TunnelType::Left, _leftMesh, _curvedTexture, _tunnels[1]));
	_tunnels.push_back(new Tunnel(TunnelType::Straight, _straightMesh, _straightTexture, _tunnels[2]));
	_tunnels.push_back(new Tunnel(TunnelType::Straight, _straightMesh, _straightTexture, _tunnels[3]));
	_tunnels.push_back(new Tunnel(TunnelType::Left, _leftMesh, _curvedTexture, _tunnels[4]));
	_tunnels.push_back(new Tunnel(TunnelType::Straight, _straightMesh, _straightTexture, _tunnels[5]));
	_tunnels.push_back(new Tunnel(TunnelType::Right, _rightMesh, _curvedTexture, _tunnels[6]));

	for (Tunnel* tun : _tunnels)
	{
		tun->UpdatePhysics(_velocity);
		tun->SetScale(_scale);
	}

	_currentTunnelIndex = 0;
	_endTunnelIndex = _tunnels.size() - 1;
	_tunnelsPastThrough = 1;

	_tunnelVelIncrease = atof(SettingsFile::Instance().GetValue("tunnelIncrement").c_str());
	_tunnelMaxVelocity = atof(SettingsFile::Instance().GetValue("tunnelMaxVel").c_str());
}


TunnelLevel::~TunnelLevel()
{
	for (Tunnel* tunnel : _tunnels)
	{
		delete tunnel;
	}
}

void TunnelLevel::Start()
{
	
}

void TunnelLevel::Update(double deltaTime)
{
	//Move tunnel when it goes behind camera
	if (_tunnels[_currentTunnelIndex]->GetPosition().z <= -4.0f * _scale.y * 0.5f)
	{
		
		_tunnels[_currentTunnelIndex]->SetPrevious(_tunnels[_endTunnelIndex]);
		_tunnels[_currentTunnelIndex]->Reset();
		_endTunnelIndex = _currentTunnelIndex;
		_currentTunnelIndex++;
		if (_currentTunnelIndex > _tunnels.size() - 1)
		{
			_currentTunnelIndex = 0;
		}
		_tunnels[_currentTunnelIndex]->SetPrevious(NULL);
		_tunnelsPastThrough++;

		if (_tunnels[_currentTunnelIndex]->GetTunnelType() == TunnelType::Left ||
			_tunnels[_currentTunnelIndex]->GetTunnelType() == TunnelType::Right)
		{
			_startingAngle = _tunnels[_currentTunnelIndex]->GetLocalAngle().y;
		}
		else
		{
			_tunnels[_currentTunnelIndex]->SetPosition(glm::vec3(0, 0, _tunnels[_currentTunnelIndex]->GetLocalPosition().z));
			_tunnels[_currentTunnelIndex]->SetAngle(glm::vec3(_tunnels[_currentTunnelIndex]->GetAngle().x, 0, _tunnels[_currentTunnelIndex]->GetAngle().z));
		}
		for (Tunnel* tun : _tunnels)
		{
			if (_velocity.z > -40.0f)
				_velocity.z -= 0.05f;
			tun->UpdatePhysics(_velocity);
		}
	}

	if (_tunnels[_currentTunnelIndex]->GetTunnelType() == TunnelType::Left)
	{
		if (_tunnels[_currentTunnelIndex]->GetLocalAngle().y < _startingAngle + 90)
		{
			float angleSpeed = 90.0f / (2.0f * _scale.z / _velocity.z);
			_tunnels[_currentTunnelIndex]->SetAngle(_tunnels[_currentTunnelIndex]->GetAngle() + glm::vec3(0, -angleSpeed, 0) * (float)deltaTime);
		}

	}
	else if (_tunnels[_currentTunnelIndex]->GetTunnelType() == TunnelType::Right)
	{
		if (_tunnels[_currentTunnelIndex]->GetLocalAngle().y > _startingAngle - 90)
		{
			float angleSpeed = 90.0f / (2.0f * _scale.z / _velocity.z);
			_tunnels[_currentTunnelIndex]->SetAngle(_tunnels[_currentTunnelIndex]->GetAngle() + glm::vec3(0, angleSpeed, 0) * (float)deltaTime);
		}
	}
}

void TunnelLevel::End()
{
}

void TunnelLevel::Reset()
{
}

void TunnelLevel::ResetSpeed()
{
	_velocity = glm::vec3(0, 0, -3);
	for (Tunnel* tun : _tunnels)
	{
		tun->UpdatePhysics(_velocity);
	}
}
