#pragma once
#include "GameObject.h"
#include "Mesh.h"
#include "RenderComponent.h"
#include <string>
#include "Font.h"

class Text :
	public GameObject
{
public:
	Text(Font* font, const std::string & text, Alignment::Alignment alignment = Alignment::Center, bool cache = true);
	virtual ~Text();

	void SetText(const std::string & text, Alignment::Alignment alignment = Alignment::Center);
	std::string GetText() const { return _text; }

protected:
	Font* _font;
	RenderComponent* _rc;
	std::string _text;
	Mesh* _mesh;
	bool _cache;
};

