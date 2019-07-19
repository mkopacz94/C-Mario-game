#pragma once
#include "Rectangle.h"
#include "Player.h"

class aspirine : public Rectangle
{
public:

	aspirine(const Window &window, float pos_x, float pos_y, int width, int height, const string &picture);
	~aspirine();

	void drawAspirine();
	void update(Player *player);
	void collision(Rectangle &object);
	bool isBumped();

private:

	bool collected, bumped;
	bool contactUp, contactDown, contactX;

	int collisionPoints[16] = { 7, 0, 28, 0,
							7, 35, 28, 35,
							0, 7, 0, 28,
							35, 7, 35, 28 };

	float startPosY, finalPosition;

	SDL_Rect clip;
};