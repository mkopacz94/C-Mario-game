#include "turtleEnemy.h"

turtleEnemy::turtleEnemy(const Window &window, float pos_x, float pos_y, int width, int height, float horizontalStartSpeed,
	const string &picture)
	: Rectangle(window, pos_x, pos_y, width, height, picture)
{
	speedX = horizontalStartSpeed;
	currentAnimationFrame = 1;
	collisionAllowed = true;
	hiddenInShell = false;
}

turtleEnemy::~turtleEnemy()
{
}

void turtleEnemy::draw()
{
	SDL_Rect object_rectangle = { static_cast<int>(rectangle_posX), static_cast<int>(rectangle_posY), 
									rectangle_width, rectangle_height };

	if (!hiddenInShell && !hitByShell)
	{
		if (speedX < 0)
		{
			clip.x = (rectangle_width * ((SDL_GetTicks() / 150) % 2));
			clip.y = 0;
			clip.w = 55;
			clip.h = 50;
		}
		else if (speedX > 0)
		{
			clip.x = 110 + (rectangle_width * ((SDL_GetTicks() / 150) % 2));
			clip.y = 0;
			clip.w = 55;
			clip.h = 50;
		}
	}
	else if (hitByShell)
	{
		clip.x = 55;
		clip.y = 51;
		clip.w = 55;
		clip.h = 50;
	}
	else
	{
		clip.x = 0;
		clip.y = 51;
		clip.w = 55;
		clip.h = 50;
	}


	if (object_texture)
	{
		SDL_RenderCopy(new_renderer, object_texture, &clip, &object_rectangle);
	}
}

void turtleEnemy::update(float dt)
{
	//UPDATE X POSITION

	rectangle_posX = rectangle_posX + speedX * dt;

	rectangle_posY = rectangle_posY + speedY * dt;


	//UPDATE Y POSITION

	speedY += Gravity * dt;

	cout << hiddenInShell << " " << timeInShell.updateTimer() << endl;
	if (hiddenInShell&&speedX==0)
	{
		if (!timeInShell.isTimerRunning())
		{
			timeInShell.resetTimer();
			timeInShell.startTimer();
		}
		if (timeInShell.isTimerRunning() && timeInShell.updateTimer() >= 3000)
		{
			hiddenInShell = false;
			speedX = 5;
			timeInShell.pauseTimer();
		}
	}
	if (timeInShell.isTimerRunning() && (speedX > 10 || speedX < -10)) timeInShell.pauseTimer();
}

void turtleEnemy::collision(Rectangle &object)
{
	if (collisionAllowed)
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

			while (((rectangle_posX + collisionPoints[4 * dir] + predictedMoveX >= object.getPosX()) && (rectangle_posX + collisionPoints[4 * dir] + predictedMoveX <= object.getPosX() + object.getWidth()))
				&& ((rectangle_posY + collisionPoints[4 * dir + 1] + predictedMoveY >= object.getPosY()) && (rectangle_posY + collisionPoints[4 * dir + 1] + predictedMoveY <= object.getPosY() + object.getHeight()))
				||
				((rectangle_posX + collisionPoints[4 * dir + 2] + predictedMoveX >= object.getPosX()) && (rectangle_posX + collisionPoints[4 * dir + 2] + predictedMoveX <= object.getPosX() + object.getWidth()))
				&& ((rectangle_posY + collisionPoints[4 * dir + 3] + predictedMoveY >= object.getPosY()) && (rectangle_posY + collisionPoints[4 * dir + 3] + predictedMoveY <= object.getPosY() + object.getHeight())))
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
			speedX = -speedX;

		}
		if (contactUp || contactDown)
		{
			rectangle_posY += (nextMoveY);
			speedY = 0;
		}
	}
}

void turtleEnemy::collisionOtherEnemy(Rectangle &object)
{
	if (collisionAllowed)
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

			while (((rectangle_posX + collisionPoints[4 * dir] + predictedMoveX >= object.getPosX()) && (rectangle_posX + collisionPoints[4 * dir] + predictedMoveX <= object.getPosX() + object.getWidth()))
				&& ((rectangle_posY + collisionPoints[4 * dir + 1] + predictedMoveY >= object.getPosY()) && (rectangle_posY + collisionPoints[4 * dir + 1] + predictedMoveY <= object.getPosY() + object.getHeight()))
				||
				((rectangle_posX + collisionPoints[4 * dir + 2] + predictedMoveX >= object.getPosX()) && (rectangle_posX + collisionPoints[4 * dir + 2] + predictedMoveX <= object.getPosX() + object.getWidth()))
				&& ((rectangle_posY + collisionPoints[4 * dir + 3] + predictedMoveY >= object.getPosY()) && (rectangle_posY + collisionPoints[4 * dir + 3] + predictedMoveY <= object.getPosY() + object.getHeight())))
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

			if (!hiddenInShell || (hiddenInShell && speedX == 0))
			{
				speedX = -speedX;
			}
			else if(hiddenInShell && speedX!=0)
			{
				object.setHitByShell(true);
				object.setCollisionAllowed(false);
				object.setSpeedY(-15);
				if (!object.enemyDestroyed)
				{
					soundPlayer->PlayChunk("enemyDestroyed.wav");
					object.enemyDestroyed = true;
				}
			}
		}
		if (contactUp || contactDown)
		{
			rectangle_posY += (nextMoveY);
			speedY = 0;
		}
	}
}