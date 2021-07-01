#include "buttons.h"

const int Buttons::BUTTONS_HEIGHT = 57;
const int Buttons::BUTTONS_WIDTH = 152;

Buttons::Buttons()
{
	setSrc_h(BUTTONS_HEIGHT);
	setSrc_w(BUTTONS_WIDTH);
}

Buttons::~Buttons()
{
}

//Checks if player cursor on button and left click is pressed
bool Buttons::isPressed()
{
	return (isIntersecting() && SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1));
}

//Collision and intersection
bool Buttons::isIntersecting()
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	return (x > getPos_x() && x < getPos_x() + BUTTONS_WIDTH && 
			y > getPos_y() && y < getPos_y() + BUTTONS_HEIGHT);
}

//Changes the button when pressed
void Buttons::update()
{
	if (isPressed()) {
		setSrc_y(115);
	}
	else if (isIntersecting()) {
		setSrc_y(57);
	}
	else {
		setSrc_y(0);
	}
}