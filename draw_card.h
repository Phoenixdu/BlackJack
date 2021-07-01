#pragma once

#include "card.h"

int cardImage(Card card);
Card* createCard(SDL_Renderer* renderer, Suit suit, int value);
Card* cardNum(SDL_Renderer* renderer, int num);

