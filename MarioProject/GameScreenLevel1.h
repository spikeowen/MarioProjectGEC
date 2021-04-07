#pragma once
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "MarioCharacter.h"
#include "LuigiCharacter.h"
#include "LevelMap.h"
//MACRO
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

class Texture2D;
class Character;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* m_background_texture;
	bool SetUpLevel();
	LuigiCharacter* luigi_character;
	MarioCharacter* mario_character;
	void SetLevelMap();
	LevelMap* m_level_map;

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
};

#endif //_GAMESCREENLEVEL1_H