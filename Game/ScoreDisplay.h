#pragma once
#include "Text.h"
#include "Ship.h"

class ScoreDisplay :
	public Text
{
public:
	ScoreDisplay(Ship* ship, Font* font, Alignment::Alignment alignment = Alignment::Center);
	virtual ~ScoreDisplay();

	virtual void Update(double deltaTime);

protected:
	Ship* _ship;
	Alignment::Alignment _alignment;
};

