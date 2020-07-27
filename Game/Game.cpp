#include "Game.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Math/Math.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
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
}

bool Game::Update(float dt)
{
	m_frameTime = dt;
	m_spawnTimer += dt;
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	switch (m_state)
	{
	case Game::eState::TITLE:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			m_state = eState::INIT_GAME;
			g_audioSystem.PlayAudio("BG");
		}
		break;
	case::Game::eState::INIT_GAME:
		m_score = 0;
		m_lives = 3;
		m_state = eState::START_GAME;
		break;
	case Game::eState::START_GAME:
	{
		Player* player = new Player;
		player->Load("player.txt");
		m_scene.AddActor(player);

		for (size_t i = 0; i < 10; i++)
		{
			nc::Actor* e = new Enemy;
			e->Load("enemy.txt");
			dynamic_cast<Enemy*>(e)->SetTarget(player);
			dynamic_cast<Enemy*>(e)->SetSpeed(nc::random(50, 100));
			e->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };
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
			e->SetSpeed(nc::random(50, 100));

			e->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };

			m_scene.AddActor(e);
		}

		m_scene.Update(dt);

		/*
		if (m_score == 10)
		{
			Enemy* e = new Enemy;
			e->Load("Satan.txt");
			e->SetTarget(m_scene.GetActor<Player>());
			e->SetSpeed(150);

			e->GetTransform().position = nc::Vector2{ 400, 300 };

			m_scene.AddActor(e);
		}
		*/
	}
		break;
	case Game::eState::GAME_OVER:
		m_stateTimer += dt;
		if (m_stateTimer >= 3)
		{
			m_scene.RemoveAllActors();

			m_state = eState::TITLE;
			m_stateTimer = 0;
		}
		break;
	default:
		break;
	}

	int x, y;
	Core::Input::GetMousePos(x, y);
	if (Core::Input::IsPressed('E'))
	{
		g_particlesSystem.Create({x,y}, 0, 180, 2500, 1, nc::Color{ nc::random(0,1),nc::random(0,1),nc::random(0,1) }, 100, 200);
	}

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
	{
		std::string score = "Score: " + std::to_string(m_score);
		graphics.DrawString(700, 10, score.c_str());
		m_scene.Draw(graphics);
	}
		break;
	case Game::eState::GAME_OVER:
		graphics.DrawString(400, 300, "GAME OVER");
		break;
	default:
		break;
	}

	graphics.SetColor(nc::Color{ 1,1,1 });
	std::string score = "High Score: " + std::to_string(m_highScore);
	graphics.DrawString(350, 10, score.c_str());

	g_particlesSystem.Draw(graphics);
}
