#pragma once
#include "GameObject.h"
#include "Mesh.h"
#include "Texture.h"
#include "PhysicsComponent.h"
#include "ShipControllerComponent.h"

// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"

class Ship :
	public GameObject
{
public:
	Ship(glm::vec3 position, ControlScheme controlsScheme, bool playerTwo = false);
	virtual ~Ship();

	virtual void Update(double deltaTime);
	virtual void OnMessage(Message* msg);
	virtual void Reset();

	void RevertToPreviousPosition() { _position = _previousPosition; }

	int GetScore() const { return (int)(_score * 100.0f); }
	void SetScorePerSecond(float sps) { _scorePerSecond = sps; }

	bool Dead() const { return _dead; }

protected:
	Mesh* _mesh;
	Texture* _texture;

	glm::vec3 _previousPosition;
	PhysicsComponent* _pc;
	float _speed;
	float _score;
	float _scorePerSecond;
	float _scoreMultiplier;
	float _scoreMultTimer;

	bool _dead;
};

