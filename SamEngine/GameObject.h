#pragma once
#include <map>
#include <vector>
#include "ObserverSubject.h"

// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"

// Forward references
class GameObjectComponent;
class Message;

// Typedefs
typedef std::map<std::string, GameObjectComponent*> ComponentMap;
typedef std::map<std::string, GameObjectComponent*>::iterator ComponentMapIterator;
typedef std::vector<GameObjectComponent*>::iterator ComponentListIterator;

class GameObject
	: public ObserverSubject
{
public:
	GameObject(std::string type);
	virtual ~GameObject();

	glm::vec3 GetAngle() const;
	glm::vec3 GetLocalAngle() const;
	void SetAngle(glm::vec3 v) { _angle = v; }

	glm::vec3 GetScale() const;
	glm::vec3 GetLocalScale() const;
	void SetScale(glm::vec3 v) { _scale = v; }

	glm::vec3 GetPosition() const;
	glm::vec3 GetLocalPosition() const;
	void SetPosition(glm::vec3 v) { _position = v; }

	bool IsAlive() const { return _alive; }
	void SetAlive(bool v) { _alive = v; }

	bool ShouldBeDeleted() const { return _deleteFlag; }
	void SetDeleteFlag(bool v) { _deleteFlag = v; }

	std::string GetType() const { return _type; }

	bool AddComponent(GameObjectComponent* goc);
	bool RemoveComponent(GameObjectComponent* goc);
	bool RemoveComponent(std::string componentType);
	GameObjectComponent* GetComponent(std::string type);

	GameObject* Parent() const { return _parent; }
	void Parent(GameObject* parent) { _parent = parent; }

	virtual void Start();
	virtual void Update(double deltaTime);
	virtual void OnMessage(Message* msg) { BroadcastMessage(msg); }
	virtual void End();
	virtual void Reset();

protected:
	std::string	_type;
	glm::vec3 _angle;
	glm::vec3 _scale;
	glm::vec3 _position;
	bool _alive;
	bool _deleteFlag;

	ComponentMap _components;

	GameObject* _parent;

private:
	GameObject(const GameObject&);
	GameObject& operator=(const GameObject&);
};

