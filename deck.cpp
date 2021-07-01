#include "deck.h"

#include <time.h>
#include <vector>

using namespace std;

Deck::Deck()
{
}

Deck::~Deck()
{
}

//For drawing a random card
Card* Deck::randomCard()
{
	srand(time(NULL));	//Get a random card from the deck
	int i = rand() % cards.size();
	Card* card = cards[i];
	cards.erase(cards.begin() + i);		//Remove the random card from the deck so that we cant draw it again
	return card;
}

void Deck::fillDeck(SDL_Renderer* renderer)
{
	for (int i = 0; i <= 39; i++)
	{
		Card* cardID = cardNum(renderer, i);
		cards.push_back(cardID);
	}
}