#pragma once
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Commons.h"
#include "Character.h"
#include "Texture2D.h"
#include "Collisions.h"
#include "PowBlock.h"
#include "Coin.h"
#include "MarioCharacter.h"
#include "LuigiCharacter.h"
#include "KoopaCharacter.h"
#include "Goomba.h"
#include "LevelMap.h"
#include <vector>
//MACRO
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

class Texture2D;
class Character;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* m_background_texture;
	bool SetUpLevel();

	LuigiCharacter* luigi_character;
	MarioCharacter* mario_character;

	void SetLevelMap();
	LevelMap* m_level_map;

	PowBlock* m_pow_block;

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	void DoScreenShake();

	void UpdateKoopas(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateCoin(Vector2D position);

	void UpdateGoombas(float deltaTime, SDL_Event e);
	void CreateGoomba(Vector2D position, FACING direction, float speed);

	vector<KoopaCharacter*> m_koopas;
	vector<Goomba*> m_goombas;
	vector<Coin*> m_coins;
	float m_respawn_enemy;

	int coin_count;

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void UpdatePOWBlock();
};

#endif //_GAMESCREENLEVEL1_H