#include "MainMenuScene.h"
#include "SceneManager.h"
#include "ControlSelectScene.h"
#include "Text.h"
#include "Game.h"
#include "Button.h"
#include "GameScene.h"
#include "ScoresScene.h"
#include "NameEntryScene.h"

MainMenuScene::MainMenuScene()
{
}


MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::Initialise()
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
	tun->SetScale(glm::vec3(8, 8, 8));
	tun->SetPosition(glm::vec3(0, 0, 12.0f));
	AddGameObject(tun);
	GameObject* tun3 = new GameObject("tun");
	RenderComponent* rc5 = new RenderComponent(tun3);
	rc5->SetMesh(Game::TheGame->GetMesh("tunnel"));
	rc5->SetTexture(Game::TheGame->GetTexture("straightTexture"));
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


	Text* text = new Text(Game::TheGame->GetFont("8Bit"), "TUNNEL RIDERS");
	text->SetPosition(glm::vec3(1280.0f / 2.0f, 60.0f, 1.0f));
	text->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	AddGameObject(text);

	_playButton = new Button(Game::TheGame->GetMesh("square"), Game::TheGame->GetTexture("btnPlay"), 
		glm::vec3(1280.0f / 2.0f, 180.0f, 1.0f), glm::vec3(300, 100, 1));
	AddGameObject(_playButton);

	_versusButton = new Button(Game::TheGame->GetMesh("square"), Game::TheGame->GetTexture("btnVersus"),
		glm::vec3(1280.0f / 2.0f, 280.0f + 10.0f, 1.0f), glm::vec3(300, 100, 1));
	AddGameObject(_versusButton);

	_scoresButton = new Button(Game::TheGame->GetMesh("square"), Game::TheGame->GetTexture("btnScores"), 
		glm::vec3(1280.0f / 2.0f, 380.0f + 20.0f, 1.0f), glm::vec3(300, 100, 1));
	AddGameObject(_scoresButton);

	_exitButton = new Button(Game::TheGame->GetMesh("square"), Game::TheGame->GetTexture("btnExit"), 
		glm::vec3(1280.0f / 2.0f, 480.0f + 30.0f, 1.0f), glm::vec3(300, 100, 1));
	AddGameObject(_exitButton);

	for (int i = 0; i < (int)_gameObjects.size(); i++)
	{
		_gameObjects[i]->Start();
	}
}

void MainMenuScene::OnKeyboard(int key, bool down)
{
	//if (key == 27 && !Game::TheGame->GetPreviousKeyState(key))
		//_sceneManager->PopScene();
}

void MainMenuScene::OnMessage(Message * msg)
{
	Scene::OnMessage(msg);
}

void MainMenuScene::Update(double deltaTime)
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

	if (_playButton->IsPressed())
	{
		_playButton->Press(false);
		_sceneManager->PushScene(new ControlSelectScene(false));
	}
	if (_exitButton->IsPressed())
	{
		_exitButton->Press(false);
		_sceneManager->PopScene();
	}
	if (_versusButton->IsPressed())
	{
		_versusButton->Press(false);
		_sceneManager->PushScene(new ControlSelectScene(true));
	}
	if (_scoresButton->IsPressed())
	{
		_scoresButton->Press(false);
		_sceneManager->PushScene(new ScoresScene());
	}
	

	//_physicsSystem.Process(_gameObjects, deltaTime);
	//_collisionSystem.Process(_gameObjects, deltaTime);
}

void MainMenuScene::Render(RenderSystem * renderer)
{
	renderer->Process(_gameObjects, 0);
}

void MainMenuScene::Reset()
{
}
