#include "ControlSelectScene.h"
#include "SceneManager.h"
#include "Text.h"
#include "Game.h"
#include "Button.h"
#include "GameScene.h"




ControlSelectScene::ControlSelectScene(bool twoPlayers) : _twoPlayers(twoPlayers), _p1Controls(ControlScheme::Keyboard1), _p2Controls(ControlScheme::Keyboard2)
{
}


ControlSelectScene::~ControlSelectScene()
{
}

void ControlSelectScene::Initialise()
{
	_yPos = 1.0f;

	_ship = new GameObject("demoShip");
	RenderComponent* rc = new RenderComponent(_ship);
	rc->SetMesh(Game::TheGame->GetMesh("ship"));
	rc->SetTexture(Game::TheGame->GetTexture("ship_yellow"));
	_ship->SetAngle(glm::vec3(0, 135, 0));
	_ship->SetPosition(glm::vec3(5, -3.5, 7.0f));
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

	Text* text2 = new Text(Game::TheGame->GetFont("8Bit"), "SELECT CONTROLS");
	text2->SetPosition(glm::vec3(1280.0f / 2.0f, 120, 1.0f));
	text2->SetScale(glm::vec3(0.7f, 0.7f, 1.0f));
	AddGameObject(text2);

	_playButton = new Button(Game::TheGame->GetMesh("square"), Game::TheGame->GetTexture("btnPlay"),
		glm::vec3(1280.0f / 2.0f, 620, 1.0f), glm::vec3(300, 100, 1));
	AddGameObject(_playButton);

	// Cached button states
	_buttonStates = { false, false, false, false, false, false };

	// Button placement coords
	float x = 1280.0f / 2.0f;
	float y = 720.0f / 2.0f;

	// If versus mode, place player 2 options buttons
	if (_twoPlayers)
	{
		// offset player 2 buttons
		x = 1000;
		y = 720.0f / 2.0f - 20.0f;

		_p2Key1 = new Button(Game::TheGame->GetMesh("square"), Game::TheGame->GetTexture("btnKeyboard"), Game::TheGame->GetTexture("btnKeyboardPressed"),
			glm::vec3(x - 110.0f, y, 1.0f), glm::vec3(100, 100, 1));
		AddGameObject(_p2Key1);

		_p2Key2 = new Button(Game::TheGame->GetMesh("square"), Game::TheGame->GetTexture("btnKeyboard"), Game::TheGame->GetTexture("btnKeyboardPressed"),
			glm::vec3(x + 110.0f, y, 1.0f), glm::vec3(100, 100, 1));
		AddGameObject(_p2Key2);
		_p2Key2->Press(true);
		_buttonStates[4] = true;

		_p2Mouse = new Button(Game::TheGame->GetMesh("square"), Game::TheGame->GetTexture("btnMouse"), Game::TheGame->GetTexture("btnMousePressed"),
			glm::vec3(x, y, 1.0f), glm::vec3(100, 100, 1));
		AddGameObject(_p2Mouse);

		// offset player 1 buttons
		x = 280;
	}

	// Place player 1 buttons
	_p1Key1 = new Button(Game::TheGame->GetMesh("square"), Game::TheGame->GetTexture("btnKeyboard"), Game::TheGame->GetTexture("btnKeyboardPressed"),
		glm::vec3(x - 110.0f, y, 1.0f), glm::vec3(100, 100, 1));
	AddGameObject(_p1Key1);
	_p1Key1->Press(true);
	_buttonStates[0] = true;

	_p1Key2 = new Button(Game::TheGame->GetMesh("square"), Game::TheGame->GetTexture("btnKeyboard"), Game::TheGame->GetTexture("btnKeyboardPressed"),
		glm::vec3(x + 110.0f, y, 1.0f), glm::vec3(100, 100, 1));
	AddGameObject(_p1Key2);

	_p1Mouse = new Button(Game::TheGame->GetMesh("square"), Game::TheGame->GetTexture("btnMouse"), Game::TheGame->GetTexture("btnMousePressed"),
		glm::vec3(x, y, 1.0f), glm::vec3(100, 100, 1));
	AddGameObject(_p1Mouse);

	for (int i = 0; i < (int)_gameObjects.size(); i++)
	{
		_gameObjects[i]->Start();
	}
}

void ControlSelectScene::OnKeyboard(int key, bool down)
{
	switch (key)
	{
	case 27:
		_sceneManager->PopScene();
		break;
	default:
		break;
	}
}

void ControlSelectScene::OnMessage(Message * msg)
{
	Scene::OnMessage(msg);
}

