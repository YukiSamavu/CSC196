#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Graphics/Shape.h"
#include "Object/Actor.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Object/Scene.h"
#include "Graphics/PartilcesSystem.h"
#include <iostream>
#include <string>
#include <list>

nc::Scene scene;
nc::ParticlesSystem ps;

float frameTime;
float spawnTimer{ 0 };

bool Update(float dt)
{
	frameTime = dt;
	spawnTimer += dt;

	if (spawnTimer >= 3.0f)
	{
		spawnTimer = 0.0f;

		Enemy* e = new Enemy;
		e->Load("enemy.txt");
		e->SetTarget(scene.GetActor<Player>());
		e->SetSpeed(nc::random(50, 100));

		e->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };

		scene.AddActor(e);
	}

	Player* player = scene.GetActor<Player>();
	ps.Create(player->GetTransform().position, player->GetTransform().angle + nc::PI, 20, 1, 1, nc::Color{ 1,1,1 }, 100, 200);

	if (Core::Input::IsPressed('E'))
	{
		ps.Create(player->GetTransform().position, player->GetTransform().angle + nc::PI, 180, 1000, 1, nc::Color{ nc::random(0,1),nc::random(0,1),nc::random(0,1) }, 100, 200);
	}

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x, y;
	Core::Input::GetMousePos(x,y);

	ps.Update(dt);
	scene.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 1,1,1 });
	graphics.DrawString(10, 10,std::to_string(frameTime).c_str());
	graphics.DrawString(10, 20,std::to_string(1.0f / frameTime).c_str());

	ps.Draw(graphics);
	scene.Draw(graphics);
}

int main()
{
	// start engine
	scene.Startup();
	ps.Startup();

	Player* player = new Player;
	player->Load("player.txt");
	scene.AddActor(player);

	for (size_t i = 0; i < 10; i++)
	{
		nc::Actor* e = new Enemy;
		e->Load("enemy.txt");
		dynamic_cast<Enemy*>(e)->SetTarget(player);
		dynamic_cast<Enemy*>(e)->SetSpeed(nc::random(50, 100));
		e->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };
		scene.AddActor(e);
	}

	char name[] = "Yuki's Game";
	Core::Init(name, 800, 600, 90);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();

	// shutdown engine
	ps.Shutdown();
	scene.Shutdown();
};

