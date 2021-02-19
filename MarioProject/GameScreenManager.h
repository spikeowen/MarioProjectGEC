#pragma once
#include "SDL.h"
#include "Commons.h"
//MACRO
#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

class GameScreen;

class GameScreenManager
{
private:
	SDL_Renderer* m_renderer;
	GameScreen* m_current_screen;
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS new_screen);
};

#endif //_GAMESCREENMANAGER_H