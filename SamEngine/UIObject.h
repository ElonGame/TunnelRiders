#pragma once
#include "GameObject.h"
#include "Components.h"
#include "Mesh.h"
#include "Texture.h"

class UIObject :
	public GameObject
{
public:
	UIObject(Mesh* mesh, Texture* texture, glm::vec3 position, glm::vec3 scale);
	virtual ~UIObject();

	virtual void Start();
	virtual void Update(double deltaTime);
	virtual void OnMessage(Message* msg) { BroadcastMessage(msg); }
	virtual void End();
	virtual void Reset();
};

