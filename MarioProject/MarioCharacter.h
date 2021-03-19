#pragma once
#include "Character.h"
//MACRO
#ifndef _MARIOCHARACTER_H
#define _MARIOCHARACTER_H

class MarioCharacter : public Character
{
public:
	MarioCharacter(SDL_Renderer* renderer, string imagePath, Vector2D start_position);
	~MarioCharacter();
	void Update(float deltaTime, SDL_Event e) override;
	void Render();
};

#endif //_MARIOCHARACTER_H