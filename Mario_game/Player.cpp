#include "Player.h"
#include "Brick.h"
#include "AudioManager.h"
Player::Player(const Window &window, float pos_x, float pos_y, int width, int height, const string &picture) 
	: Rectangle(window, pos_x, pos_y, width, height, picture)
{

	soundPlayer ->PlayMusic("theme.wav");
	
	playerHealth = 1;
	speedFactor = 1;
	player_hasWeapon = false;
	immortal = false;
	playBrickBreak= false, playBlockHit = false;

	coinsCollected = 0;

	collisionPoints[0] = 8;
	collisionPoints[1] = 0;
	collisionPoints[2] = 40;
	collisionPoints[3] = 0;
	collisionPoints[4] = 8;
	collisionPoints[5] = 89;
	collisionPoints[6] = 44;
	collisionPoints[7] = 89;
	collisionPoints[8] = 0;
	collisionPoints[9] = 25;
	collisionPoints[10] = 0;
	collisionPoints[11] = 82;
	collisionPoints[12] = 48;
	collisionPoints[13] = 25;
	collisionPoints[14] = 48;
	collisionPoints[15] = 82;

	spartanMode = false;
}

Player::~Player()
{
}

void Player::checkBoundaries()
{
	if (rectangle_posX <= 0) rectangle_posX = 0;
	if (rectangle_posX >= 400 - rectangle_width) rectangle_posX = static_cast<float>(399 - rectangle_width);
}

bool Player::isPlayerMovingRight()
{
	return movingRight;
}

bool Player::isPlayerMovingLeft()
{
	return movingLeft;
}

void Player::drawPlayer(SDL_Rect *clip)
{
	SDL_Rect object_rectangle = { static_cast<int>(rectangle_posX), static_cast<int>(rectangle_posY), 
								rectangle_width, rectangle_height };

	if (jumping)
	{
		if (isPlayerMovingLeft())
		{
			clip->x = 48;
			clip->y = 180 + 4*90*spartanMode;
		}
		else
		{
			clip->x = 96;
			clip->y = 180 + 4 * 90 *spartanMode;
		}

	}
	else
	{
		if (movingLeft)
		{
			clip->x = (rectangle_width * ((SDL_GetTicks() / 120) % 2));
			clip->y = 0 + 4 * 90 * spartanMode;
		}
		else if (movingRight)
		{
			clip->x = 96 + (rectangle_width * ((SDL_GetTicks() / 120) % 2));
			//clip->x = 48;
			clip->y = 0 + 4 * 90 * spartanMode;
		}
		else if (crouching)
		{
			clip->x = 96;
			clip->y = 270 + 4 * 90 * spartanMode;
		}
		else
		{
			//clip->x = rectangle_width * ((SDL_GetTicks() / 100) % 2);
			clip->x = 96;
			clip->y = 90 + 4 * 90 * spartanMode;
		}
	}

	object_rectangle.w = clip->w;

	if (object_texture)
	{
		SDL_RenderCopy(new_renderer, object_texture, clip, &object_rectangle);
	}
}

void Player::detectEvents(SDL_Event &event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:

			movingRight = true;
			break;

		case SDLK_LEFT:

			movingLeft = true;
			break;

		case SDLK_UP:

			if (!jumping && !(speedY > 0))
			{
				jumping = true;

				soundPlayer->PlayChunk("jump.wav");

				if(!spartanMode) speedY = -33.0;
				else speedY = -40.0;
			}
			break;

		case SDLK_DOWN:

			crouching = true;
			break;

		case SDLK_h:
			spartanMode = true;
			break;

		case SDLK_b:
			spartanMode = false;
			break;

		default:
			break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:

			movingRight = false;
			break;

		case SDLK_LEFT:

			movingLeft = false;
			break;

		case SDLK_DOWN:

			crouching = false;
			break;

		case SDLK_i:
			playerHealth++;
			break;
		default:
			break;
		}
	}
}

