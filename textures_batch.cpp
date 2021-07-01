#include "textures_All.h"

TexturesAll::TexturesAll()
{
}

TexturesAll::~TexturesAll()
{
}

//Puts the texture to the front
void TexturesAll::addAll(Textures* object)
{
	All.push_back(object);
}

//Updates all textures
void TexturesAll::updateAll()
{
	for (Textures* t : All) {
		t->update();
	}
}

//Draws all textures
void TexturesAll::drawAll(SDL_Renderer* renderer)
{
	for (Textures* t : All) {
		t->draw(renderer);
	}
}