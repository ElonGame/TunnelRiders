#include "NameEntryScene.h"
#include "SceneManager.h"
#include "Text.h"
#include "Game.h"
#include "HighScores.h"
#include "TextFieldInputController.h"
#include "ScoresScene.h"

NameEntryScene::NameEntryScene(int score1, int score2) : _p1Score(score1), _p2Score(score2)
{
}


NameEntryScene::~NameEntryScene()
{
}

void NameEntryScene::Initialise()
{
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



	Text* text = new Text(Game::TheGame->GetFont("8Bit"), "GAME OVER");
	text->SetPosition(glm::vec3(1280.0f / 2.0f, 60.0f, 1.0f));
	text->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	AddGameObject(text);

	if (_p2Score > 0)
	{
		Text* text2 = new Text(Game::TheGame->GetFont("8Bit"), "PLAYER 1 WINS");
		text2->SetPosition(glm::vec3(1280.0f / 2.0f, 120, 1.0f));
		text2->SetScale(glm::vec3(0.8f, 0.8f, 1.0f));

		if (_p2Score > _p1Score)
			text2->SetText("PLAYER 2 WINS");
		else if (_p2Score == _p1Score)
			text2->SetText("DRAW");

		AddGameObject(text2);
	}

	_prompt = new Text(Game::TheGame->GetFont("8Bit"), "ENTER YOUR NAME");
	_prompt->SetPosition(glm::vec3(1280.0f / 2.0f, 720.0f / 2.0f - 60.0f, 1.0f));
	_prompt->SetScale(glm::vec3(0.7f, 0.7f, 1.0f));
	AddGameObject(_prompt);

	if (_p2Score > 0)
	{
		_prompt->SetText("PLAYER 1 ENTER YOUR NAME");
	}

	_scores = HighScores::ReadHighScores("highscores.txt");

	_input = new Text(Game::TheGame->GetFont("8Bit"), "");
	_input->SetPosition(glm::vec3(1280.0f / 2.0f, 720.0f / 2.0f + 20.0f, 1.0f));
	_input->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	TextFieldInputController* tc = new TextFieldInputController(_input);
	AddGameObject(_input);

	_player1Name = "";
	_player2Name = "";

	for (int i = 0; i < (int)_gameObjects.size(); i++)
	{
		_gameObjects[i]->Start();
	}
}

void NameEntryScene::OnKeyboard(int key, bool down)
{
	if (key == 13)
	{
		if (Game::TheGame->GetPreviousKeyState(key)) return;
		if (_input->GetText() != "")
		{
			if (_player1Name == "")
			{
				_player1Name = _input->GetText();
				_input->SetText("");
				_scores.push_back(std::pair<std::string, int>(_player1Name, _p1Score));
				_scores = HighScores::Sort(_scores);
				if (_p2Score > 0)
				{
					_prompt->SetText("PLAYER 2 ENTER YOUR NAME");
				}
				else
				{
					HighScores::WriteHighScores(_scores, "highscores.txt");
					_sceneManager->PopScene();
					_sceneManager->PushScene(new ScoresScene(_scores));
				}
			}
			else
			{
				_player2Name = _input->GetText();
				_scores.push_back(std::pair<std::string, int>(_player2Name, _p2Score));
				_scores = HighScores::Sort(_scores);
				HighScores::WriteHighScores(_scores, "highscores.txt");
				_sceneManager->PopScene();
				_sceneManager->PushScene(new ScoresScene(_scores));
			}
		}
	}
}

void NameEntryScene::OnMessage(Message * msg)
{
	Scene::OnMessage(msg);
}

void NameEntryScene::Update(double deltaTime)
{
	Scene::Update(deltaTime);

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

void NameEntryScene::Render(RenderSystem * renderer)
{
	renderer->Process(_gameObjects, 0);
}

void NameEntryScene::Reset()
{
}
