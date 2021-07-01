#pragma once

#include "textures.h"

const enum Type { HIT, STAND, BET, DOUBLE_DOWN, SURRENDER, SPLIT };

class Buttons : public Textures
{
public:
	Buttons();
	~Buttons();

	bool isPressed();
	bool isIntersecting(); //Checks if cursors are intersecting

	void update();

private:
	static const int BUTTONS_HEIGHT;
	static const int BUTTONS_WIDTH;
}; 