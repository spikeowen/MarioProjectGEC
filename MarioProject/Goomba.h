#pragma once
#include "Character.h"
//MACRO
#ifndef _GOOMBA_H
#define _GOOMBA_H

class Goomba : public Character
{
private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	FACING m_facing_direction;
	float m_movement_speed;

	float m_frame_delay;
	int m_current_frame;

public:
	Goomba(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~Goomba();

	void Update(float deltaTime, SDL_Event e) override;
	void Render();

	void Jump();

	void EdgeFlip();
};

#endif

