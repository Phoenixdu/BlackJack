#pragma once

#include <vector>

#include "draw_card.h"
#include "textures.h"

using namespace std;

class Deck : public Textures
{
public:
	Deck();
	~Deck();

	Card* randomCard();
	void fillDeck(SDL_Renderer* renderer);

private:
	vector<Card*> cards;
};