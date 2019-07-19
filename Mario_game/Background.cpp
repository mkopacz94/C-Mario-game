#include "Background.h"
#include <SDL_image.h>
#include <iostream>

using namespace std;

Background::Background(const Rectangle &rectangle, int pos_x, int pos_y, int width, int height, const std::string &image) :
	Rectangle(rectangle), backgound_posX(pos_x), background_posY(pos_y), background_width(width), background_height(height)
{
	auto surface = IMG_Load(image.c_str());

	if (!surface) cerr << "Failed to create surface." << endl;
		
	background_texture = SDL_CreateTextureFromSurface(new_renderer, surface);

	if (!background_texture) cerr << "Failed to create texture." << endl;

	SDL_FreeSurface(surface);

	draw();
	
}

Background::~Background()
{
	SDL_DestroyTexture(background_texture);
}

void Background::draw() const
{
	SDL_Rect background_rectangle = { backgound_posX, background_posY, background_width, background_height };

	if (background_texture)
	{
		SDL_RenderCopy(new_renderer, background_texture, nullptr, &background_rectangle);
	}

	SDL_RenderPresent(new_renderer);
}