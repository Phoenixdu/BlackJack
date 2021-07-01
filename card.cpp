#include "card.h"

using namespace std;

const int Card::CARD_HEIGHT = 124;
const int Card::CARD_WIDTH = 91;

Card::Card(SDL_Renderer* renderer, Suit nextSuit, int nextValue)
{
	suit = nextSuit;
	value = nextValue;

	int suitValue;

	this->setTexture(renderer, "Images/cards.png"); 

	switch (suit)
	{
	case (DIAMONDS):
		suitValue = 0;
		break;
	case (CLUBS):
		suitValue = 1;
		break;
	case (SPADES):
		suitValue = 2;
		break;
	case (HEARTS):
		suitValue = 3;
		break;
	}

	setSrc_x(CARD_WIDTH * (value - 1));
	setSrc_y(CARD_HEIGHT * suitValue);
	
	setSrc_h(CARD_HEIGHT);
	setSrc_w(CARD_WIDTH);
	
}

Card::~Card()
{
}

int Card::getValue()
{
	return value;
}