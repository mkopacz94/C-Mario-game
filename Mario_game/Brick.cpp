#include "Brick.h"


Brick::Brick(const Window &window, float pos_x, float pos_y, int width, int height, const string &picture,
	bool objectDestructible, bool objectHiddenInside)
	: Rectangle(window, pos_x, pos_y, width, height, picture)
{
	destructible = objectDestructible;
	collisionAllowed = true;
	currentAnimationFrame = 1;
}

Brick::~Brick()
{
}

void Brick::reinitialize()
{
	collisionByHead = false;
	collisionAllowed = true;
	currentAnimationFrame = 1;
}

void Brick::drawBrick()
{
	SDL_Rect object_rectangle = { static_cast<int>(rectangle_posX), static_cast<int>(rectangle_posY),
									 rectangle_width, rectangle_height };

	if (bumpUp)
	{
		if (currentAnimationFrame == 3)
		{
			rectangle_posY -= 4;
		}
		if (currentAnimationFrame == 6)
		{
			rectangle_posY -= 4;
		}
		if (currentAnimationFrame == 9)
		{
			rectangle_posY -= 4;
		}
		if (currentAnimationFrame == 12)
		{
			rectangle_posY += 4;
		}
		if (currentAnimationFrame == 15)
		{
			rectangle_posY += 4;
		}
		if (currentAnimationFrame == 18)
		{
			rectangle_posY += 4;
			currentAnimationFrame = 0;
			bumpUp = false;
		}

		currentAnimationFrame++;
	}

	if(collisionByHead && destructible)
	{
		update(0.5);
			if (currentAnimationFrame == 5)
			{
				clip.x = 55;
				clip.w = 55;
				clip.h = 55;
				speedY = -20;
			}
			if (currentAnimationFrame==10)
			{
				clip.x = 110;
				clip.w = 70;
				clip.h = 60;
		
				

			}
			else if (currentAnimationFrame == 15)
			{
				clip.x = 180;
				clip.w = 86;
				clip.h = 80;

	
			}
			else if (currentAnimationFrame == 20)
			{
				clip.x = 275;
				clip.w = 151;
				clip.h = 132;


			}

			else if (currentAnimationFrame == 25)
			{
				clip.x = 0;
				clip.y = 135;
				clip.w = 150;
				clip.h = 140;

			}

			currentAnimationFrame++;
		
		
	}
	else
	{
		clip.w = 55;
		clip.h = 55;
		clip.x = 0;
		clip.y = 0;
	}
	object_rectangle.w = clip.w;
	object_rectangle.h = clip.h;

	if (object_texture)
	{
		SDL_RenderCopy(new_renderer, object_texture, &clip, &object_rectangle);
	}
}

void Brick::update(float dt)
{
	rectangle_posY = rectangle_posY + speedY * dt;

	//UPDATE Y POSITION
	speedY += Gravity * dt;

	
}

bool Brick::isDestructible()
{
	return destructible;
}

void Brick::bumpUpBrick()
{
	bumpUp = true;
}