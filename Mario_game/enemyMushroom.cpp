#include "enemyMushroom.h"

enemyMushroom::enemyMushroom(const Window &window, float pos_x, float pos_y, int width, int height, float horizontalStartSpeed,
							const string &picture)
	: Rectangle(window, pos_x, pos_y, width, height, picture)
{
	speedX = horizontalStartSpeed;
	currentAnimationFrame = 1;
	collisionAllowed = true;
	releaseGravity = false;
	hitByShell = false;
}

enemyMushroom::~enemyMushroom()
{
}

void enemyMushroom::draw()
{
	SDL_Rect object_rectangle = { static_cast<int>(rectangle_posX), static_cast<int>(rectangle_posY), 
									rectangle_width, rectangle_height };

	if (!collisionByHead && !hitByShell)
	{
		clip.x = (rectangle_width * ((SDL_GetTicks() / 150) % 12));
		clip.y = 0;
		clip.w = 55;
		clip.h = 50;
	}
	else if(collisionByHead)
	{
		if (currentAnimationFrame == 3)
		{
			clip.x = 0;
			clip.y = 50;
			clip.w = 55;
			clip.h = 50;
		
		}
		if (currentAnimationFrame == 6)
		{
			clip.x = 0;
			clip.y = 100;
			clip.w = 55;
			clip.h = 50;

		}
		else if (currentAnimationFrame == 9)
		{
			clip.x = 0;
			clip.y = 150;
			clip.w = 55;
			clip.h = 50;
		}
		else if (currentAnimationFrame == 25)
		{
			clip.x = 55;
			clip.y = 150;
			clip.w = 55;
			clip.h = 50;

			releaseGravity = true;
		}

		currentAnimationFrame++;
	}
	else if (hitByShell)
	{
		clip.x = 55;
		clip.y = 50;
		clip.w = 55;
		clip.h = 50;
	}


	if (object_texture)
	{
		SDL_RenderCopy(new_renderer, object_texture, &clip, &object_rectangle);
	}
}

void enemyMushroom::update(float dt)
{
	//UPDATE X POSITION

	rectangle_posX = rectangle_posX + speedX * dt;

	rectangle_posY = rectangle_posY + speedY * dt;


	//UPDATE Y POSITION

	speedY += Gravity * dt;

}

void enemyMushroom::collision(Rectangle &object)
{
	if (!hitByShell && !releaseGravity)
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

void enemyMushroom::collisionTurtle(Rectangle &object)
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