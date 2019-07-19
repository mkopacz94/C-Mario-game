#pragma once
#include "Window.h"
#include "Rectangle.h"

class Background : public Rectangle
{
public:
	Background(const Rectangle &rectangle, int pos_x, int pos_y, int width, int height, const std::string &image);
	~Background();

	void draw() const;

private:

	int backgound_posX, background_posY;
	int background_width, background_height;
	std::string background_image;

	SDL_Texture *background_texture = nullptr;
};