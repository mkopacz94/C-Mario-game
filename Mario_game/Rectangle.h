#pragma once
#include "Window.h"
#include <vector>

extern const float Gravity;

class Rectangle :public Window
{
public:
	Rectangle(const Window &window, float pos_x, float pos_y, int width, int height, const string &picture);
	Rectangle(float pos_x, float pos_y, int width, int height, const string &picture);
	~Rectangle();
	
	void draw();

	void changeRectanglePosition(int pos_x, int pos_y);

	vector<int> getPositionxy();
	vector<int> getWidthHeight();
	
	float getSpeedX();
	float getSpeedY();
	void setSpeedX(float speed);
	void setSpeedY(float speed);

	float getPosX();
	float getPosY();
	int getWidth();
	int getHeight();

	bool isHiddenInShell();
	void setHiddenInShell(bool state);

	void setHitByShell(bool state);

	void setHeadCollision(bool state);

	void setCollisionAllowed(bool state);
	bool isCollisionAllowed();
	bool enemyDestroyed;
private:

	string rectangle_picture;
	
protected:

	SDL_Texture *object_texture = nullptr;
	int speedGoal;
	float speedX, speedY;

	float rectangle_posX, rectangle_posY;
	int rectangle_width, rectangle_height;

	bool hitByShell, hiddenInShell;
	bool collisionByHead, collisionAllowed;
	bool releaseGravity;
};