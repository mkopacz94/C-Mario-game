#include "AudioManager.h"

AudioManager *AudioManager::sInstance = nullptr;

AudioManager *AudioManager::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new AudioManager();
	}

	return sInstance;
}

void AudioManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

AudioManager::AudioManager()
{
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		std::cout << "Audio mixer initialization error." << std::endl;
	}
}

AudioManager::~AudioManager()
{
	Release();
	Mix_Quit();
}

void AudioManager::PlayMusic(const std::string &filepath, int loops)
{
	std::string fullPath; 
	fullPath.append("music/" + filepath);

	Mix_PlayMusic(Mix_LoadMUS(fullPath.c_str()), loops);
}

void AudioManager::PlayChunk(const std::string &filepath, int loops, int channel)
{
	std::string fullPath;
	fullPath.append("music/" + filepath);

	Mix_PlayChannel(channel, Mix_LoadWAV(fullPath.c_str()), loops);
}