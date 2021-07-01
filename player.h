#pragma once

#include <vector>

#include "textures_all.h"
#include "card.h"
#include "debug.h"


using namespace std;

class Player
{
public:
	Player();
	~Player();

	//Money
	int money = 500;
	int wager = 0;

	//adds card to the hand and draws it
	void addCard(Card* card);	
	void update();
	void draw(SDL_Renderer* renderer);

	//Set main hand's origin positions
	void setHandPos_x(int x);
	void setHandPos_y(int y);
	
	//Get the score of the player
	int getScore();
	void setScore(int newScore);
	
	void setSpawn_x(int new_x);
	void setSpawn_y(int new_y);

	bool done = false;

private:
	static const int gap;		//gap between cards

	TexturesAll cardAll;

	vector<Card*> hand;

	//Hand origin position
	int handPos_x;
	int handPos_y;

	int score;
	int spawn_x;
	int spawn_y;
};