float Player::move(float speedGoal, float currentSpeed, float dt)
{
	float difference = speedGoal - currentSpeed;

	if (difference > dt) return (currentSpeed + dt);
	if (difference < -dt) return (currentSpeed - dt);

	return speedGoal;
}

void Player::update(float dt, Window &main_window)
{
	if (spartanMode && !crouching)
	{
		collisionPoints[1] = 0;
		collisionPoints[3] = 0;
	}
	else if(!spartanMode && !crouching)
	{
		collisionPoints[1] = 14;
		collisionPoints[3] = 14;
	}
	else if (crouching)
	{
		collisionPoints[1] = 38;
		collisionPoints[3] = 38;

		collisionPoints[9] = 40;
		collisionPoints[13] = 40;
	}
	//UPDATE X POSITION

	speedX = move(speedGoal*speedFactor, speedX, dt);
	rectangle_posX = rectangle_posX + speedX * dt;

	rectangle_posY = rectangle_posY + speedY * dt;

	if (rectangle_posY >= 600 - rectangle_height) decrementHealth();

	SDL_Event event_occured;

	if (SDL_PollEvent(&event_occured))
	{
		main_window.detectEvents(event_occured);
		detectEvents(event_occured);
	}

	if (movingRight) speedGoal = 10;
	else if (movingLeft) speedGoal = -10;
	else speedGoal = 0;

	//UPDATE Y POSITION

	speedY += Gravity * dt;

	//FREEFALL MAXIMUM SPEED LIMIT

	if (speedY > 40.0) speedY = 40.0;

	//END OF FREEFALL MAXIMUM SPEED LIMIT

	if (!(SDL_GetTicks() % 200)) immortal = false;

}

void Player::newCollision(Rectangle &object)
{
	float nextMoveX = speedX;
	float nextMoveY = speedY;

	contactUp = contactDown = contactX = false;

	float originalMoveX, originalMoveY, predictedMoveX, predictedMoveY;

	originalMoveX = nextMoveX;
	originalMoveY = nextMoveY;

	checkBoundaries();

	for (int dir = 0; dir < 4; dir++) // 0 - w górê, 1 - w dó³, 2 - w lewo, 3 - w prawo
	{		
		if (dir == 0 && nextMoveY > 0) continue;
		if (dir == 1 && nextMoveY < 0) continue;
		if (dir == 2 && nextMoveX > 0) continue;
		if (dir == 3 && nextMoveX < 0) continue;

		predictedMoveX = (dir >= 2 ? nextMoveX : 0);
		predictedMoveY = (dir < 2 ? nextMoveY : 0);

		while (((rectangle_posX + collisionPoints[4 * dir]+predictedMoveX >= object.getPosX()) && (rectangle_posX + collisionPoints[4 * dir] + predictedMoveX <= object.getPosX() + object.getWidth()))
			&& ((rectangle_posY + collisionPoints[4 * dir + 1] + predictedMoveY >= object.getPosY()) && (rectangle_posY + collisionPoints[4 * dir + 1] + predictedMoveY <= object.getPosY() + object.getHeight()))
			||
			((rectangle_posX + collisionPoints[4 * dir + 2]+predictedMoveX >= object.getPosX()) && (rectangle_posX + collisionPoints[4 * dir + 2] +predictedMoveX <= object.getPosX() + object.getWidth()))
			&& ((rectangle_posY + collisionPoints[4 * dir + 3]+predictedMoveY >= object.getPosY()) && (rectangle_posY + collisionPoints[4 * dir + 3] + predictedMoveY <= object.getPosY() + object.getHeight()))
			)
		{
			if (dir == 0) predictedMoveY++;
			if (dir == 1) predictedMoveY--;
			if (dir == 2) predictedMoveX++;
			if (dir == 3) predictedMoveX--;	

		}

		if (dir >= 2) nextMoveX = predictedMoveX;
		if (dir < 2) nextMoveY = predictedMoveY;

	}

	if (nextMoveY > originalMoveY && originalMoveY < 0) contactUp = true;
	if (nextMoveY < originalMoveY && originalMoveY > 0) contactDown = true;		
	if (abs(originalMoveX - nextMoveX) > 0) contactX = true;

	if (contactX)
	{
		rectangle_posX += nextMoveX;
		speedX = 0;
	}
	if (contactUp || contactDown)
	{
		rectangle_posY += (nextMoveY);
		speedY = 0;

		if(contactDown) jumping = false;
	}

}

