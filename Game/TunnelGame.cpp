#pragma once
#include "TunnelGame.h"
#include "GameScene.h"
#include "Mesh.h"
#include "Texture_DX.h"
#include "Renderer_DX.h"
#include "ObjImporter.h"
#include "Font.h"
#include "MainMenuScene.h"
#include "SettingsFile.h"

TunnelGame::TunnelGame()
{
}


TunnelGame::~TunnelGame()
{
}

void TunnelGame::Initialise(Window* w)
{
	Game::Initialise(w);
	Renderer_DX* renderer_dx = (Renderer_DX*)_renderer;
	
	InitialiseSettings("settings.txt");

	//Mesh* triangle = new Mesh();
	//Vertex a = {  0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f };
	//Vertex b = {  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.1f, 1.0f };
	//Vertex c = { -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f };
	//triangle->AddVertex(c);
	//triangle->AddVertex(b);
	//triangle->AddVertex(a);
	//triangle->AddVertex(a);
	//triangle->AddVertex(b);
	//triangle->AddVertex(c);
	//triangle->CreateVBO(GetRenderer());
	//AddMesh("triangle", triangle);

	// Square Mesh
	Mesh* square = new Mesh();
	Vertex tl = { -0.5f,  0.5f, 0.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f };
	Vertex tr = {  0.5f,  0.5f, 0.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f };
	Vertex bl = { -0.5f, -0.5f, 0.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f };
	Vertex br = {  0.5f, -0.5f, 0.0f,-1.0f, -1.0f, -1.0f,  0.0f, 0.0f };
	square->AddVertex(br);
	square->AddVertex(bl);
	square->AddVertex(tl);
	square->AddVertex(tr);
	square->AddVertex(br);
	square->AddVertex(tl);
	square->CreateVBO(GetRenderer());
	AddMesh("square", square);

	// Font Textures
	Texture_DX* font8Bit = new Texture_DX();
	font8Bit->Initialisze(L"../Assets/Fonts/8BitOutline.dds");
	AddTexture("8Bit", font8Bit);

	// Test Texture
	Texture_DX* texture = new Texture_DX();
	texture->Initialisze(L"../Assets/Textures/texture.dds");
	AddTexture("texture", texture);

	// Tunnel Textures
	Texture_DX* curvedTexture = new Texture_DX();
	curvedTexture->Initialisze(L"../Assets/Textures/ltg.dds");
	AddTexture("curvedTexture", curvedTexture);

	Texture_DX* straightTexture = new Texture_DX();
	straightTexture->Initialisze(L"../Assets/Textures/tunnelGroove.dds");
	AddTexture("straightTexture", straightTexture);

	// Ship textures
	Texture_DX* ship_red = new Texture_DX();
	ship_red->Initialisze(L"../Assets/Textures/myship_red.dds");
	AddTexture("ship_red", ship_red);

	Texture_DX* ship_yellow = new Texture_DX();
	ship_yellow->Initialisze(L"../Assets/Textures/myship.dds");
	AddTexture("ship_yellow", ship_yellow);

	// Obstacle Texture
	Texture_DX* obstacleTexture = new Texture_DX();
	obstacleTexture->Initialisze(L"../Assets/Textures/obstacle_blue.dds");
	AddTexture("obstacle", obstacleTexture);

	Texture_DX* powerUpTexture = new Texture_DX();
	powerUpTexture->Initialisze(L"../Assets/Textures/obstacle.dds");
	AddTexture("powerUp", powerUpTexture);

	// Ship Mesh
	Mesh* ship = new Mesh();
	ship->ImportFromObj("../Assets/Models/myship3.obj");
	ship->CreateVBO(GetRenderer());
	AddMesh("ship", ship);

	// Tunnel Meshes
	Mesh* tunnel = new Mesh();
	tunnel->ImportFromObj("../Assets/Models/tunnelGrooveSplit.obj");
	tunnel->CreateVBO(GetRenderer());
	AddMesh("tunnel", tunnel);

	Mesh* curvedTunnel = new Mesh();
	curvedTunnel->ImportFromObj("../Assets/Models/LeftTurnGroove.obj");
	curvedTunnel->CreateVBO(GetRenderer());
	AddMesh("curvedTunnel", curvedTunnel);

	Mesh* curvedTunnelRight = new Mesh();
	curvedTunnelRight->ImportFromObj("../Assets/Models/rightTurnGrooveFlip.obj");
	curvedTunnelRight->CreateVBO(GetRenderer());
	AddMesh("curvedTunnelRight", curvedTunnelRight);

	// Obstacle Meshes
	Mesh* obstacles = new Mesh();
	obstacles->ImportFromObj("../Assets/Models/Obstacle.obj");
	obstacles->CreateVBO(GetRenderer());
	AddMesh("obstacle", obstacles);

	Mesh* obstacleVert = new Mesh();
	obstacleVert->ImportFromObj("../Assets/Models/obstacle_vert.obj");
	obstacleVert->CreateVBO(GetRenderer());
	AddMesh("obstacleVert", obstacleVert);

	//Power Up
	Mesh* powerUp = new Mesh();
	powerUp->ImportFromObj("../Assets/Models/power_up.obj");
	powerUp->CreateVBO(GetRenderer());
	AddMesh("powerUp", powerUp);

	// Button Textures
	Texture_DX* playButton = new Texture_DX();
	playButton->Initialisze(L"../Assets/Textures/Buttons/play.dds");
	AddTexture("btnPlay", playButton);

	Texture_DX* exitButton = new Texture_DX();
	exitButton->Initialisze(L"../Assets/Textures/Buttons/exit.dds");
	AddTexture("btnExit", exitButton);

	Texture_DX* versusButton = new Texture_DX();
	versusButton->Initialisze(L"../Assets/Textures/Buttons/versus.dds");
	AddTexture("btnVersus", versusButton);

	Texture_DX* scoresButton = new Texture_DX();
	scoresButton->Initialisze(L"../Assets/Textures/Buttons/scores.dds");
	AddTexture("btnScores", scoresButton);

	Texture_DX* keyboardButton = new Texture_DX();
	keyboardButton->Initialisze(L"../Assets/Textures/Buttons/keyboard.dds");
	AddTexture("btnKeyboard", keyboardButton);

	Texture_DX* keyboardPressedButton = new Texture_DX();
	keyboardPressedButton->Initialisze(L"../Assets/Textures/Buttons/keyboard_pressed.dds");
	AddTexture("btnKeyboardPressed", keyboardPressedButton);

	Texture_DX* mouseButton = new Texture_DX();
	mouseButton->Initialisze(L"../Assets/Textures/Buttons/mouse.dds");
	AddTexture("btnMouse", mouseButton);

	Texture_DX* mousePressedButton = new Texture_DX();
	mousePressedButton->Initialisze(L"../Assets/Textures/Buttons/mouse_pressed.dds");
	AddTexture("btnMousePressed", mousePressedButton);

	// Fonts
	Font* font = new Font(Game::TheGame->GetTexture("8Bit"), "../Assets/Fonts/fontData2.txt");
	AddFont("8Bit", font);

	//_sceneManager.PushScene(new GameScene());
	_sceneManager.PushScene(new MainMenuScene());
}

