#pragma once
#include <string>
#include "SDL_mixer.h"
#include <iostream>
#include "SDL.h"

class AudioManager
{
private:

	static AudioManager *sInstance;

	AudioManager();
	~AudioManager();
public:

	static AudioManager *Instance();
	static void Release();

	void PlayMusic(const std::string &filepath, int loops = -1);
	void PlayChunk(const std::string &filepath, int loops = 0, int channel =-1);
};