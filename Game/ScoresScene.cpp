#include "ScoresScene.h"
#include "SceneManager.h"
#include "Text.h"
#include "Game.h"
#include "HighScores.h"
#include "TextFieldInputController.h"


ScoresScene::ScoresScene()
{
}

ScoresScene::ScoresScene(std::vector<std::pair<std::string, int>> scores) : _scores(scores)
{
}


ScoresScene::~ScoresScene()
{
}

void ScoresScene::Initialise()
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



	Text* text = new Text(Game::TheGame->GetFont("8Bit"), "TUNNEL RIDERS");
	text->SetPosition(glm::vec3(1280.0f / 2.0f, 60.0f, 1.0f));
	text->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	AddGameObject(text);

	Text* text2 = new Text(Game::TheGame->GetFont("8Bit"), "HIGH SCORES");
	text2->SetPosition(glm::vec3(1280.0f / 2.0f, 120, 1.0f));
	text2->SetScale(glm::vec3(0.8f, 0.8f, 1.0f));
	AddGameObject(text2);


	if (_scores.size() <= 0)
	{
		_scores = HighScores::ReadHighScores("highscores.txt");
	}

	std::vector<Text*> nameTexts;
	std::vector<Text*> scoreTexts;
	float nameX = 1280.0f / 2.0f - 10.0f;
	float scoreX = 1280.0f / 2.0f + 10.0f;
	float y = 220.0f;

	int count = glm::min(5, (int)_scores.size());
	for (int i = 0; i < count; i++)
	{
		std::string name = _scores[i].first;
		int score = _scores[i].second;

		nameTexts.push_back(new Text(Game::TheGame->GetFont("8Bit"), name, Alignment::Right));
		nameTexts[i]->SetPosition(glm::vec3(nameX, y, 1.0f));
		nameTexts[i]->SetScale(glm::vec3(0.7f, 0.7f, 1.0f));
		AddGameObject(nameTexts[i]);

		scoreTexts.push_back(new Text(Game::TheGame->GetFont("8Bit"), std::to_string(score), Alignment::Left));
		scoreTexts[i]->SetPosition(glm::vec3(scoreX, y, 1.0f));
		scoreTexts[i]->SetScale(glm::vec3(0.7f, 0.7f, 1.0f));
		AddGameObject(scoreTexts[i]);

		y += 100.0f;
	}

	for (int i = 0; i < (int)_gameObjects.size(); i++)
	{
		_gameObjects[i]->Start();
	}
}

void ScoresScene::OnKeyboard(int key, bool down)
{
	if (!Game::TheGame->GetPreviousKeyState(key))
		_sceneManager->PopScene();
}

void ScoresScene::OnMessage(Message * msg)
{
	Scene::OnMessage(msg);
}

void ScoresScene::Update(double deltaTime)
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

void ScoresScene::Render(RenderSystem * renderer)
{
	renderer->Process(_gameObjects, 0);
}

void ScoresScene::Reset()
{
}
