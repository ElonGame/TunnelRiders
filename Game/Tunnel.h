#pragma once
#include "GameObject.h"
#include "Mesh.h"
#include "Texture.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "Obstacle.h"
#include "PowerUp.h"

enum TunnelType
{
	Straight,
	Left,
	Right,
};

class Tunnel :
	public GameObject
{
public:
	Tunnel(TunnelType, Mesh*, Texture*, Tunnel*);
	virtual ~Tunnel();

	void PlaceTunnel();

	virtual void Start();
	virtual void Update(double deltaTime);
	virtual void OnMessage(Message* msg);
	virtual void End();
	virtual void Reset();

	TunnelType GetTunnelType() const { return _tunnelType; }
	void SetPrevious(Tunnel* prev) { _previousTunnel = prev; }

	void SetupTunnelType(TunnelType type);

	void UpdatePhysics(glm::vec3 vel);

protected:
	Mesh* _mesh;
	Texture* _texture;

	TunnelType _tunnelType;
	Tunnel* _previousTunnel;

	Mesh* _leftMesh;
	Mesh* _rightMesh;
	Mesh* _straightMesh;
	Texture* _curvedTexture;
	Texture* _straightTexture;

	PhysicsComponent* _pc;
	RenderComponent* _rc;
	glm::vec3 _velocity;

	Obstacle* _obstacle;
	PowerUp* _powerUp;
};

