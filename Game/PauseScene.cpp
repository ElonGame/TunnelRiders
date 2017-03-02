#include "PauseScene.h"
#include "SceneManager.h"
#include "Text.h"
#include "Game.h"

float lerp2(float v0, float v1, float t) {
	return (1 - t)*v0 + t*v1;
}


PauseScene::PauseScene() : Scene()
{
}


PauseScene::~PauseScene()
{
}

void PauseScene::Initialise()
{
	_yPos = 1.0f;

	_ship = new GameObject("demoShip");
	RenderComponent* rc = new RenderComponent(_ship);
	rc->SetMesh(Game::TheGame->GetMesh("ship"));
	rc->SetTexture(Game::TheGame->GetTexture("ship_yellow"));
	_ship->SetAngle(glm::vec3(0, 135, 0));
	_ship->SetPosition(glm::vec3(5, -3, 7.0f));
	AddGameObject(_ship);

	_ship2 = new GameObject("demoShip");
	RenderComponent* rc2 = new RenderComponent(_ship2);
	rc2->SetMesh(Game::TheGame->GetMesh("ship"));
	rc2->SetTexture(Game::TheGame->GetTexture("ship_red"));
	_ship2->SetAngle(glm::vec3(0, 225, 0));
	_ship2->SetPosition(glm::vec3(-5, -3.5, 7.0f));
	AddGameObject(_ship2);


	GameObject* tun = new GameObject("tun");
	RenderComponent* rc3 = new RenderComponent(tun);
	rc3->SetMesh(Game::TheGame->GetMesh("tunnel"));
	rc3->SetTexture(Game::TheGame->GetTexture("straightTexture"));
	tun->SetAngle(glm::vec3(0, 0, 0));
	tun->SetScale(glm::vec3(8, 8, 8));
	tun->SetPosition(glm::vec3(0, 0, 12.0f));
	AddGameObject(tun);
	GameObject* tun3 = new GameObject("tun");
	RenderComponent* rc5 = new RenderComponent(tun3);
	rc5->SetMesh(Game::TheGame->GetMesh("tunnel"));
	rc5->SetTexture(Game::TheGame->GetTexture("straightTexture"));
	tun3->SetAngle(glm::vec3(0, 0, 0));
	tun3->SetScale(glm::vec3(8, 8, 8));
	tun3->SetPosition(glm::vec3(0, 0, 42.0f));
	AddGameObject(tun3);
	GameObject* tun2 = new GameObject("tun");
	RenderComponent* rc4 = new RenderComponent(tun2);
	rc4->SetMesh(Game::TheGame->GetMesh("curvedTunnel"));
	rc4->SetTexture(Game::TheGame->GetTexture("curvedTexture"));
	tun2->SetAngle(glm::vec3(0, 0, 0));
	tun2->SetScale(glm::vec3(8, 8, 8));
	tun2->SetPosition(glm::vec3(24.0f, 0, 52.0f));
	AddGameObject(tun2);



	Text* text = new Text(Game::TheGame->GetFont("8Bit"), "PAUSED");
	text->SetPosition(glm::vec3(1280.0f / 2.0f, 720.0f / 2.0f - 30.0f, 1.0f));
	text->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	AddGameObject(text);

	Text* anyKey = new Text(Game::TheGame->GetFont("8Bit"), "PRESS ANY KEY");
	anyKey->SetPosition(glm::vec3(1280.0f / 2.0f, 720.0f / 2.0f + 30.0f, 1.0f));
	anyKey->SetScale(glm::vec3(0.5f, 0.5f, 1.0f));
	AddGameObject(anyKey);
}

void PauseScene::OnKeyboard(int key, bool down)
{
	if (key != 80)
		_sceneManager->PopScene();
}

void PauseScene::OnMessage(Message * msg)
{
	Scene::OnMessage(msg);
}

void PauseScene::Update(double deltaTime)
{
	Scene::Update(deltaTime);

	if (_ship->GetPosition().y < -4.0f)
		_yPos = 0.5f;
	else if (_ship->GetPosition().y > -2.5f)
		_yPos = -0.5f;

	_ship->SetPosition(glm::vec3(_ship->GetPosition().x, _ship->GetPosition().y + (_yPos * deltaTime), _ship->GetPosition().z));
	_ship2->SetPosition(glm::vec3(_ship2->GetPosition().x, _ship2->GetPosition().y + (_yPos * deltaTime), _ship2->GetPosition().z));

	for (GameObject* obj : _gameObjects)
	{
		if (obj->IsAlive())
		{
			obj->Update(deltaTime);
		}
	}

	//_physicsSystem.Process(_gameObjects, deltaTime);
	//_collisionSystem.Process(_gameObjects, deltaTime);
}

void PauseScene::Render(RenderSystem * renderer)
{
	renderer->Process(_gameObjects, 0);
}

void PauseScene::Reset()
{
}
