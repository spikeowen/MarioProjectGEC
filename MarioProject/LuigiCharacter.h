#pragma once
#include "Character.h"
//MACRO
#ifndef _LUIGICHARACTER_H
#define _LUIGICHARACTER_H

class LuigiCharacter : public Character
{
public:
	LuigiCharacter(SDL_Renderer* renderer, string imagePath, Vector2D start_position);
	~LuigiCharacter();
	void Update(float deltaTime, SDL_Event e) override;
	void Render();
};

#endif //_LUIGICHARACTER_H