#include "coin.h"

coin::coin(const Window &window, float pos_x, float pos_y, int width, int height, const string &picture)
	: Rectangle(window, pos_x, pos_y, width, height, picture)
{
	startPosY = pos_y;
	bumped = false;
	collected = false;
}


coin::~coin()
{
}

void coin::drawCoin()
{

	SDL_Rect object_rectangle = { static_cast<int>(rectangle_posX), static_cast<int>(rectangle_posY),
										 rectangle_width, rectangle_height };

	clip.x = (rectangle_width * ((SDL_GetTicks() / 180) % 8));
	clip.y = 0;
	clip.w = 20;
	clip.h = 20;

	if (object_texture)
	{
		SDL_RenderCopy(new_renderer, object_texture, &clip, &object_rectangle);
	}
	
}

void coin::updateCoin(Player *player)
{
	if (!collected)
	{
		if (((player->getPosX() + player->getWidth()) > rectangle_posX) && (player->getPosX() < (rectangle_posX + rectangle_width))
			&& ((player->getPosY() + player->getHeight()) > rectangle_posY) && (player->getPosY() < (rectangle_posY + rectangle_height)))
		{
			collected = true;
			player->incrementCollectedCoinsCounter();
		}

		drawCoin();

		if ((rectangle_posY >= startPosY - 60) && !bumped)
		{
			rectangle_posY -= 5;
			finalPosition = rectangle_posY;

			if (rectangle_posY <= startPosY - 60) bumped = true;
		}
		else
		{
			if (rectangle_posY <= finalPosition) speedY = 1;
			if (rectangle_posY >= finalPosition + 20) speedY = -1;

			rectangle_posY = rectangle_posY + speedY * 0.35;

		}
	}
}
