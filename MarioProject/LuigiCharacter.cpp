#include "LuigiCharacter.h"

LuigiCharacter::LuigiCharacter(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{

}

LuigiCharacter::~LuigiCharacter() {}

void LuigiCharacter::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = true;
			break;
		case SDLK_d:
			m_moving_right = true;
			break;
		case SDLK_w:
			if (m_can_jump == true)
				Jump();
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = false;
			break;
		case SDLK_d:
			m_moving_right = false;
			break;
		}
		break;
	}

	Character::Update(deltaTime, e);
}

void LuigiCharacter::Render()
{
	Character::Render();
}