void Player::brickCollision(Brick &brick)
{
	if (brick.isCollisionAllowed())
	{
		float nextMoveX = speedX;
		float nextMoveY = speedY;

		contactUp = contactDown = contactX = false;

		float originalMoveX, originalMoveY, predictedMoveX, predictedMoveY;

		originalMoveX = nextMoveX;
		originalMoveY = nextMoveY;


		for (int dir = 0; dir < 4; dir++) // 0 - w górê, 1 - w dó³, 2 - w lewo, 3 - w prawo
		{
			if (dir == 0 && nextMoveY > 0) continue;
			if (dir == 1 && nextMoveY < 0) continue;
			if (dir == 2 && nextMoveX > 0) continue;
			if (dir == 3 && nextMoveX < 0) continue;

			predictedMoveX = (dir >= 2 ? nextMoveX : 0);
			predictedMoveY = (dir < 2 ? nextMoveY : 0);

			while (((rectangle_posX + collisionPoints[4 * dir] + predictedMoveX >= brick.getPosX()) && (rectangle_posX + collisionPoints[4 * dir] + predictedMoveX <= brick.getPosX() + brick.getWidth()))
				&& ((rectangle_posY + collisionPoints[4 * dir + 1] + predictedMoveY >= brick.getPosY()) && (rectangle_posY + collisionPoints[4 * dir + 1] + predictedMoveY <= brick.getPosY() + brick.getHeight()))
				||
				((rectangle_posX + collisionPoints[4 * dir + 2] + predictedMoveX >= brick.getPosX()) && (rectangle_posX + collisionPoints[4 * dir + 2] + predictedMoveX <= brick.getPosX() + brick.getWidth()))
				&& ((rectangle_posY + collisionPoints[4 * dir + 3] + predictedMoveY >= brick.getPosY()) && (rectangle_posY + collisionPoints[4 * dir + 3] + predictedMoveY <= brick.getPosY() + brick.getHeight())))
			{

				if (dir == 0) predictedMoveY++;
				if (dir == 1) predictedMoveY--;
				if (dir == 2) predictedMoveX++;
				if (dir == 3) predictedMoveX--;

			}

			if (dir >= 2) nextMoveX = predictedMoveX;
			if (dir < 2) nextMoveY = predictedMoveY;

		}

		if (nextMoveY > originalMoveY && originalMoveY < 0) contactUp = true;
		if (nextMoveY < originalMoveY && originalMoveY > 0) contactDown = true;
		if (abs(originalMoveX - nextMoveX) > 0) contactX = true;

		if (contactX)
		{
			rectangle_posX += nextMoveX;
			speedX = 0;
		}
		if (contactUp || contactDown)
		{
			rectangle_posY += (nextMoveY);
			speedY = 0;

			if (contactDown) jumping = false;
			if (contactUp)
			{
				if(brick.isDestructible()) brick.setCollisionAllowed(false);
				brick.setHeadCollision(true);
				
				if(brick.isDestructible()) soundPlayer->PlayChunk("brick_break.wav");
				else soundPlayer->PlayChunk("blockHit.wav");

				if (!brick.isDestructible()) brick.bumpUpBrick();
			}
		}
	}

}

