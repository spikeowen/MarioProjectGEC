#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
#include <iostream>
using namespace std;

//Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;

//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();

int main(int argc, char* args[])
{
	//check if SDL is setup correctly
	if (InitSDL())
	{
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
		//set the time
		g_old_time = SDL_GetTicks();

		//Check for quit
		bool quit = false;
		//Game Loop
		while (!quit)
		{
			Render();
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
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_renderer != nullptr)
		{
			//init PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}
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

	//Release renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

	//Destroy game screen manager
	delete game_screen_manager;
	game_screen_manager = nullptr;
}

bool Update()
{
	Uint32 new_time = SDL_GetTicks();
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
	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;
	return false;
}

void Render()
{
	//Clear screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	game_screen_manager->Render();

	//Update Screen
	SDL_RenderPresent(g_renderer);
}

