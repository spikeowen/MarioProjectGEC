#include "GameScreenLevel2.h"
#include <iostream>

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel2::~GameScreenLevel2()
{
	delete m_background_texture;
	m_background_texture = nullptr;
	delete luigi_character;
	luigi_character = nullptr;
	delete mario_character;
	mario_character = nullptr;
	delete m_pow_block;
	m_pow_block = nullptr;

	m_koopas.clear();
	m_coins.clear();
	m_goombas.clear();
}

void GameScreenLevel2::Render()
{
	//Draw Koopas
	for (int i = 0; i < m_koopas.size(); i++)
	{
		m_koopas[i]->Render();
	}

	//Draw Coins
	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render();
	}

	//Draw Coins
	for (int i = 0; i < m_goombas.size(); i++)
	{
		m_goombas[i]->Render();
	}

	//Draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	//Draw Characters
	luigi_character->Render();
	mario_character->Render();
	m_pow_block->Render();
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}

	//update characters
	luigi_character->Update(deltaTime, e);
	mario_character->Update(deltaTime, e);

	UpdatePOWBlock();
	UpdateKoopas(deltaTime, e);

	UpdateCoins(deltaTime, e);
	UpdateGoombas(deltaTime, e);

	//SPAWN NEW ENEMIES
	m_respawn_enemy -= deltaTime;
	if (m_respawn_enemy <= 0.0f)
	{
		CreateKoopa(Vector2D(450, 330), FACING_LEFT, KOOPA_SPEED);
		CreateGoomba(Vector2D(25, 330), FACING_RIGHT, GOOMBA_SPEED);
		m_respawn_enemy = ENEMY_RESPAWN;
	}

	//if (Collisions::Instance()->Circle(mario_character->GetCollisionCircle(), luigi_character->GetCollisionCircle()))
	//{
	//	cout << "Circle hit!" << endl;
	//}

	//if (Collisions::Instance()->Box(mario_character->GetCollisionBox(), luigi_character->GetCollisionBox()))
	//{
	//	cout << "Box hit!" << endl;
	//}
}

bool GameScreenLevel2::SetUpLevel()
{
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	SetLevelMap();

	//set up player character
	luigi_character = new LuigiCharacter(m_renderer, "Images/Luigi.png", Vector2D(128, 25), m_level_map);
	mario_character = new MarioCharacter(m_renderer, "Images/Mario.png", Vector2D(64, 25), m_level_map);

	CreateKoopa(Vector2D(25, 330), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(450, 330), FACING_LEFT, KOOPA_SPEED);

	CreateCoin(Vector2D(170, 330));
	CreateCoin(Vector2D(325, 330));

	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;
	m_respawn_enemy = ENEMY_RESPAWN;
}

void GameScreenLevel2::SetLevelMap()
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

void GameScreenLevel2::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(mario_character->GetCollisionBox(), m_pow_block->GetCollisionBox()) && m_pow_block->IsAvailable())
	{
		if (mario_character->IsJumping())
		{
			cout << "POW Block hit!" << endl;
			DoScreenShake();
			m_pow_block->TakeHit();
			mario_character->CancelJump();
		}
	}
	else if (Collisions::Instance()->Box(luigi_character->GetCollisionBox(), m_pow_block->GetCollisionBox()) && m_pow_block->IsAvailable())
	{
		if (luigi_character->IsJumping())
		{
			cout << "POW Block hit!" << endl;
			DoScreenShake();
			m_pow_block->TakeHit();
			luigi_character->CancelJump();
		}
	}
}

void GameScreenLevel2::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (int i = 0; i < m_koopas.size(); i++)
	{
		m_koopas[i]->TakeDamage();
	}

	for (int i = 0; i < m_goombas.size(); i++)
	{
		m_goombas[i]->Jump();
	}

	/*for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Jump();
	}*/
}



void GameScreenLevel2::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	KoopaCharacter* koopa = new KoopaCharacter(m_renderer, "Images/Koopa.png", m_level_map, position, direction, speed);
	m_koopas.push_back(koopa);
}

void GameScreenLevel2::CreateCoin(Vector2D position)
{
	Coin* coin = new Coin(m_renderer, "Images/Coin.png", m_level_map, position);
	m_coins.push_back(coin);
}

void GameScreenLevel2::CreateGoomba(Vector2D position, FACING direction, float speed)
{
	Goomba* goomba = new Goomba(m_renderer, "Images/Goomba.png", m_level_map, position, direction, speed);
	m_goombas.push_back(goomba);
}

