#include "Game.h"
#include "MouseMoveMessage.h"
#include "MouseDownMessage.h"

Game* Game::TheGame = NULL;

Game::Game()
	: _quitFlag(false),
	_sceneManager(this)
{
	for (int i = 0; i < 256; i++) _keyStates[i] = false;
	_currentTime = clock();

	Game::TheGame = this;
}


Game::~Game()
{
	for (MeshMapIterator i = _meshes.begin(); i != _meshes.end(); ++i)
	{
		delete i->second;
	}
	_meshes.clear();
}

void Game::Initialise(Window* w)
{
	_window = w;
	_renderer = w->GetRenderer();

	_renderSystem.SetRenderer(_renderer);
}

void Game::OnKeyboard(int key, bool down)
{
	

	// Create keypress message and send it to all objects
	KeyPressMessage msg(key, down);

	BroadcastMessage(&msg);

	_keyStates[key] = down;
}

void Game::OnMouseMove(float x, float y)
{
	x = 2 * x / 1280.0f - 1;
	y = -2 * y / 720.0f + 1;

	_mousePosition = glm::vec3(x, y, 1);

	glm::mat4 mouseMat = glm::inverse( GetSceneManager()->GetCamera()->GetProjectionMatrix() * GetSceneManager()->GetCamera()->GetViewMatrix());
	_mousePosition = glm::vec3(mouseMat * glm::vec4(_mousePosition, 0));

	MouseMoveMessage msg(_mousePosition);
	BroadcastMessage(&msg);
}

void Game::OnMouseDown(float x, float y, int button)
{
	//x = x / 1280.0f - 1;
	//y = y / 720.0f + 1;
	//glm::vec3 mousePosition = glm::vec3(x, y, 1);

	//glm::mat4 mouseMat = glm::inverse(GetSceneManager()->GetCamera()->GetOrthoMatrix() * GetSceneManager()->GetCamera()->GetViewMatrix());
	//mousePosition = glm::vec3(mouseMat * glm::vec4(_mousePosition, 0));

	//mousePosition.x -= -1280.0f / 2;
	//mousePosition.y -= -720.0f / 2;
	
	MouseDownMessage msg(x, y, button);
	BroadcastMessage(&msg);
}

void Game::Run()
{
	// Get delta time
	double temp_time = clock();
	_deltaTime = (temp_time - _currentTime) / CLOCKS_PER_SEC;
	_currentTime = temp_time;
}

void Game::BroadcastMessage(Message* msg)
{
	ListenToMessage(msg);

	_sceneManager.OnMessage(msg);
}