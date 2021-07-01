#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "instance.h"

using namespace std;

enum TextureType { FROM_SURFACE, FROM_TEXT };

class Textures : public Instance
{
public:
	Textures();
	~Textures();

	virtual void update();		//Used for animation of cards

	void draw(SDL_Renderer* renderer);
	void setTexture(SDL_Renderer* renderer, string path);

	void setSrc_x(int x);
	void setSrc_y(int y);
	
	void setSrc_w(int w);
	void setSrc_h(int h);	

	int getHeight();
	void setHeight(int h);
	
	int getWidth();
	void setWidth(int w);

	int getPos_x();
	void setPos_x(int x);

	int getPos_y();
	void setPos_y(int y);

	void setTarget_x(int x);
	void setTarget_y(int y);

private:
	static const int animationSpeed;

	SDL_Texture* texture;

	SDL_Rect src_rect;
	SDL_Rect dst_rect;

	int height, width;
	int xPos, yPos;
	int xTarget, yTarget;

	bool isActive;

};
