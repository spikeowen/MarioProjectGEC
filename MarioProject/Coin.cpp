#include "Coin.h"

Coin::Coin(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position) : Character(renderer, imagePath, start_position, map)
{
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
	m_position = start_position;
}

Coin::~Coin()
{

}

void Coin::Update(float deltaTime, SDL_Event e)
{
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
			if (m_current_frame > 2)
				m_current_frame = 0;
		}
	}
}

void Coin::Render()
{
	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame,0,m_single_sprite_w, m_single_sprite_h };

	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
}

void Coin::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE / 3;
		m_jumping = true;
		m_can_jump = false;
	}
}