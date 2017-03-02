#pragma once
#include "Text.h"


Text::Text(Font * font, const std::string & text, Alignment::Alignment alignment, bool cache) : GameObject("text"), _font(font), _text(text), _cache(cache)
{
	_rc = new RenderComponent(this);
	_rc->ShouldDraw(true);
	_rc->TwoDimensions(true);
	_rc->SetTexture(_font->GetFontTexture());
	_mesh = _font->CreateMesh(text, alignment, cache);
	_rc->SetMesh(_mesh);
}

Text::~Text()
{
	if (!_cache && _mesh != NULL) delete _mesh;
	_mesh = 0;
}

void Text::SetText(const std::string & text, Alignment::Alignment alignment)
{
	_text = text;
	_mesh = _font->CreateMesh(text, alignment, _cache);
	_rc->SetMesh(_mesh);
}
