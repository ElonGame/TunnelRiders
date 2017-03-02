#include "GameObject.h"
#include "GameObjectComponent.h"
#include "Message.h"
#include "GL\GLM\GTX\transform.hpp"
#include "GL\GLM\GTX\rotate_vector.hpp"

GameObject::GameObject(std::string type)
	: _angle(0.0f, 0.0f, 0.0f),
	_scale(1.0f, 1.0f, 1.0f),
	_position(0.0f, 0.0f, 0.0f),
	_alive(true),
	_type(type)
{
}


GameObject::~GameObject()
{
	End();
}

glm::vec3 GameObject::GetPosition() const
{
	if (!_parent)
	{
		return _position;
	}
	else
	{
		glm::vec3 parentToChild = -_position;
		parentToChild = glm::rotate(parentToChild, -_parent->GetAngle().z, glm::vec3(0, 0, 1));
		parentToChild = glm::rotate(parentToChild, -_parent->GetAngle().y, glm::vec3(0, 1, 0));
		parentToChild = glm::rotate(parentToChild, -_parent->GetAngle().x, glm::vec3(1, 0, 0));

		
		return _parent->GetPosition() + parentToChild;
	}
}

glm::vec3 GameObject::GetLocalPosition() const
{
	return _position;
}

glm::vec3 GameObject::GetScale() const
{
	if (!_parent)
	{
		return _scale;
	}
	else
	{
		return _parent->GetScale() + _scale;
	}
}

glm::vec3 GameObject::GetLocalScale() const
{
	return _scale;
}

glm::vec3 GameObject::GetAngle() const
{
	if (!_parent)
	{
		return _angle;
	}
	else
	{
		return _parent->GetAngle() + _angle;
	}
}

glm::vec3 GameObject::GetLocalAngle() const
{
	return _angle;
}

bool GameObject::AddComponent(GameObjectComponent* goc)
{
	if (_components.find(goc->GetComponentType()) != _components.end())
	{
		// Already have this component!
		return false;
	}
	_components[goc->GetComponentType()] = goc;

	return true;
}

bool GameObject::RemoveComponent(GameObjectComponent* goc)
{
	return RemoveComponent(goc->GetComponentType());
}

bool GameObject::RemoveComponent(std::string type)
{
	ComponentMapIterator i = _components.find(type);
	if (i != _components.end())
	{
		// Remove it
		_components.erase(i);

		// Delete it
		i->second->End();
		delete i->second;

		return true;
	}

	// Couldn't find it
	return false;
}

GameObjectComponent* GameObject::GetComponent(std::string type)
{
	ComponentMapIterator i = _components.find(type);
	if (i != _components.end())
	{
		// Return it
		return i->second;
	}

	// Couldn't find it
	return NULL;
}

void GameObject::Start()
{
	// Initialise all objects
	for (ComponentMapIterator i = _components.begin(); i != _components.end(); ++i)
	{
		i->second->Start();
	}
}

void GameObject::Update(double deltaTime)
{
	// Update all objects
	for (ComponentMapIterator i = _components.begin(); i != _components.end(); ++i)
	{
		i->second->Update(deltaTime);
	}
}

void GameObject::End()
{
	// End all objects
	for (ComponentMapIterator i = _components.begin(); i != _components.end(); ++i)
	{
		GameObjectComponent* component = i->second;
		component->End();
		delete component;
	}

	// Clear list
	_components.clear();
}

void GameObject::Reset()
{

}