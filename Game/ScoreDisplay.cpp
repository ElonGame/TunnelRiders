#include "ScoreDisplay.h"
#include <string>



ScoreDisplay::ScoreDisplay(Ship* ship, Font* font, Alignment::Alignment alignment) : Text(font, std::to_string(ship->GetScore()), alignment, false), _ship(ship), _alignment(alignment)
{
}


ScoreDisplay::~ScoreDisplay()
{
}

void ScoreDisplay::Update(double deltaTime)
{
	if (_mesh != NULL)
	{
		delete _mesh;
	}
	SetText(std::to_string(_ship->GetScore()), _alignment);
}
