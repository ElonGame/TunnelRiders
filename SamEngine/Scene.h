#pragma once
#include <vector>
#include "Camera.h"

// Forward Declarations
class GameObject;
class RenderSystem;
class SceneManager;
class Message;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	void AddGameObject(GameObject* obj) { _gameObjects.push_back(obj); }
	std::vector<GameObject*>& GetGameObjects() { return _gameObjects; }

	void SetSceneManager(SceneManager* s) { _sceneManager = s; }
	SceneManager* GetSceneManager()	const { return _sceneManager; }
	Camera* GetCamera() const { return _camera; }

	virtual void Initialise() = 0;
	virtual void OnKeyboard(int key, bool down) = 0;
	virtual void OnMessage(Message* msg);
	virtual void Update(double deltaTime);
	virtual void Render(RenderSystem* renderer) = 0;

protected:
	SceneManager* _sceneManager;
	std::vector<GameObject*> _gameObjects;
	
	Camera* _camera;
};

