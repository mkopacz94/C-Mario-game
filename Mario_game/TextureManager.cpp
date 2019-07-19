#include "TextureManager.h"
#include <SDL_image.h>
#include <SDL.h>

SDL_Texture* TextureManager::LoadTexture(const string &picture, SDL_Renderer *current_renderer)
{
	SDL_Surface *tempSurface = IMG_Load(picture.c_str());
	SDL_Texture *new_texture = SDL_CreateTextureFromSurface(current_renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return new_texture;
}





