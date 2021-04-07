#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Character.h"
#include "MarioCharacter.h"
#include "Collisions.h"
#include <iostream>

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	m_level_map = nullptr;
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	m_background_texture = nullptr;
	delete luigi_character;
	luigi_character = nullptr;
	delete mario_character;
	mario_character = nullptr;
}

void GameScreenLevel1::Render()
{
	//Draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	luigi_character->Render();
	mario_character->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//update characters
	luigi_character->Update(deltaTime, e);
	mario_character->Update(deltaTime, e);

	//if (Collisions::Instance()->Circle(mario_character->GetCollisionCircle(), luigi_character->GetCollisionCircle()))
	//{
	//	cout << "Circle hit!" << endl;
	//}

	//if (Collisions::Instance()->Box(mario_character->GetCollisionBox(), luigi_character->GetCollisionBox()))
	//{
	//	cout << "Box hit!" << endl;
	//}
}

bool GameScreenLevel1::SetUpLevel()
{
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	SetLevelMap();

	//set up player character
	luigi_character = new LuigiCharacter(m_renderer, "Images/Luigi.png", Vector2D(64, 330), m_level_map);
	mario_character = new MarioCharacter(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = 
	{ 
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
		{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
		{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } 
	};

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);
}