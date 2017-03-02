#pragma once
#include "GameObject.h"
#include <vector>
#include "Tunnel.h"
#include "PhysicsComponent.h"
#include "Mesh.h"
#include "Texture.h"
// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"


typedef std::vector<Tunnel*> TunnelList;

class TunnelLevel
{
public:
	TunnelLevel();
	virtual ~TunnelLevel();


	//glm::vec3 Velocity() const { return _physicsComponent->GetVelocity(); }
	//void Velocity(glm::vec3 vel)  { _physicsComponent->SetVelocity(vel); }

	virtual void Start();
	virtual void Update(double deltaTime);
	virtual void End();
	virtual void Reset();

	void ResetSpeed();

	TunnelList _tunnels;

protected:
	int _currentTunnelIndex;
	int _endTunnelIndex;
	//PhysicsComponent* _physicsComponent;

	Mesh* _leftMesh;
	Mesh* _rightMesh;
	Mesh* _straightMesh;
	Texture* _curvedTexture;
	Texture* _straightTexture;

	glm::vec3 _scale;
	glm::vec3 _velocity;
	float _startingAngle;
	glm::vec3 _startingPosition;
	int _tunnelsPastThrough;

	float _tunnelVelIncrease;
	float _tunnelMaxVelocity;
};

