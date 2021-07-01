#pragma once

#include <vector>

#include "textures.h"

using namespace std;

class TexturesAll		//For all textures
{
public:
	TexturesAll();
	~TexturesAll();

	void addAll(Textures* object);
	void updateAll();
	void drawAll(SDL_Renderer* renderer);

private:
	vector<Textures*> All;
};
