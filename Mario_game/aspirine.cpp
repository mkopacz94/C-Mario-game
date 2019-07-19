#include "aspirine.h"

aspirine::aspirine(const Window &window, float pos_x, float pos_y, int width, int height, const string &picture)
	: Rectangle(window, pos_x, pos_y, width, height, picture)
{
	collected = bumped = false;

	startPosY = pos_y;
}

aspirine::~aspirine()
{

}

void aspirine::drawAspirine()
{
	SDL_Rect object_rectangle = { static_cast<int>(rectangle_posX), static_cast<int>(rectangle_posY),
										 rectangle_width, rectangle_height };

	clip.x = (rectangle_width * ((SDL_GetTicks() / 150) % 4));
	clip.y = 0;
	clip.w = 35;
	clip.h = 35;

	if (object_texture)
	{
		SDL_RenderCopy(new_renderer, object_texture, &clip, &object_rectangle);
	}
}

void aspirine::update(Player *player)
{
	if (!collected)
	{
		if (((player->getPosX() + player->getWidth()) > rectangle_posX) && (player->getPosX() < (rectangle_posX + rectangle_width))
			&& ((player->getPosY() + player->getHeight()) > rectangle_posY) && (player->getPosY() < (rectangle_posY + rectangle_height)))
		{
			collected = true;
			player->incrementHealth();
		}

		drawAspirine();

		if(!bumped) speedY = -20.0;

		if (rectangle_posY <= startPosY - 50)
		{
			bumped = true;
			speedX = 5.0;	
		}
		
		/*else
		{
			if (rectangle_posY <= finalPosition) speedY = 1;
			if (rectangle_posY >= finalPosition + 20) speedY = -1;

			rectangle_posY = rectangle_posY + speedY * 0.35;

		}*/
		if (bumped)
		{
			rectangle_posX = rectangle_posX + speedX * 0.5;

			


			//UPDATE Y POSITION

			speedY += Gravity * 0.5;

		}
		rectangle_posY = rectangle_posY + speedY * 0.5;

	}
}

void aspirine::collision(Rectangle &object)
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

bool aspirine::isBumped()
{
	return bumped;
}