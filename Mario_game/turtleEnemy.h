#pragma once

#include "Rectangle.h"
#include "Timer.h"

class turtleEnemy : public Rectangle
{
public:

	turtleEnemy(const Window &window, float pos_x, float pos_y, int width, int height, float horizontalStartSpeed,
		const string &picture);
	~turtleEnemy();

	void update(float dt);
	void draw();
	void collision(Rectangle &object);
	void collisionOtherEnemy(Rectangle &object);

private:

	int collisionPoints[16] = { 10, 0, 50, 0,
							6, 49, 58, 49,
							0, 10, 0, 40,
							55, 10, 55, 40 };
	bool contactUp, contactDown, contactX;
	int currentAnimationFrame;
	SDL_Rect clip;
	Timer timeInShell;
};