void Player::blockCollision(blockWithObject &block)
{

		float nextMoveX = speedX;
		float nextMoveY = speedY;

		contactUp = contactDown = contactX = false;

		float originalMoveX, originalMoveY, predictedMoveX, predictedMoveY;

		originalMoveX = nextMoveX;
		originalMoveY = nextMoveY;


		for (int dir = 0; dir < 4; dir++) // 0 - w górê, 1 - w dó³, 2 - w lewo, 3 - w prawo
		{
			if (dir == 0 && nextMoveY > 0) continue;
			if (dir == 1 && nextMoveY < 0) continue;
			if (dir == 2 && nextMoveX > 0) continue;
			if (dir == 3 && nextMoveX < 0) continue;
			if (dir == 1 && !block.isBlockVisible()) continue;
			if (dir == 2 && !block.isBlockVisible()) continue;
			if (dir == 3 && !block.isBlockVisible()) continue;

			predictedMoveX = (dir >= 2 ? nextMoveX : 0);
			predictedMoveY = (dir < 2 ? nextMoveY : 0);

			while (((rectangle_posX + collisionPoints[4 * dir] + predictedMoveX >= block.getPosX()) && (rectangle_posX + collisionPoints[4 * dir] + predictedMoveX <= block.getPosX() + block.getWidth()))
				&& ((rectangle_posY + collisionPoints[4 * dir + 1] + predictedMoveY >= block.getPosY()) && (rectangle_posY + collisionPoints[4 * dir + 1] + predictedMoveY <= block.getPosY() + block.getHeight()))
				||
				((rectangle_posX + collisionPoints[4 * dir + 2] + predictedMoveX >= block.getPosX()) && (rectangle_posX + collisionPoints[4 * dir + 2] + predictedMoveX <= block.getPosX() + block.getWidth()))
				&& ((rectangle_posY + collisionPoints[4 * dir + 3] + predictedMoveY >= block.getPosY()) && (rectangle_posY + collisionPoints[4 * dir + 3] + predictedMoveY <= block.getPosY() + block.getHeight())))
			{

				if (dir == 0) predictedMoveY++;
				if (dir == 1) predictedMoveY--;
				if (dir == 2) predictedMoveX++;
				if (dir == 3) predictedMoveX--;

			}

			if (dir >= 2) nextMoveX = predictedMoveX;
			if (dir < 2) nextMoveY = predictedMoveY;

		}

		if (nextMoveY > originalMoveY && originalMoveY < 0) contactUp = true;
		if (nextMoveY < originalMoveY && originalMoveY > 0) contactDown = true;
		if (abs(originalMoveX - nextMoveX) > 0) contactX = true;

		if (contactX)
		{
			rectangle_posX += nextMoveX;
			speedX = 0;
		}
		if (contactUp || contactDown)
		{
			rectangle_posY += (nextMoveY);
			speedY = 0;

			if (contactDown) jumping = false;
			if (contactUp)
			{
				block.bumpUpBlock();
				soundPlayer->PlayChunk("blockHit.wav");

			}
		}
	

}

