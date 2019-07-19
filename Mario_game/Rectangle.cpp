#include "Rectangle.h"
#include "TextureManager.h"
#include <SDL_image.h>
#include <SDL.h>
#include <math.h>

Rectangle::Rectangle(const Window &window, float pos_x, float pos_y, int width, int height, const string &picture) :
	Window(window), rectangle_posX(pos_x), rectangle_posY(pos_y), rectangle_width(width), rectangle_height(height), rectangle_picture(picture)
{
	speedX = 0;
	object_texture = TextureManager::LoadTexture(rectangle_picture, new_renderer);
	enemyDestroyed = false;
}

Rectangle::Rectangle(float pos_x, float pos_y, int width, int height, const string &picture) :
	rectangle_posX(pos_x), rectangle_posY(pos_y), rectangle_width(width), rectangle_height(height), rectangle_picture(picture)
{
	speedX = 0;
	object_texture = TextureManager::LoadTexture(rectangle_picture, new_renderer);
}


Rectangle::~Rectangle()
{
	SDL_DestroyTexture(object_texture);
}

void Rectangle::draw() 
{
	SDL_Rect object_rectangle = { static_cast<int>(rectangle_posX), static_cast<int>(rectangle_posY), 
								rectangle_width, rectangle_height };

	if (object_texture)
	{
		SDL_RenderCopy(new_renderer, object_texture, nullptr, &object_rectangle);
	}
}

vector<int> Rectangle::getPositionxy()
{
	vector<int> position(2);

	position[0] = static_cast<int>(rectangle_posX);
	position[1] = static_cast<int>(rectangle_posY);

	return position;
}

vector<int> Rectangle::getWidthHeight()
{
	vector<int> size(2);

	size[0] = rectangle_width;
	size[1] = rectangle_height;

	return size;
}

void Rectangle::changeRectanglePosition(int pos_x, int pos_y)
{
	rectangle_posX = static_cast<float>(pos_x);
	rectangle_posY = static_cast<float>(pos_y);
}

float Rectangle::getSpeedX()
{
	return speedX;
}

float Rectangle::getSpeedY()
{
	return speedY;
}

void Rectangle::setSpeedX(float speed)
{
	speedX = speed;
}

void Rectangle::setSpeedY(float speed)
{
	speedY = speed;
}

float Rectangle::getPosX()
{
	return rectangle_posX;
}

float Rectangle::getPosY()
{
	return rectangle_posY;
}

int Rectangle::getWidth()
{
	return rectangle_width;
}

int Rectangle::getHeight()
{
	return rectangle_height;
}

bool Rectangle::isHiddenInShell()
{
	return hiddenInShell;
}

void Rectangle::setHitByShell(bool state)
{
	hitByShell = state;
}

void Rectangle::setHiddenInShell(bool state)
{
	hiddenInShell = state;
}

void Rectangle::setHeadCollision(bool state)
{
	collisionByHead = state;
}

void Rectangle::setCollisionAllowed(bool state)
{
	collisionAllowed = state;
}

bool Rectangle::isCollisionAllowed()
{
	return collisionAllowed;
}