void GameScreenLevel2::UpdateKoopas(float deltaTime, SDL_Event e)
{
	if (!m_koopas.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_koopas.size(); i++)
		{
			//check if the enemy is past middle of the screen
			if (m_koopas[i]->GetPosition().y > 150.0f)
			{
				//is the enemy off screen to the left / right?
				if (m_koopas[i]->GetPosition().x < (float)(-m_koopas[i]->GetCollisionBox().width * 0.5f)
					|| m_koopas[i]->GetPosition().x > SCREEN_WIDTH - (float)(m_koopas[i]->GetCollisionBox().width * 0.5f))
				{
					//Flip the koopas at edge of screen 
					m_koopas[i]->EdgeFlip();
					std::cout << "Koopa should have flipped." << std::endl;

					//m_koopas[i]->SetAlive(false);
				}
			}

			m_koopas[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_koopas[i]->GetPosition().y > 300.0f || m_koopas[i]->GetPosition().y <= 64.0f) && (m_koopas[i]->GetPosition().x < 64.0f
				|| m_koopas[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_koopas[i]->GetCollisionCircle(), mario_character->GetCollisionCircle()))
				{
					if (mario_character->IsJumping())
					{
						if (m_koopas[i]->GetInjured())
						{
							cout << "Koopa Killed!" << endl;
							m_koopas[i]->SetAlive(false);
							mario_character->CancelJump();
						}
						else
						{
							cout << "Koopa hit!" << endl;
							m_koopas[i]->TakeDamage();
							mario_character->CancelJump();
						}
					}
					else if (!m_koopas[i]->GetInjured())
					{
						//kill mario
						mario_character->SetAlive(false);
					}
				}
				else if (Collisions::Instance()->Circle(m_koopas[i]->GetCollisionCircle(), luigi_character->GetCollisionCircle()))
				{
					if (luigi_character->IsJumping())
					{
						if (m_koopas[i]->GetInjured())
						{
							cout << "Koopa Killed!" << endl;
							m_koopas[i]->SetAlive(false);
							luigi_character->CancelJump();
						}
						else
						{
							cout << "Koopa hit!" << endl;
							m_koopas[i]->TakeDamage();
							luigi_character->CancelJump();
						}
					}
					else if (!m_koopas[i]->GetInjured())
					{
						//kill luigi
						luigi_character->SetAlive(false);
					}
				}
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_koopas[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//remove dead enemies -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_koopas.erase(m_koopas.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel2::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (!m_coins.empty())
	{
		int coinIndexToDelete = -1;
		for (unsigned int i = 0; i < m_coins.size(); i++)
		{
			m_coins[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if (Collisions::Instance()->Circle(m_coins[i]->GetCollisionCircle(), mario_character->GetCollisionCircle()))
			{
				if (m_coins[i]->GetAlive())
				{
					cout << "Coin Collected!" << endl;
					coin_count++;
					m_coins[i]->SetAlive(false);
				}
			}
			else if (Collisions::Instance()->Circle(m_coins[i]->GetCollisionCircle(), luigi_character->GetCollisionCircle()))
			{
				if (m_coins[i]->GetAlive())
				{
					cout << "Coin Collected!" << endl;
					coin_count++;
					m_coins[i]->SetAlive(false);
				}
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_coins[i]->GetAlive())
			{
				coinIndexToDelete = i;
			}
		}

		//remove dead enemies -1 each update
		if (coinIndexToDelete != -1)
		{
			m_coins.erase(m_coins.begin() + coinIndexToDelete);
		}
	}
}

void GameScreenLevel2::UpdateGoombas(float deltaTime, SDL_Event e)
{
	if (!m_goombas.empty())
	{
		int goombaIndexToDelete = -1;
		for (unsigned int i = 0; i < m_goombas.size(); i++)
		{
			//check if the enemy is past middle of screen
			if (m_goombas[i]->GetPosition().y > 150.0f)
			{
				//is the enemy off screen to the left / right?
				if (m_goombas[i]->GetPosition().x < (float)(-m_goombas[i]->GetCollisionBox().width * 0.5f)
					|| m_goombas[i]->GetPosition().x > SCREEN_WIDTH - (float)(m_goombas[i]->GetCollisionBox().width * 0.5f))
				{
					//Flip the koopas at edge of screen 
					m_goombas[i]->EdgeFlip();
					std::cout << "Should have flipped Goomba." << std::endl;
				}
			}

			m_goombas[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_goombas[i]->GetPosition().y > 300.0f || m_goombas[i]->GetPosition().y <= 64.0f) && (m_goombas[i]->GetPosition().x < 64.0f
				|| m_goombas[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_goombas[i]->GetCollisionCircle(), mario_character->GetCollisionCircle()))
				{
					if (mario_character->IsJumping())
					{
						cout << "Goomba Killed!" << endl;
						m_goombas[i]->SetAlive(false);
						mario_character->CancelJump();
					}
					else
					{
						//kill mario
						mario_character->SetAlive(false);
					}
				}
				else if (Collisions::Instance()->Circle(m_goombas[i]->GetCollisionCircle(), luigi_character->GetCollisionCircle()))
				{
					if (luigi_character->IsJumping())
					{
						cout << "Goomba Killed!" << endl;
						m_goombas[i]->SetAlive(false);
						luigi_character->CancelJump();
					}
					else 
					{
						//kill luigi
						luigi_character->SetAlive(false);
					}
				}
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_goombas[i]->GetAlive())
			{
				goombaIndexToDelete = i;
			}
		}

		//remove dead enemies -1 each update
		if (goombaIndexToDelete != -1)
		{
			m_goombas.erase(m_goombas.begin() + goombaIndexToDelete);
		}
	}
}