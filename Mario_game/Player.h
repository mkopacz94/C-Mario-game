#pragma once

#include "Rectangle.h"
#include "Brick.h"
#include "blockWithObject.h"
#include "flowerEnemy.h"

class Player : public Rectangle
{
public:

	Player(const Window &window, float pos_x, float pos_y, int width, int height, const string &picture);
	~Player();

	float move(float speedGoal, float currentSpeed, float dt);
	void update(float dt, Window &window);

	void detectEvents(SDL_Event &event);
	void checkBoundaries();
	bool isPlayerMovingRight();
	bool isPlayerMovingLeft();	
	void drawPlayer(SDL_Rect *clip);

	void newCollision(Rectangle &object);
	void brickCollision(Brick &brick);
	void blockCollision(blockWithObject &block);
	void enemyCollision(Rectangle &enemy);
	void turtleCollision(Rectangle &enemy);
	void flowerEnemyCollision(flowerEnemy &flower);
	void setSpeedFactor(float factorToSet);
	bool isJumping();
	
	void incrementCollectedCoinsCounter();
	void decrementCollectedCoinsCounter();
	int getPlayerHealth();
	void incrementHealth();
	void decrementHealth();

	void setSpartanMode();
	void deleteSpartanMode();

	bool playBrickBreak, playBlockHit, playCoinCollected;

private:

	int collisionPoints[16];

	bool contactUp, contactDown, contactX;
	bool movingRight, movingLeft, crouching;
	bool spartanMode;
	int playerHealth;
	bool player_hasWeapon, immortal, jumping;

	float speedFactor;

	int coinsCollected;
};