void Player::enemyCollision(Rectangle &enemy)
{
	if (enemy.isCollisionAllowed())
	{
		float nextMoveX = speedX;
		float nextMoveY = speedY;

		contactUp = contactDown = contactX = false;

		float originalMoveX, originalMoveY, predictedMoveX, predictedMoveY;

		originalMoveX = nextMoveX;
		originalMoveY = nextMoveY;


		for (int dir = 0; dir < 4; dir++) // 0 - w górê, 1 - w dó³, 2 - w lewo, 3 - w prawo
		{
			if (dir == 0 && nextMoveY > 0) continue;
			if (dir == 1 && nextMoveY < 0) continue;
			if (dir == 2 && nextMoveX > 0) continue;
			if (dir == 3 && nextMoveX < 0) continue;

			predictedMoveX = (dir >= 2 ? nextMoveX : 0);
			predictedMoveY = (dir < 2 ? nextMoveY : 0);

			while (((rectangle_posX + collisionPoints[4 * dir] + predictedMoveX >= enemy.getPosX()) && (rectangle_posX + collisionPoints[4 * dir] + predictedMoveX <= enemy.getPosX() + enemy.getWidth()))
				&& ((rectangle_posY + collisionPoints[4 * dir + 1] + predictedMoveY >= enemy.getPosY()) && (rectangle_posY + collisionPoints[4 * dir + 1] + predictedMoveY <= enemy.getPosY() + enemy.getHeight()))
				||
				((rectangle_posX + collisionPoints[4 * dir + 2] + predictedMoveX >= enemy.getPosX()) && (rectangle_posX + collisionPoints[4 * dir + 2] + predictedMoveX <= enemy.getPosX() + enemy.getWidth()))
				&& ((rectangle_posY + collisionPoints[4 * dir + 3] + predictedMoveY >= enemy.getPosY()) && (rectangle_posY + collisionPoints[4 * dir + 3] + predictedMoveY <= enemy.getPosY() + enemy.getHeight())))
			{

				if (dir == 0) predictedMoveY++;
				if (dir == 1) predictedMoveY--;
				if (dir == 2) predictedMoveX++;
				if (dir == 3) predictedMoveX--;

			}

			if (dir >= 2) nextMoveX = predictedMoveX;
			if (dir < 2) nextMoveY = predictedMoveY;

		}

		if (nextMoveY > originalMoveY && originalMoveY < 0) contactUp = true;
		if (nextMoveY < originalMoveY && originalMoveY > 0) contactDown = true;
		if (abs(originalMoveX - nextMoveX) > 0) contactX = true;

		if (contactX)
		{
			rectangle_posX += nextMoveX;
			speedX = 0;
			speedY = -20;
			soundPlayer->PlayChunk("enemyCollision.wav");

			if (!immortal)
			{
				playerHealth--;
				immortal = true;
			}

		}
		if (contactUp || (contactDown))
		{
			rectangle_posY += (nextMoveY);

			if(contactUp) speedY = 0;
			else if (contactDown)
			{
				enemy.setSpeedX(0);
				enemy.setHeadCollision(true);
				enemy.setCollisionAllowed(false);
				soundPlayer->PlayChunk("enemyTrodden.wav");
				speedY = -15;
				jumping = true;
			}
		}
	}
}

