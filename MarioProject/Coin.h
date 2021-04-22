#pragma once
#include "Character.h"
//MACRO
#ifndef _COIN_H
#define _COIN_H

class Coin : public Character
{
private:
	float m_single_sprite_w;
	float m_single_sprite_h;

	float m_frame_delay;
	int m_current_frame;

public:
	Coin(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position);
	~Coin();

	void Update(float deltaTime, SDL_Event e) override;
	void Render();

	void Jump();
};

#endif