#pragma once
#include "Scene.h"
#include "GameScene.h"
#include "GameObject.h"
#include "Components.h"
#include "SceneManager.h"
#include "Game.h"
#include "Tunnel.h"
#include "CollisionMatrix.h"
#include "Font.h"
#include "ScoreDisplay.h"
#include "PauseScene.h"
#include "Button.h"
#include "NameEntryScene.h"

GameScene::GameScene(bool twoPlayers, ControlScheme p1, ControlScheme p2) : Scene(), _twoPlayers(twoPlayers), _p1(p1), _p2(p2)
{
}


GameScene::~GameScene()
{
	delete _level;
}

void GameScene::Initialise()
{
	_physicsSystem = PhysicsSystem();
	_collisionSystem = CollisionSystem();

	_ship = new Ship(glm::vec3(0, -0.5, 5), _p1);
	AddGameObject(_ship);

	if (_twoPlayers)
	{
		_ship2 = new Ship(glm::vec3(0, -3, 5), _p2, true);
		AddGameObject(_ship2);
	}

	_level = new TunnelLevel();
	for (Tunnel* tunnel : _level->_tunnels)
	{
		AddGameObject(tunnel);
	}

	_tunnelCollider = new GameObject("tunnelCollider");
	InverseCircleColliderComponent* icc = new InverseCircleColliderComponent(_tunnelCollider, 3.5f);
	icc->SetCollisionID(CollisionID::Tunnel_ID);
	icc->SetCollisionMatrixFlag(CollisionID::Ship_ID);
	AddGameObject(_tunnelCollider);

	// 2D Game Object Only beyond this point
	ScoreDisplay* scoreDisplay1 = new ScoreDisplay(_ship, Game::TheGame->GetFont("8Bit"), Alignment::Left);
	scoreDisplay1->SetPosition(glm::vec3(0, 40.0f, 1.0f));
	scoreDisplay1->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	AddGameObject(scoreDisplay1);
	if (_twoPlayers)
	{
		ScoreDisplay* scoreDisplay2 = new ScoreDisplay(_ship2, Game::TheGame->GetFont("8Bit"), Alignment::Right);
		scoreDisplay2->SetPosition(glm::vec3(1280.0f, 40.0f, 1.0f));
		scoreDisplay2->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
		AddGameObject(scoreDisplay2);
	}

	for (int i = 0; i < (int)_gameObjects.size(); i++)
	{
		_gameObjects[i]->Start();
	}

	// Debug Cameras
	//_camera->SetPosition(glm::vec3(0, 0, -20));
	//_camera->SetPosition(glm::vec3(0, 90, 0));
	//_camera->SetAngle(glm::vec3(90, 0, 0));
}

void GameScene::OnKeyboard(int key, bool down)
{
	switch (key)
	{
	case 80:
		_sceneManager->PushScene(new PauseScene());
		break;
	case 27:
		_sceneManager->PopScene();
		break;
	default:
		break;
	}
}

void GameScene::OnMessage(Message * msg)
{
	Scene::OnMessage(msg);

	if (msg->GetMessageType() == "tunnelSpeedMessage")
	{
		_level->ResetSpeed();
	}
}

void GameScene::Update(double deltaTime)
{
	Scene::Update(deltaTime);
	_level->Update(deltaTime);

	for (GameObject* obj : _gameObjects)
	{
		if (obj->IsAlive())
		{
			obj->Update(deltaTime);
		}
	}

	if (_ship->Dead())
	{
		if (_twoPlayers)
		{
			if (_ship2->Dead())
			{
				_sceneManager->PopScene();
				_sceneManager->PushScene(new NameEntryScene(_ship->GetScore(), _ship2->GetScore()));
			}
		}
		else
		{
			_sceneManager->PopScene();
			_sceneManager->PushScene(new NameEntryScene(_ship->GetScore(), 0));
		}
	}

	_physicsSystem.Process(_gameObjects, deltaTime);
	_collisionSystem.Process(_gameObjects, deltaTime);
}

void GameScene::Render(RenderSystem* renderer)
{
	renderer->Process(_gameObjects, 0);
}

void GameScene::Reset()
{

}