void Player::turtleCollision(Rectangle &enemy)
{
	if (enemy.isCollisionAllowed())
	{
		float nextMoveX = speedX;
		float nextMoveY = speedY;


		contactUp = contactDown = contactX = false;

		float originalMoveX, originalMoveY, predictedMoveX, predictedMoveY;

		originalMoveX = nextMoveX;
		originalMoveY = nextMoveY;


		for (int dir = 0; dir < 4; dir++) // 0 - w górê, 1 - w dó³, 2 - w lewo, 3 - w prawo
		{
			if (dir == 0 && nextMoveY > 0) continue;
			if (dir == 1 && nextMoveY < 0) continue;
			if (dir == 2 && nextMoveX > 0) continue;
			if (dir == 3 && nextMoveX < 0) continue;

			predictedMoveX = (dir >= 2 ? nextMoveX : 0);
			predictedMoveY = (dir < 2 ? nextMoveY : 0);

			while (((rectangle_posX + collisionPoints[4 * dir] + predictedMoveX >= enemy.getPosX()) && (rectangle_posX + collisionPoints[4 * dir] + predictedMoveX <= enemy.getPosX() + enemy.getWidth()))
				&& ((rectangle_posY + collisionPoints[4 * dir + 1] + predictedMoveY >= enemy.getPosY()) && (rectangle_posY + collisionPoints[4 * dir + 1] + predictedMoveY <= enemy.getPosY() + enemy.getHeight()))
				||
				((rectangle_posX + collisionPoints[4 * dir + 2] + predictedMoveX >= enemy.getPosX()) && (rectangle_posX + collisionPoints[4 * dir + 2] + predictedMoveX <= enemy.getPosX() + enemy.getWidth()))
				&& ((rectangle_posY + collisionPoints[4 * dir + 3] + predictedMoveY >= enemy.getPosY()) && (rectangle_posY + collisionPoints[4 * dir + 3] + predictedMoveY <= enemy.getPosY() + enemy.getHeight())))
			{

				if (dir == 0) predictedMoveY++;
				if (dir == 1) predictedMoveY--;
				if (dir == 2) predictedMoveX++;
				if (dir == 3) predictedMoveX--;

			}

			if (dir >= 2) nextMoveX = predictedMoveX;
			if (dir < 2) nextMoveY = predictedMoveY;

		}

		if (nextMoveY > originalMoveY && originalMoveY < 0) contactUp = true;
		if (nextMoveY < originalMoveY && originalMoveY > 0) contactDown = true;
		if (abs(originalMoveX - nextMoveX) > 0) contactX = true;

		if (contactX)
		{
			if (enemy.isHiddenInShell() && enemy.getSpeedX()==0)
			{
				if(originalMoveX > 0) enemy.setSpeedX(15);
				else enemy.setSpeedX(-15);

				soundPlayer->PlayChunk("enemyDestroyed.wav");
				
			}
			else if(!enemy.isHiddenInShell() || (enemy.isHiddenInShell() && ((originalMoveX==0 && enemy.getSpeedX() !=0)
					|| (originalMoveX > 0 && enemy.getSpeedX() <0) || originalMoveX < 0 && enemy.getSpeedX()>0)) )
			{
				speedX = 0;
				speedY = -25;

				soundPlayer->PlayChunk("enemyCollision.wav");

				if (!immortal)
				{
					playerHealth--;
					immortal = true;
				}
			}

		}
		if (contactUp || (contactDown))
		{
			rectangle_posY += nextMoveY;

			if (contactUp) speedY = 0;
			else if (contactDown && !enemy.isHiddenInShell())
			{
				enemy.setHiddenInShell(true);
				enemy.setSpeedX(0);

				speedY = -25;
				jumping = true;

				soundPlayer->PlayChunk("enemyTrodden.wav");
			}
			else if (contactDown && enemy.isHiddenInShell() && enemy.getSpeedX() == 0)
			{
				if(rectangle_posX + 0.5*rectangle_width >= enemy.getPosX() + 0.5*enemy.getWidth()) enemy.setSpeedX(-15);
				else enemy.setSpeedX(15);
				
				soundPlayer->PlayChunk("enemyDestroyed.wav");

				speedY = -25;
				jumping = true;
			}
			else if (contactDown && enemy.isHiddenInShell() && enemy.getSpeedX() != 0)
			{
				enemy.setSpeedX(0);
				soundPlayer->PlayChunk("enemyDestroyed.wav");
				speedY = -25;
				jumping = true;
			}
		}
	}
}

void Player::setSpeedFactor(float factorToSet)
{
	speedFactor = factorToSet;
}

bool Player::isJumping()
{
	return jumping;
}

void Player::flowerEnemyCollision(flowerEnemy &flower)
{
	if (((rectangle_posX + rectangle_width) > flower.getPosX()) && (rectangle_posX < (flower.getPosX() + flower.getWidth()))
		&& ((rectangle_posY + rectangle_height) > flower.getPosY()) && (rectangle_posY < (flower.getPosY() + flower.getHeight())))
	{

		soundPlayer->PlayChunk("enemyCollision.wav");

		if (!immortal)
		{
			playerHealth--;
			immortal = true;
		}

		if (speedX >= 0)
		{
			speedX = -15;
			speedY = -20;
		}
		else
		{
			speedX = 15;
			speedY = -20;
		}
	}
}

void Player::incrementCollectedCoinsCounter()
{
	coinsCollected++;
	soundPlayer->PlayChunk("coinCollected.wav");
}

void Player::decrementCollectedCoinsCounter()
{
	coinsCollected--;
}

void Player::setSpartanMode()
{
	spartanMode = true;
	soundPlayer->PlayChunk("itemCollected.wav");
}

void Player::deleteSpartanMode()
{
	spartanMode = false;
}

void Player::incrementHealth()
{
	playerHealth++;
	soundPlayer->PlayChunk("aspirineCollected.wav");
}

void Player::decrementHealth()
{
	playerHealth--;
}

int Player::getPlayerHealth()
{
	return playerHealth;
}