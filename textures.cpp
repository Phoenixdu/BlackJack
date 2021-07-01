#include "textures.h"
#include "debug.h"

#include <string>
#include <vector>
#include <cmath>

using namespace std;

#define PI 3.1415

const int Textures::animationSpeed = 10;		//To set later for animation

Textures::Textures()
{
}

Textures::~Textures()
{
}

//Animation goes here
void Textures::update()
{
	int distance_x = xTarget - xPos;
	int distane_y = yTarget - yPos;

	double angle = SDL_fmod(atan2(-distane_y, distance_x), PI * 2);

	if (xTarget != xPos)
	{
		int new_x = xPos + (int)(cos(angle) * animationSpeed);
		
		if (xTarget > xPos) {

			new_x = new_x > xTarget ? xTarget : new_x;
		}
		else {
			new_x = new_x < xTarget ? xTarget : new_x;
		}
		setPos_x(new_x);		
	}

	if (yTarget != xPos)
	{
		int new_y = yPos - (int)(sin(angle) * animationSpeed);
		
		if (yTarget > yPos) {

			new_y = new_y < yTarget ? yTarget : new_y;
		}
		else {
			new_y = new_y < yTarget ? yTarget : new_y;
		}
		setPos_y(new_y);
	}
} 

void Textures::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, &src_rect, &dst_rect);
}

void Textures::setTexture(SDL_Renderer* renderer, string path)
{
	//Check if texture exists
	if (!pathValid(path)) {
		string text = "Texture not found " + path + " ";
		printError(text);
		return;
	}

	SDL_Surface* surface = IMG_Load(path.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (dst_rect.w == NULL && dst_rect.h == NULL) {
		int h, w;
		SDL_QueryTexture(texture, NULL, NULL, &h, &w);

		height = h;
		width = w;

		src_rect.x = 0;
		src_rect.y = 0;

		dst_rect.x = 0;
		dst_rect.x = 0;
		
		src_rect.h = h;
		src_rect.w = w;

		dst_rect.h = h;
		dst_rect.w = w;			
	}		
}

void Textures::setSrc_x(int x)
{
	src_rect.x = x;
}

void Textures::setSrc_y(int y)
{
	src_rect.y = y;
}

void Textures::setSrc_h(int h)
{
	src_rect.h = h;
	dst_rect.h = h;
}

void Textures::setSrc_w(int w)
{
	src_rect.w = w;
	dst_rect.w = w;
}

int Textures::getHeight()
{
	return height;
}

void Textures::setHeight(int h)
{
	dst_rect.h = h;
	height = h;
}

int Textures::getWidth()
{
	return width;
}

void Textures::setWidth(int w)
{
	dst_rect.w = w;
	width = w;
}

int Textures::getPos_x()
{
	return xPos;
}

void Textures::setPos_x(int x)
{
	dst_rect.x = x;
	xPos = x;
}

int Textures::getPos_y()
{
	return yPos;
}

void Textures::setPos_y(int y)
{
	dst_rect.y = y;
	yPos = y;
}

void Textures::setTarget_x(int x)
{
	xTarget = x;
}

void Textures::setTarget_y(int y)
{
	yTarget = y;
}