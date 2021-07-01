#include "draw_card.h"

int cardImage(Card card)
{
	return 0;
}

Card* createCard(SDL_Renderer* renderer, Suit suit, int value)
{
	Card* nextCard = new Card(renderer, suit, value);
	return nextCard;
}

Card* cardNum(SDL_Renderer* renderer, int number)
{
	Suit suit;

	switch (number / 10)
	{
	case (0):
		suit = DIAMONDS;
		break;
	case (1):
		suit = CLUBS;
		break;
	case (2):
		suit = SPADES;
		break;
	case (3):
		suit = HEARTS;
		break;
	}

	int value = number % 10 + 1;

	Card* nextCard = new Card(renderer, suit, value);
	return nextCard;

		
}