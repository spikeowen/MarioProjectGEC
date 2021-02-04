#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "constants.h"
#include <iostream>
using namespace std;

//Globals
SDL_Window* g_window = nullptr;

//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();

int main(int argc, char* args[])
{
	//check if SDL is setup correctly
	if (InitSDL())
	{
		//Check for quit
		bool quit = false;
		//Game Loop
		while (!quit)
		{
			quit = Update();
		}
	}
	CloseSDL();
	return 0;
}

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//setup passed so create window
		g_window = SDL_CreateWindow("Games Engine Creation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (g_window == nullptr)
		{
			//window failed to open
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
		else
			return true;
	}
}

void CloseSDL()
{
	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool Update()
{
	SDL_Event e;

	//get Events
	SDL_PollEvent(&e);

	//handle the events
	switch (e.type)
	{
		//click 'X' to quit
	case SDL_QUIT:
		return true;
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		case SDLK_q:
			return true;
			break;
	}
	return false;
}