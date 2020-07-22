#include "Game.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Math/Math.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Graphics/PartilcesSystem.h"
#include <iostream>
#include <string>

void Game::Initialize()
{
	// start engine
	m_scene.Startup();
	g_particlesSystem.Startup();

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
}

bool Game::Update(float dt)
{
	m_frameTime = dt;
	m_spawnTimer += dt;

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

	int x, y;
	Core::Input::GetMousePos(x, y);
	if (Core::Input::IsPressed('E'))
	{
		g_particlesSystem.Create({x,y}, 0, 180, 2500, 1, nc::Color{ nc::random(0,1),nc::random(0,1),nc::random(0,1) }, 100, 200);
	}


	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	g_particlesSystem.Update(dt);
	m_scene.Update(dt);

	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 1,1,1 });
	graphics.DrawString(10, 10, std::to_string(m_frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / m_frameTime).c_str());

	g_particlesSystem.Draw(graphics);
	m_scene.Draw(graphics);
}