void ControlSelectScene::Update(double deltaTime)
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
		_sceneManager->PopScene();
		_sceneManager->PushScene(new GameScene(_twoPlayers, _p1Controls, _p2Controls));
	}

	if (_twoPlayers)
	{
		// Check state change
		if (_buttonStates[0] != _p1Key1->IsPressed())
		{
			// If changed to true
			if (_p1Key1->IsPressed())
			{
				// Check if other player isn't using the same scheme
				if (_p2Controls == ControlScheme::Keyboard1)
				{
					_p1Key1->Press(false);
				}
				// If it isn't turn the other buttons off and set the control scheme
				else
				{
					_p1Key2->Press(false);
					_p1Mouse->Press(false);
					_p1Controls = ControlScheme::Keyboard1;
				}
			}
			_buttonStates[0] = _p1Key1->IsPressed();
		}

		if (_buttonStates[1] != _p1Key2->IsPressed())
		{
			if (_p1Key2->IsPressed())
			{
				if (_p2Controls == ControlScheme::Keyboard2)
				{
					_p1Key2->Press(false);
				}
				else
				{
					_p1Key1->Press(false);
					_p1Mouse->Press(false);
					_p1Controls = ControlScheme::Keyboard2;
				}
			}
			_buttonStates[1] = _p1Key2->IsPressed();
		}

		if (_buttonStates[2] != _p1Mouse->IsPressed())
		{
			if (_p1Mouse->IsPressed())
			{
				if (_p2Controls == ControlScheme::Mouse)
				{
					_p1Mouse->Press(false);
				}
				else
				{
					_p1Key1->Press(false);
					_p1Key2->Press(false);
					_p1Controls = ControlScheme::Mouse;
				}
			}
			_buttonStates[2] = _p1Mouse->IsPressed();
		}



		// Check state change
		if (_buttonStates[3] != _p2Key1->IsPressed())
		{
			// If changed to true
			if (_p2Key1->IsPressed())
			{
				// Check if other player isn't using the same scheme
				if (_p1Controls == ControlScheme::Keyboard1)
				{
					_p2Key1->Press(false);
				}
				// If it isn't turn the other buttons off and set the control scheme
				else
				{
					_p2Key2->Press(false);
					_p2Mouse->Press(false);
					_p2Controls = ControlScheme::Keyboard1;
				}
			}
			_buttonStates[3] = _p2Key1->IsPressed();
		}

		if (_buttonStates[4] != _p2Key2->IsPressed())
		{
			if (_p2Key2->IsPressed())
			{
				if (_p1Controls == ControlScheme::Keyboard2)
				{
					_p2Key2->Press(false);
				}
				else
				{
					_p2Key1->Press(false);
					_p2Mouse->Press(false);
					_p2Controls = ControlScheme::Keyboard2;
				}
			}
			_buttonStates[4] = _p2Key2->IsPressed();
		}

		if (_buttonStates[5] != _p2Mouse->IsPressed())
		{
			if (_p2Mouse->IsPressed())
			{
				if (_p1Controls == ControlScheme::Mouse)
				{
					_p2Mouse->Press(false);
				}
				else
				{
					_p2Key1->Press(false);
					_p2Key2->Press(false);
					_p2Controls = ControlScheme::Mouse;
				}
			}
			_buttonStates[5] = _p2Mouse->IsPressed();
		}
	}
	else
	{
		if (_buttonStates[0] != _p1Key1->IsPressed())
		{
			_buttonStates[0] = _p1Key1->IsPressed();
			if (_buttonStates[0])
			{
				_p1Key2->Press(false);
				_p1Mouse->Press(false);
				_p1Controls = ControlScheme::Keyboard1;
			}
		}

		if (_buttonStates[1] != _p1Key2->IsPressed())
		{
			_buttonStates[1] = _p1Key2->IsPressed();
			if (_buttonStates[1])
			{
				_p1Key1->Press(false);
				_p1Mouse->Press(false);
				_p1Controls = ControlScheme::Keyboard2;
			}
		}

		if (_buttonStates[2] != _p1Mouse->IsPressed())
		{
			_buttonStates[2] = _p1Mouse->IsPressed();
			if (_buttonStates[2])
			{
				_p1Key1->Press(false);
				_p1Key2->Press(false);
				_p1Controls = ControlScheme::Mouse;
			}
		}
	}


	//_physicsSystem.Process(_gameObjects, deltaTime);
	//_collisionSystem.Process(_gameObjects, deltaTime);
}

void ControlSelectScene::Render(RenderSystem * renderer)
{
	renderer->Process(_gameObjects, 0);
}

void ControlSelectScene::Reset()
{
}
