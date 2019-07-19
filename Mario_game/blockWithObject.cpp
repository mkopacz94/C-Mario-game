#include "blockWithObject.h"

blockWithObject::blockWithObject(const Window &window, float pos_x, float pos_y, int width, int height, const string &picture,
	int hiddenItemType, bool visibility) : Rectangle(window, pos_x, pos_y, width, height, picture)
{
	itemVisible = false;
	bumped = false;
	blockVisible = visibility;

	switch (hiddenItemType)
	{
	case 0:
		hiddenObject = spartanHelmetToCollect;
		break;
		
	case 1:
		hiddenObject = coins;
		
		break;

	default:
		hiddenObject = emptyBlock;
		break;
	}
}

blockWithObject::~blockWithObject()
{
}

void blockWithObject::drawBlock()
{
	if (blockVisible)
	{
		SDL_Rect object_rectangle = { static_cast<int>(rectangle_posX), static_cast<int>(rectangle_posY),
										 rectangle_width, rectangle_height };

		if (bumped)
		{
			clip.x = 55;
			clip.y = 0;
			clip.w = 55;
			clip.h = 55;
		}
		else
		{
			clip.x = 0;
			clip.y = 0;
			clip.w = 55;
			clip.h = 55;
		}

		if (object_texture)
		{
			SDL_RenderCopy(new_renderer, object_texture, &clip, &object_rectangle);
		}
	}
}

void blockWithObject::updateBlock()
{
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
}

void blockWithObject::bumpUpBlock()
{
	bumpUp = true;
	bumped = true;
	itemVisible = true;
	blockVisible = true;
}

bool blockWithObject::isItemVisible()
{
	return itemVisible;
}

bool blockWithObject::isBlockVisible()
{
	return blockVisible;
}