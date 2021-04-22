#pragma once
#include "Character.h"
//MACRO
#ifndef _KOOPACHARACTER_H
#define _KOOPACHARACTER_H

class KoopaCharacter : public Character
{
private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	FACING m_facing_direction;
	float m_movement_speed;

	bool m_injured;
	float m_injured_time;
	void FlipRightWayUp();

public:
	KoopaCharacter(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~KoopaCharacter();

	void Update(float deltaTime, SDL_Event e) override;
	void Render();

	void TakeDamage();
	void Jump();

	bool GetInjured() { return m_injured; }

	void Flip();
	void EdgeFlip();
};

#endif