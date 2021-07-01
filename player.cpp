#include "player.h"

const int Player::gap = 100;

Player::Player()
{
}

Player::~Player()
{
}

void Player::addCard(Card* card)
{
	cardAll.addAll(card);
	hand.push_back(card);

	int xPos = handPos_x + ((hand.size() - 1) * gap);		//For card positioning

	card->setPos_x(spawn_x);
	card->setPos_y(spawn_y);

	card->setTarget_x(xPos);		//Card move towards player or dealer
	card->setTarget_y(handPos_y);

	score += card->getValue();		//update score with card value
}

void Player::draw(SDL_Renderer* renderer)
{
	cardAll.drawAll(renderer);
}

void Player::update()
{
	cardAll.updateAll();
}


void Player::setHandPos_x(int newHand_x)
{
	handPos_x = newHand_x;
}

void Player::setHandPos_y(int newHand_y)
{
	handPos_y = newHand_y;
}

int Player::getScore()
{
	return score;
}

void Player::setScore(int newScore)
{
	score = newScore;
}

void Player::setSpawn_x(int newSpawn_x)
{
	spawn_x = newSpawn_x;
}

void Player::setSpawn_y(int newSpawn_y)
{
	spawn_x = newSpawn_y;
}