void TunnelGame::OnKeyboard(int key, bool down)
{
	Game::OnKeyboard(key, down);
	_sceneManager.OnKeyboard(key, down);
}

void TunnelGame::Render()
{
	// Clear screen
	_renderer->ClearScreen();

	_sceneManager.Render(&_renderSystem);

	// Swap buffers
	_renderer->SwapBuffers();
}

void TunnelGame::Run()
{
	// Run parent method to get delta time etc
	Game::Run();

	// Update scenes
	_sceneManager.Update(_deltaTime);

	// Check for exit
	if (_sceneManager.GetCurrentScene() == NULL)
	{
		SetQuitFlag(true);
	}

	// Draw
	Render();
}

void TunnelGame::InitialiseSettings(const std::string & filePath)
{
	// Set Defaults
	SettingsFile::Instance().SetValue("p1_up", "38");
	SettingsFile::Instance().SetValue("p1_down", "40");
	SettingsFile::Instance().SetValue("p1_left", "37");
	SettingsFile::Instance().SetValue("p1_right", "39");
	SettingsFile::Instance().SetValue("p2_up", "87");
	SettingsFile::Instance().SetValue("p2_down", "83");
	SettingsFile::Instance().SetValue("p2_left", "65");
	SettingsFile::Instance().SetValue("p2_right", "68");

	SettingsFile::Instance().SetValue("tunnelIncrement", "0.05");
	SettingsFile::Instance().SetValue("tunnelMaxVel", "40");
	// Parse custom settings
	SettingsFile::Instance().parseFile("settings.txt");
}
