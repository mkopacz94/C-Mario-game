#include "flowerEnemy.h"

flowerEnemy::flowerEnemy(const Window &window, float pos_x, float pos_y, int width, int height,
	const string &picture)
	: Rectangle(window, pos_x, pos_y, width, height, picture)
{
	speedY = -3;
	startPosY = rectangle_posY;
}

flowerEnemy::~flowerEnemy()
{

}

void flowerEnemy::drawFlowerEnemy()
{
	SDL_Rect object_rectangle = { static_cast<int>(rectangle_posX), static_cast<int>(rectangle_posY),
									rectangle_width, rectangle_height };


	clip.x = (rectangle_width * ((SDL_GetTicks() / 120) % 6));
	clip.y = 0;
	clip.w = 85;
	clip.h = 90;

	if (object_texture)
	{
		SDL_RenderCopy(new_renderer, object_texture, &clip, &object_rectangle);
	}
}

void flowerEnemy::update(float dt)
{
	if (rectangle_posY <= startPosY - rectangle_height+1)
	{
		if (!hideAndShowTimer.isTimerRunning())
		{
			speedY = 0;
			hideAndShowTimer.resetTimer();
			hideAndShowTimer.startTimer();
		}

		if (hideAndShowTimer.updateTimer() >= 3000)
		{
			speedY = 3;
			hideAndShowTimer.pauseTimer();

		}
	}
	else if (rectangle_posY >= startPosY+1)
	{
		if (!hideAndShowTimer.isTimerRunning())
		{
			speedY = 0;
			hideAndShowTimer.resetTimer();
			hideAndShowTimer.startTimer();
		}

		if (hideAndShowTimer.updateTimer() >= 3000)
		{
			speedY = -3;
			hideAndShowTimer.pauseTimer();

		}
	}

	rectangle_posY = rectangle_posY + speedY * dt;
}