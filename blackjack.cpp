#include "blackjack.h"
#include "draw_card.h"
#include "debug.h"

#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>


extern ostream cerr;

using namespace std;

const int Blackjack::WINDOW_HEIGHT = 1200;
const int Blackjack::WINDOW_WIDTH = 800;

Blackjack::Blackjack()
{
}

Blackjack::~Blackjack()
{
}

bool Blackjack::graphics()
{
	//Check if SDL could initiate
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		printError("SDL could not initiate");
		return false;
	}
	printSuccess("SDL initated successfully");

	//Audio Initialization
	SDL_Init(SDL_INIT_EVERYTHING);


	//Create a window
	window = SDL_CreateWindow("Farid Badran's Blackjack", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_HEIGHT, WINDOW_WIDTH, NULL);

	if (window == NULL)
	{
		printError("Window could not be created");
		return false;
	}
	printSuccess("Window was created successfully. Also money is included but i could not figure out how to print a text");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//Sound Effects
	chipsAudio.load("Audio/chips.wav");
	clickAudio.load("Audio/click.wav");
	loseAudio.load("Audio/lose.wav");
	winAudio.load("Audio/win.wav");

	if (renderer == NULL)
	{
		printError("Could not render");
		return false;
	}
	printSuccess("Rendered successfully");

	deck.fillDeck(renderer);	//Add cards to the deck

	//Render the background
	background.setTexture(renderer, "Images/background.jpg");

	//Render the deck
	deckImage.setTexture(renderer, "Images/deck.png");		
	deckImage.setPos_x(-150);
	deckImage.setPos_y(10);


	//Render chip1
	chip1.setTexture(renderer, "Images/chip1.png");
	chip1.setPos_x(10);
	chip1.setPos_y(700);
	
	//Render chip5
	chip5.setTexture(renderer, "Images/chip5.png");
	chip5.setPos_x(100);
	chip5.setPos_y(700);

	//Render chip25
	chip25.setTexture(renderer, "Images/chip25.png");
	chip25.setPos_x(10);
	chip25.setPos_y(630);
	
	//Render chip50
	chip50.setTexture(renderer, "Images/chip50.png");
	chip50.setPos_x(100);
	chip50.setPos_y(630);

	//Render player avatar
	playerAvatar.setTexture(renderer, "Images/player_avatar.png");
	playerAvatar.setPos_x(50);
	playerAvatar.setPos_y(500);

	//Render dealer avatar
	dealerAvatar.setTexture(renderer, "Images/dealer_avatar.jpg");
	dealerAvatar.setPos_x(50);
	dealerAvatar.setPos_y(50);
	

	//Render winning  screen
	win.setTexture(renderer, "Images/win.png");
	win.setPos_x(300);
	win.setPos_y(50);

	//Render losing screen
	lose.setTexture(renderer, "Images/lose.png");
	lose.setPos_x(0);
	lose.setPos_y(-350);

	//Set position of all cards dealt
	player.setHandPos_x(200);
	player.setHandPos_y(500);

	player.setSpawn_x(500);
	player.setSpawn_y(194);

	dealer.setHandPos_x(200);
	dealer.setHandPos_y(20);

	dealer.setSpawn_x(20);
	dealer.setSpawn_y(194);

	//Render HIT button
	hit.setTexture(renderer, "Images/hit.png");
	hit.setPos_x(250);
	hit.setPos_y(700);

	//Render STAND button
	stand.setTexture(renderer, "Images/stand.png");
	stand.setPos_x(400);
	stand.setPos_y(700);

	//Render DOUBLE DOWN button
	doubleDown.setTexture(renderer, "Images/double_down.png");
	doubleDown.setPos_x(550);
	doubleDown.setPos_y(700);

	//Render SPLIT button
	split.setTexture(renderer, "Images/split.png");
	split.setPos_x(700);
	split.setPos_y(700);

	//Render SURRENDER button
	surrender.setTexture(renderer, "Images/surrender.png");
	surrender.setPos_x(850);
	surrender.setPos_y(700);

	//Render menu
	menu.setTexture(renderer, "Images/menu.png");

	state = TAKING_TURNS;

	thread = new std::thread(&Blackjack::takingTurns, this);

	gameRunning = true;
	return true;
}

//Game loop
void Blackjack::execute()
{
	while (gameRunning) {
		update();
		input();
		draw();
	}
}

void Blackjack::update()
{
	player.update();
	dealer.update();
	hit.update();
	stand.update();
	doubleDown.update();
	split.update();
	surrender.update();

	//chips
	chip1.update();
	chip5.update();
	chip25.update();
	chip50.update();

	//Menu
	play.update();
	rules.update();

}

