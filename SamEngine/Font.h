#pragma once
#include <string>
#include <map>
#include "Texture.h"
#include "Mesh.h"

namespace Alignment
{
	enum Alignment
	{
		Center,
		Left, 
		Right
	};
}

struct CharacterUVDetails
{
	float leftUV;
	float rightUV;
	float characterWidth;
	float characterHeight;
};

typedef std::map<char, CharacterUVDetails> CharacterMap;

typedef std::map<std::string, Mesh*> MeshMap;
typedef std::map<std::string, Mesh*>::iterator MeshMapIterator;


class Font
{
public:
	Font(Texture* fontTexture, const std::string &fontDataFile = "");
	~Font();

	void LoadFromFile(const std::string &filePath);
	
	Texture* GetFontTexture() const { return _fontTexture; }

	/// If you do not cache then it is your responsibilty to delete the mesh once done with it
	Mesh* CreateMesh(const std::string &text, Alignment::Alignment alignment = Alignment::Center ,bool cache = true);

protected:

	void AddChar(char character, CharacterUVDetails details) { _chars[character] = details; }

	Mesh* emptyMesh();

	Mesh* GetFontMesh(std::string text);

	Texture* _fontTexture;
	Mesh* _baseMesh;

	CharacterMap _chars;
	MeshMap _meshCache;

	float _maxCharWidth;
	float _maxCharHeight;
};

inline Mesh* Font::GetFontMesh(std::string text)
{
	// Found
	MeshMapIterator i = _meshCache.find(text);
	if (i != _meshCache.end())
	{
		return i->second;
	}
	// Not found
	return NULL;
}

