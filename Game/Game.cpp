#include "Game.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Math/Math.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Boss.h"
#include "Actors/Locator.h"
#include "Actors/OneUp.h"
#include "Actors/SpeedBoost.h"
#include "Graphics/PartilcesSystem.h"
#include "Audio/AudioSystem.h"
#include <iostream>
#include <string>

void Game::Initialize()
{
	// start engine
	m_scene.Startup();
	m_scene.SetGame(this);
	g_audioSystem.AddAudio("Laser", "Laser.wav");
	g_audioSystem.AddAudio("Explosion", "Explosion.wav");
	g_audioSystem.AddAudio("BG", "BackGroundMusic.wav");
	g_audioSystem.AddAudio("BossMusic", "BossMusic.wav");
	g_audioSystem.AddAudio("PowerUp", "Powerup.wav");
}

bool Game::Update(float dt)
{
	m_frameTime = dt;
	m_spawnTimer += dt;
	m_oneUpTimer += dt;
	m_scoreBoostTimer += dt;
	float ScoreBoosSpawningTimer = nc::random(100,200);
	//float ScoreBoosSpawningTimer = 10;
	float OneUpSpawningTimer = nc::random(100,200);
	//float OneUpSpawningTimer = 10;
	m_bossTimer += dt;
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	switch (m_state)
	{
	case Game::eState::START_AUDIO:
		g_audioSystem.PlayAudio("BG");
		m_state = eState::TITLE;
		break;
	case Game::eState::TITLE:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			m_state = eState::INIT_GAME;
		}
		break;
	case Game::eState::INIT_GAME:
		m_score = 0;
		m_lives = 3;
		m_state = eState::START_GAME;
		break;
	case Game::eState::START_GAME:
	{
		Player* player = new Player;
		player->Load("player.txt");
		m_scene.AddActor(player);

		Locator* locator = new Locator;
		locator->GetTransform().position = nc::Vector2{ 2,2 };
		player->AddChild(locator);

		locator = new Locator;
		locator->GetTransform().position = nc::Vector2{ -2,2 };
		player->AddChild(locator);

		for (size_t i = 0; i < 5; i++)
		{
			Enemy* e = new Enemy;
			e->Load("enemy.txt");
			dynamic_cast<Enemy*>(e)->SetTarget(player);
			//dynamic_cast<Enemy*>(e)->SetSpeed(nc::random(50, 100));
			float distance = nc::random(150, 300);
			float angle = nc::random(0, nc::TWO_PI);
			nc::Vector2 position = nc::Vector2::Rotate({0.0f,distance}, angle);
			e->GetTransform().position = m_scene.GetActor<Player>()->GetTransform().position + position;
			if (e->GetTransform().position.x > 800)
			{
				e->GetTransform().position.x = 800;
			}
			else if (e->GetTransform().position.x < 0)
			{
				e->GetTransform().position.x = 0;
			}
			if (e->GetTransform().position.y > 600)
			{
				e->GetTransform().position.y = 600;
			}
			else if (e->GetTransform().position.y < 0)
			{
				e->GetTransform().position.y = 0;
			}
			e->SetFireRate(nc::random(5.0f, 10.0f));
			m_scene.AddActor(e);
		}

		m_state = eState::GAME;
	}
		break;
	case Game::eState::GAME:
	{
		if (m_score > m_highScore) m_highScore = m_score;

		if (m_spawnTimer >= 3.0f)
		{
			m_spawnTimer = 0.0f;

			Enemy* e = new Enemy;
			e->Load("enemy.txt");
			e->SetTarget(m_scene.GetActor<Player>());
			//dynamic_cast<Enemy*>(e)->SetSpeed(nc::random(50, 100));
			float distance = nc::random(150, 300);
			float angle = nc::random(0, nc::TWO_PI);
			nc::Vector2 position = nc::Vector2::Rotate({ 0.0f,distance }, angle);
			e->GetTransform().position = m_scene.GetActor<Player>()->GetTransform().position + position;
			if (e->GetTransform().position.x > 800)
			{
				e->GetTransform().position.x = 800;
			}
			else if (e->GetTransform().position.x < 0)
			{
				e->GetTransform().position.x = 0;
			}
			if (e->GetTransform().position.y > 600)
			{
				e->GetTransform().position.y = 600;
			}
			else if (e->GetTransform().position.y < 0)
			{
				e->GetTransform().position.y = 0;
			}
			e->SetFireRate(nc::random(5.0f, 10.0f));

			m_scene.AddActor(e);
		}

		if (m_oneUpTimer >= OneUpSpawningTimer)
		{
			OneUpSpawningTimer = nc::random(100, 175);

			m_oneUpTimer = 0;

			OneUp* plusOne = new OneUp;
			plusOne->Load("PlusOne.txt");

			plusOne->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };

			m_scene.AddActor(plusOne);
		}

		if (m_bossTimer >= 10)
		{
			m_bossTimer = 0;
			//m_state = eState::BOSS_FIGHT;
		}

		if (m_scoreBoostTimer >= ScoreBoosSpawningTimer)
		{
			ScoreBoosSpawningTimer = nc::random(100, 175);

			m_scoreBoostTimer = 0;

			SpeedBoost* speedboost = new SpeedBoost;
			speedboost->Load("SpeedBoost.txt");

			speedboost->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };

			m_scene.AddActor(speedboost);
		}
	}
		break;
	case Game::eState::BOSS_FIGHT:
		//g_audioSystem.PlayAudio("BossMusic");

		//Delete All Enemies
		/*
		Enemy* enemy = m_scene.GetActor<Enemy>();
	    m_scene.RemoveActor(enemy);
		auto enemies = m_scene.GetActors<Enemy>();
		for (Enemy* enemy : enemies)
		{
			m_scene.RemoveActor(enemy);
		}
		*/
		break;
	case Game::eState::PLAYER_DEAD:
		m_lives = m_lives - 1;
		m_state = (m_lives == 0) ? eState::GAME_OVER : eState::GAME_WAIT;
		m_stateTimer = 3;
		break;
	case Game::eState::GAME_WAIT:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene.RemoveAllActors();
			m_state = eState::START_GAME;
		}
		break;
	case Game::eState::GAME_OVER:
		m_stateTimer -= dt;
		m_scene.RemoveAllActors();
		if (m_stateTimer <= 0)
		{
			m_state = eState::TITLE;
		}
		break;
	default:
		break;
	}

	m_scene.Update(dt);

	g_audioSystem.Update(dt);
	g_particlesSystem.Update(dt);

	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 1,1,1 });
	graphics.DrawString(10, 10, std::to_string(m_frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / m_frameTime).c_str());

	switch (m_state)
	{
	case Game::eState::TITLE:
		graphics.DrawString(325, 300, "Yuki's Space Advernture");
		break;
	case Game::eState::START_GAME:
		break;
	case Game::eState::GAME:
		break;
	case Game::eState::GAME_OVER:
		graphics.DrawString(400, 300, "GAME OVER");
		break;
	default:
		break;
	}

	graphics.SetColor(nc::Color{ 1,1,1 });
	std::string score = "Score: " + std::to_string(m_score);
	graphics.DrawString(700, 10, score.c_str());
	std::string lives = "Lives: " + std::to_string(m_lives);
	graphics.DrawString(700, 25, lives.c_str());
	score = "High Score: " + std::to_string(m_highScore);
	graphics.DrawString(350, 10, score.c_str());

	m_scene.Draw(graphics);
	g_particlesSystem.Draw(graphics);
}
