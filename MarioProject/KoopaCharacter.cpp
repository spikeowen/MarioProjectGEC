#include "KoopaCharacter.h"

KoopaCharacter::KoopaCharacter(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_injured = false;

	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();
}

KoopaCharacter::~KoopaCharacter()
{

}

void KoopaCharacter::TakeDamage()
{
	m_injured = true;
	m_injured_time = INJURED_TIME;
	Jump();
}

void KoopaCharacter::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE / 3;
		m_jumping = true;
		m_can_jump = false;
	}
	Flip();
}

void KoopaCharacter::FlipRightWayUp()
{
	m_facing_direction == SDL_FLIP_HORIZONTAL;
	m_injured = false;
}

void KoopaCharacter::Render()
{
	//left position of the sprite 
	int left = 0.0f;

	//if injured switch to second image of the sprite sheet
	if (m_injured)
	{
		left = m_single_sprite_w;
	}

	SDL_Rect portion_of_sprite = { left,0,m_single_sprite_w, m_single_sprite_h };

	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}

}

void KoopaCharacter::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	if (!m_injured)
	{
		//Not injured so move
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
	}
	else
	{
		m_moving_right = false;
		m_moving_left = false;

		//count down the injured time
		m_injured_time -= deltaTime;

		if (m_injured_time <= 0.0)
			FlipRightWayUp();
	}
}

void KoopaCharacter::Flip()
{
	if(m_facing_direction == FACING_LEFT)
	{
		m_facing_direction = FACING_RIGHT;
	}
	else
	{
		m_facing_direction = FACING_LEFT;
	}
}

void KoopaCharacter::EdgeFlip()
{
	if (m_facing_direction == FACING_LEFT)
	{
		m_facing_direction = FACING_RIGHT;
		m_position.x = m_position.x + 50.0f;
	}
	else
	{
		m_facing_direction = FACING_LEFT;
		m_position.x = m_position.x - 40.0f;
	}
}