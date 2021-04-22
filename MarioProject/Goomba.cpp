#include "Goomba.h"

Goomba::Goomba(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;

	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();
}

Goomba::~Goomba()
{

}

void Goomba::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE / 3;
		m_jumping = true;
		m_can_jump = false;
	}
}

void Goomba::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	if (m_facing_direction == FACING_LEFT)
	{
		m_moving_left = true;
		m_moving_right = false;
	}
	else if (m_facing_direction == FACING_RIGHT)
	{
		m_moving_right = true;
		m_moving_left = false;
	}

	if (m_alive)
	{
		m_frame_delay -= deltaTime;
		if (m_frame_delay <= 0.0f)
		{
			//reset frame delay count
			m_frame_delay = ANIMATION_DELAY;

			//move the frame over
			m_current_frame++;

			//loop frame around if it goes beyond the number of frames
			if (m_current_frame > 1)
				m_current_frame = 0;
		}
	}
}

void Goomba::Render()
{
	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame,0,m_single_sprite_w, m_single_sprite_h };

	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
}

void Goomba::EdgeFlip()
{
	if (m_facing_direction == FACING_LEFT)
	{
		m_facing_direction = FACING_RIGHT;
		m_position.x = m_position.x + 40.0f;
	}
	else
	{
		m_facing_direction = FACING_LEFT;
		m_position.x = m_position.x - 40.0f;
	}
}