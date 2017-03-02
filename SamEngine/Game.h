#pragma once
#include <time.h>
#include <map>
#include <vector>

//#include "PhysicsSystem.h"
#include "RenderSystem.h"
//#include "CollisionSystem.h"
#include "Font.h"

#include "SceneManager.h"

#include "KeyPressMessage.h"
#include "Window.h"

// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"

// Forward declarations
class GameObject;
class Mesh;
class Texture;
class Message;
class Renderer;
class Window;

// Typedefs
typedef std::map<std::string, Mesh*> MeshMap;
typedef std::map<std::string, Mesh*>::iterator MeshMapIterator;

typedef std::map<std::string, Texture*> TextureMap;
typedef std::map<std::string, Texture*>::iterator TextureMapIterator;

typedef std::map<std::string, Font*> FontMap;
typedef std::map<std::string, Font*>::iterator FontMapIterator;

class Game
{

public:

	static Game* TheGame;

public:
	Game();
	virtual ~Game();

	Mesh* GetMesh(std::string name);
	void AddMesh(std::string name, Mesh* mesh) { _meshes[name] = mesh; }

	Texture* GetTexture(std::string name);
	void AddTexture(std::string name, Texture* texture) { _textures[name] = texture; }

	Font* GetFont(std::string name);
	void AddFont(std::string name, Font* font) { _fonts[name] = font; }

	// Quit flag
	bool GetQuitFlag() const { return _quitFlag; }
	void SetQuitFlag(bool v) { _quitFlag = v; }

	// Renderer
	Renderer* GetRenderer() const { return _renderer; }
	SceneManager* GetSceneManager() const { return (SceneManager*)&_sceneManager; }

	void AddGameObject(GameObject* obj) { _sceneManager.AddGameObject(obj); }
	std::vector<GameObject*>& GetGameObjects() { return _sceneManager.GetGameObjects(); }

	bool GetPreviousKeyState(int keycode) { return _keyStates[keycode]; }

	virtual void Initialise(Window* w);
	virtual void OnKeyboard(int key, bool down);
	virtual void OnMouseMove(float x, float y);
	virtual void OnMouseDown(float x, float y, int button);
	virtual void Render() = 0;

	// Main game loop (update)
	virtual void Run();

	// Message system
	void BroadcastMessage(Message* msg);
	virtual void ListenToMessage(Message* msg) {}

protected:
	double _currentTime;
	double _deltaTime;
	bool _keyStates[256];
	bool _quitFlag;
	Renderer* _renderer;
	Window* _window;
	MeshMap _meshes;		
	TextureMap _textures;
	FontMap _fonts;
	RenderSystem _renderSystem;
	SceneManager _sceneManager;

	glm::vec3 _mousePosition;
};

inline Mesh* Game::GetMesh(std::string name)
{
	// Found
	MeshMapIterator i = _meshes.find(name);
	if (i != _meshes.end())
	{
		return i->second;
	}
	// Not found
	return NULL;
}

inline Texture* Game::GetTexture(std::string name)
{
	// Found
	TextureMapIterator i = _textures.find(name);
	if (i != _textures.end())
	{
		return i->second;
	}
	// Not found
	return NULL;
}
inline Font* Game::GetFont(std::string name)
{
	// Found
	FontMapIterator i = _fonts.find(name);
	if (i != _fonts.end())
	{
		return i->second;
	}
	// Not found
	return NULL;
}

