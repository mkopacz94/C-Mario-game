#pragma once

#include "Rectangle.h"
#include "Timer.h"

class flowerEnemy : public Rectangle
{
public:
	flowerEnemy(const Window &window, float pos_x, float pos_y, int width, int height,
				const string &picture);
	~flowerEnemy();

	void update(float dt);
	void drawFlowerEnemy();

private:
	float startPosY;
	SDL_Rect clip;

	Timer hideAndShowTimer;
};