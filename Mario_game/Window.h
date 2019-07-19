#pragma once

#include <string>
#include <iostream>
#include "SDL.h"
#include "AudioManager.h"

using namespace std;

class Window
{
public:

	Window(const std::string &title, int width, int height);
	Window();
	virtual ~Window();

	void clear() const;
	void updateRender() const;
	void detectEvents(SDL_Event &event);
	inline bool isClosed() const { return window_closed; }
	
private:

	bool init();

	string window_title;

	SDL_Window *new_window = nullptr;

protected:
	int window_width, window_height;
	bool window_closed = false;
	SDL_Renderer *new_renderer = nullptr;
	AudioManager *soundPlayer;
};