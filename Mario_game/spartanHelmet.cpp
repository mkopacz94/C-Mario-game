#include "spartanHelmet.h"

spartanHelmet::spartanHelmet(const Window &window, float pos_x, float pos_y, int width, int height,
	const string &picture)
	: Rectangle(window, pos_x, pos_y, width, height, picture)
{
	helmetCollected = bumped =false;

	startPosX = pos_x;
	startPosY = pos_y;
	speedX = 0;
	speedY = 0;
}

spartanHelmet::~spartanHelmet()
{

}

void spartanHelmet::drawHelmet()
{
	if (!helmetCollected)
	{
		SDL_Rect object_rectangle = { static_cast<int>(rectangle_posX), static_cast<int>(rectangle_posY),
										rectangle_width, rectangle_height };
		if (bumped)
		{
			if (speedX >= 0) clip.y = 0;
			else clip.y = 59;

			clip.x = (rectangle_width * ((SDL_GetTicks() / 150) % 4));
			
		}
		else
		{
			clip.x = 0;
			clip.y = 0;
		}

		clip.w = 90;
		clip.h = 59;

		if (object_texture)
		{
			SDL_RenderCopy(new_renderer, object_texture, &clip, &object_rectangle);
		}
	}
}

void spartanHelmet::update(float dt)
{
	//UPDATE X POSITION
	if (!helmetCollected)
	{
		if (!bumped && rectangle_posY==startPosY)
		{
			speedY = -3;
		}
		else if (rectangle_posY <= startPosY - 60 && !bumped)
		{
			bumped = true;
			speedX = 3;
		}

		rectangle_posX = rectangle_posX + speedX * dt;

		rectangle_posY = rectangle_posY + speedY * dt;


		//UPDATE Y POSITION

	//	speedY += Gravity * dt;

		boundaries();
	}
}

void spartanHelmet::boundaries()
{
	if (rectangle_posY <= 0) speedY *= -1;
	if (rectangle_posY + rectangle_height >= 490) speedY *= -1;
	if (rectangle_posX <= startPosX - 300) speedX *= -1;
	if (rectangle_posX >= startPosX + 300) speedX *= -1;
}

float spartanHelmet::getStartPosX()
{
	return startPosX;
}

void spartanHelmet::changeStartPosX(float updatedStartPosX)
{
	startPosX = updatedStartPosX;
}

void spartanHelmet::collisionWithPlayer(Player *player)
{
	if (!helmetCollected && bumped)
	{
		if (((player->getPosX() + player->getWidth()) > rectangle_posX) && (player->getPosX() < (rectangle_posX + rectangle_width))
			&& ((player->getPosY() + player->getHeight()) > rectangle_posY) && (player->getPosY() < (rectangle_posY + rectangle_height)))
		{
			helmetCollected = true;
			player->setSpartanMode();
		}
	}
}