void Blackjack::input()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			gameRunning = false;
		}
	}
}

void Blackjack::draw()
{
	SDL_RenderClear(renderer);
	
	//Draw background
	background.draw(renderer);		
	
	//Draw buttons, cards, deck and avatar
	if (!player.done && gameHolding) {
		hit.draw(renderer);
		stand.draw(renderer);
		doubleDown.draw(renderer);
		split.draw(renderer);
		surrender.draw(renderer);
	}
	deckImage.draw(renderer);
	chip1.draw(renderer);
	chip5.draw(renderer);
	chip25.draw(renderer);
	chip50.draw(renderer);
	playerAvatar.draw(renderer);
	dealerAvatar.draw(renderer);
	player.draw(renderer);
	dealer.draw(renderer);

	if (state == WIN) {
		win.draw(renderer);
		winAudio.play();
	}
	if (state == LOSE) {
		lose.draw(renderer);
		loseAudio.play();
	}

	SDL_RenderPresent(renderer);
		
}

void Blackjack::takingTurns()
{
	for (int i = 0; i < 10; i++)
	{
		if (player.getScore() > dealer.getScore() && dealer.done) {
			player.done = true;
			state = WIN;
		}

		if (!player.done)
		{
			gameHolding = true;		//Player hasnt pressed anything
			while (true)
			{
				SDL_Delay(30);
				
				if (hit.isPressed()) {
					SDL_Delay(150);
					gameHolding = false;
					clickAudio.play();
					money = money + wager;					
					break;
				}
				else if (stand.isPressed()) {
					SDL_Delay(150);
					gameHolding = false;
					clickAudio.play();
					player.done = true;
					break;
				}
				else if (doubleDown.isPressed()) {
					SDL_Delay(150);
					gameHolding = false;
					clickAudio.play();
					player.done = false;
					money = wager * 2;
					break;
				}
				else if (surrender.isPressed()) {
					SDL_Delay(150);
					gameHolding = false;
					clickAudio.play();
					player.done = true;
					state = LOSE;
					money = wager / 2;
					break;
				}
				else if (chip1.isPressed()) {
					SDL_Delay(150);
					gameHolding = true;
					chipsAudio.play();
					player.done = false;
					money = money + 1;
				}
				else if (chip5.isPressed()) {
					SDL_Delay(150);
					gameHolding = true;
					chipsAudio.play();
					player.done = false;
					money = money + 5;
				}
				else if (chip25.isPressed()) {
					SDL_Delay(150);
					gameHolding = true;
					chipsAudio.play();
					player.done = false;
					money = money + 25;
				}
				else if (chip50.isPressed()) {
					SDL_Delay(150);
					gameHolding = true;
					chipsAudio.play();
					player.done = false;
					money = money + 50;
				}
			}
		}

		if (!player.done)
		{
			Card* nextPlayerCard = deck.randomCard(); //Draws random card when player isnt done
			SDL_Delay(20);
			player.addCard(nextPlayerCard);
			SDL_Delay(20);

			string playerText = ("Player score is: " + to_string(player.getScore()));
			printWarning(playerText);

			SDL_Delay(500);
		}

		//Player score
		if (player.getScore() == 21) {
			state = WIN; //Later to be made blackjack (money change)
		}
		if (player.getScore() > 21) {
			state = LOSE;
		}
		if (state != TAKING_TURNS) {
			SDL_Delay(5000);
			gameRunning = false;
		}

		SDL_Delay(500);
		
		//Draw next dealer card
		if (!dealer.done) {
			Card* nextDealerCard = deck.randomCard();
			SDL_Delay(20);
			dealer.addCard(nextDealerCard);
			SDL_Delay(20);

			string dealerText = ("Dealer's score is: " + to_string(dealer.getScore()));
			printWarning(dealerText);

			SDL_Delay(500);
		}

		//Dealer score
		if (dealer.getScore() >= 17) {
			dealer.done = true;
		}
		if (dealer.getScore() > player.getScore() && player.done) {
			dealer.done = true;
			state = LOSE;
		}
		if (dealer.getScore() == 21) {
			state = LOSE;
		}
		if (dealer.getScore() > 21) {
			state = WIN;
		}
		if (dealer.done && player.done && player.getScore() == dealer.getScore()) {
			state = WIN;
		}

		if (state != TAKING_TURNS) {
			SDL_Delay(5000);
			gameRunning = false;
		}
	}
}