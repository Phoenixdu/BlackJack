#pragma once

#include "textures.h"

const enum Suit { CLUBS, HEARTS, SPADES, DIAMONDS };

class Card : public Textures
{
public:
	Card(SDL_Renderer* renderer, Suit newSuit, int newValue);
	~Card();

	int getValue();

private:
	static const int CARD_HEIGHT;
	static const int CARD_WIDTH;

	Suit suit;
	int value;
};