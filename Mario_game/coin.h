#pragma once

#include "Rectangle.h"
#include "Player.h"

class coin : public Rectangle
{
public:

	coin(const Window &window, float pos_x, float pos_y, int width, int height, const string &picture);
	~coin();

	void drawCoin();
	void updateCoin(Player *player);

private:

	float posX, posY;
	float startPosY, finalPosition;

	int width, height;
	bool bumped, collected;

	SDL_Rect clip;
};