#pragma once
#include <stack>
#include <vector>
#include "Camera.h"

// Forward Declarations
class RenderSystem;
class Scene;
class Game;
class GameObject;
class Message;

class SceneManager
{
public:
	SceneManager(Game* _game);
	~SceneManager();

	Scene* GetCurrentScene() const { if (_scenes.size() > 0) return _scenes.top(); else return NULL; }
	Game* GetGame() const { return _game; }
	Camera* GetCamera() const;

	void PopScene() { _scenes.pop(); }
	void PushScene(Scene* s);

	void AddGameObject(GameObject* obj);
	std::vector<GameObject*>& GetGameObjects();

	void OnKeyboard(int key, bool down);
	void OnMessage(Message* msg);
	void Update(double deltaTime);
	void Render(RenderSystem* renderer);

protected:
	Game* _game;
	std::stack<Scene*> _scenes;
};

