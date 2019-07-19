#pragma once
#include "Player.h"
#include "Rectangle.h"

class spartanHelmet : public Rectangle
{

public:

	spartanHelmet(const Window &window, float pos_x, float pos_y, int width, int height, const string &picture);
	~spartanHelmet();

	void update(float dt);
	void drawHelmet();
	void collisionWithPlayer(Player *player);
	float getStartPosX();
	void changeStartPosX(float updatedStartPosX);
private:

	bool helmetCollected, bumped;
	float startPosX, startPosY;

	void boundaries();

	SDL_Rect clip;
};