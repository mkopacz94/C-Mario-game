#pragma once

#include "Rectangle.h"

class enemyMushroom : public Rectangle
{
public:

	enemyMushroom(const Window &window, float pos_x, float pos_y, int width, int height, float horizontalStartSpeed, 
					const string &picture);
	~enemyMushroom();

	void update(float dt);
	void draw();
	void collision(Rectangle &object);
	void collisionTurtle(Rectangle &object);

	
private:

	int collisionPoints[16] = { 12, 0, 46, 0,
							8, 49, 52, 49,
							0, 10, 0, 30,
							55, 10, 55, 30 };
	bool contactUp, contactDown, contactX;
	int currentAnimationFrame;
	SDL_Rect clip;

protected:
	
};