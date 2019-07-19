#pragma once
#include "Rectangle.h"


class Brick : public Rectangle
{
public:
	Brick(const Window &window, float pos_x, float pos_y, int width, int height, const string &picture, 
		bool objectDdestructible, bool objectHiddenInside);
	~Brick();

	void drawBrick();
	void update(float dt);
	void bumpUpBrick();
	bool isDestructible();
	void reinitialize();

private:

	float posX, posY;
	int width, height;

	bool destructible, bumpUp;

	int currentAnimationFrame;
	SDL_Rect clip;
};