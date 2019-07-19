#pragma once
#include <string>
#include "SDL.h"

using namespace std;
class TextureManager {
public:
	static SDL_Texture* LoadTexture(const string &picture, SDL_Renderer *current_renderer);
};