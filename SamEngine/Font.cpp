#pragma once
#include "Font.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Vertex.h"
#include "Game.h"


Font::Font(Texture* fontTexture, const std::string &fontDataFile) : _fontTexture(fontTexture)
{
	if (fontDataFile != "")
		LoadFromFile(fontDataFile);
}


Font::~Font()
{
	for (MeshMapIterator i = _meshCache.begin(); i != _meshCache.end(); ++i)
	{
		delete i->second;
	}
	_meshCache.clear();
}

void Font::LoadFromFile(const std::string & filePath)
{
	_chars.clear();
	_maxCharHeight = 0;
	_maxCharWidth = 0;

	// Open File
	std::ifstream file;
	file.open(filePath);

	// Parse File
	std::string line;
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			// Ignore comments
			if (line.substr(0, 2) == "//" || line.substr(0, 1) == "#") continue;

			// Containers
			char id;
			CharacterUVDetails details;

			// Get Data
			std::istringstream ss(line);
			ss >> id >> details.leftUV >> details.rightUV >> details.characterWidth >> details.characterHeight;

			if (id == '_') id = ' ';
			AddChar(id, details);

			if (details.characterHeight > _maxCharHeight)
				_maxCharHeight = details.characterHeight;
			if (details.characterWidth > _maxCharWidth)
				_maxCharWidth = details.characterWidth;
		}
		file.close();
	}
}

Mesh* Font::CreateMesh(const std::string & text, Alignment::Alignment alignment, bool cache)
{
	Mesh* textMesh = NULL;
	if (cache)
		textMesh = GetFontMesh(text + std::to_string(alignment));
	if (textMesh == NULL)
	{
		textMesh = new Mesh();
		float lengthOfMesh = text.length() * _maxCharWidth;
		float heightOfMesh = _maxCharHeight;

		// Changing this to 0 = left aligned?
		// Changing this to -lengthOfMesh = right aligned?
		float startingPointX = -(lengthOfMesh / 2.0f);
		switch (alignment)
		{
		case Alignment::Center:
			startingPointX = -(lengthOfMesh / 2.0f);
			break;
		case Alignment::Left:
			startingPointX = -lengthOfMesh;
			break;
		case Alignment::Right:
			startingPointX = 0;
			break;
		default:
			break;
		}

		if (text.length() <= 0) return emptyMesh();
		
		// Adding verticies
		for (int i = text.length() - 1; i >= 0; i--)
		{
			CharacterUVDetails details;
			if (_chars.find(text[i]) == _chars.end()) {
				// not found use default
				details = _chars[0];
			}
			else {
				details = _chars[text[i]];
			}
			
			// Create Verticies
			Vertex tl = { startingPointX + _maxCharWidth,	heightOfMesh / 2.0f,	0.0f, -1.0f, -1.0f, -1.0f, details.leftUV,	1.0f };
			Vertex tr = { startingPointX ,					heightOfMesh / 2.0f,	0.0f, -1.0f, -1.0f, -1.0f, details.rightUV, 1.0f };
			Vertex bl = { startingPointX + _maxCharWidth,  -heightOfMesh / 2.0f,	0.0f, -1.0f, -1.0f, -1.0f, details.leftUV,	0.0f };
			Vertex br = { startingPointX ,				   -heightOfMesh / 2.0f ,	0.0f, -1.0f, -1.0f, -1.0f, details.rightUV, 0.0f };

			// Create Triangles
			textMesh->AddVertex(tl);
			textMesh->AddVertex(bl);
			textMesh->AddVertex(br);

			textMesh->AddVertex(tl);
			textMesh->AddVertex(br);
			textMesh->AddVertex(tr);

			// Increment starting point
			startingPointX += _maxCharWidth;
		}

		textMesh->CreateVBO(Game::TheGame->GetRenderer());
		if (cache)
			_meshCache[text + std::to_string(alignment)] = textMesh;
	}
	return textMesh;
}

Mesh * Font::emptyMesh()
{
	Mesh* square = new Mesh();
	Vertex tl = { -0.5f,  0.5f, 0.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f };
	Vertex tr = { 0.5f,  0.5f, 0.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f };
	Vertex bl = { -0.5f, -0.5f, 0.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f };
	Vertex br = { 0.5f, -0.5f, 0.0f,-1.0f, -1.0f, -1.0f,  0.0f, 0.0f };
	square->AddVertex(br);
	square->AddVertex(bl);
	square->AddVertex(tl);
	square->AddVertex(tr);
	square->AddVertex(br);
	square->AddVertex(tl);
	square->CreateVBO(Game::TheGame->GetRenderer());
	return square;
}
