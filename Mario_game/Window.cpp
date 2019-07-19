#include "Window.h"


Window::Window(const std::string &title = "default", int width=800, int height=600) :
	window_title(title), window_width(width), window_height(height)
{
	window_closed = !init();
}

Window::Window()
{
	window_title = "Default_window";
	window_width = 800;
	window_height = 600;

	window_closed = !init();
}

Window::~Window()
{
	SDL_DestroyRenderer(new_renderer);
	SDL_DestroyWindow(new_window);
	SDL_Quit();
}

bool Window::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "Window initialization failed" << std::endl;
		return 0;
	}

	soundPlayer = AudioManager::Instance();

	new_window = SDL_CreateWindow
	(
		window_title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		window_width, window_height,
		0
	);

	if (new_window == nullptr)
	{
		std::cerr << "Failed to create a window." << std::endl;
		return 0;
	}

	new_renderer = SDL_CreateRenderer(new_window, -1, SDL_RENDERER_ACCELERATED);

	if (new_renderer == nullptr)
	{
		std::cerr << "Failed to create a renderer." << std::endl;
		return 0;
	}

	return true;
}

void Window::detectEvents(SDL_Event &event)
{
	switch (event.type)
	{
	case SDL_QUIT:
		window_closed = true;
		break;

	default:
		break;
	}
}

void Window::clear() const
{
	SDL_RenderClear(new_renderer);
}

void Window::updateRender() const
{
	SDL_RenderPresent(new_renderer);
}