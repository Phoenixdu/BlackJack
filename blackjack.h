#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <thread>

#include "player.h"
#include "textures.h"
#include "deck.h"
#include "buttons.h"
#include "audio.h"


using namespace std;

const enum GameState { TAKING_TURNS, WIN, LOSE, BLACKJACK, PAYOUT };

class Blackjack
{
public:
	Blackjack();
	~Blackjack();

	bool graphics();
	void execute();
	void draw();
	void update();
	void input();

	//Money
	int money = 500;
	int wager = 0;
	
	void takingTurns();

	bool hasBlackjack();
	bool canDouble = true;

	
private:
	
	static const int WINDOW_HEIGHT;
	static const int WINDOW_WIDTH;

	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font *font;
	
	bool gameRunning;
	bool gameHolding;

	Deck deck;

	//Audio
	Audio chipsAudio;
	Audio clickAudio;
	Audio winAudio;
	Audio loseAudio;

	Textures menu;
	Textures background;
	Textures deckImage;
	Textures win;
	Textures lose;
	Textures playerAvatar;
	Textures dealerAvatar;
	
	Buttons chip1;
	Buttons chip5;
	Buttons chip25;
	Buttons chip50;

	Textures moneyText;
	Textures wagerText;

	Player player;
	Player dealer;

	//Game
	Buttons hit;
	Buttons stand;
	Buttons doubleDown;
	Buttons surrender;
	Buttons split;
	
	//On menu
	Buttons play;
	Buttons rules;

	GameState state;

	thread* thread;

};