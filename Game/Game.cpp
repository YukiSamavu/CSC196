#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Graphics/Shape.h"
#include "Object/Actor.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Object/Scene.h"
#include <iostream>
#include <string>
#include <list>

nc::Scene scene;

float frameTime;
float spawnTimer{ 0 };

/*
template <typename T>
nc::Actor* GetActor()
{
	nc::Actor* actor{ nullptr };

	for (nc::Actor* a : sceneActors)
	{
		actor = dynamic_cast<T*>(a);

		if (actor != nullptr) break;
	}

	return actor;
}

template <typename T>
std::vector<T*> GetActors()
{
	std::vector<T*> actors;

	for (nc::Actor* a : sceneActors)
	{
		T* actor = dynamic_cast<T*>(a);
		if (actor)
		{
			actors.push_back(actor);
		}
	}

	return actors;
}
*/

bool Update(float dt)
{
	frameTime = dt;
	spawnTimer += dt;

	/*
	if (spawnTimer >= 3.0f)
	{
		spawnTimer = 0.0f;

		Enemy* e = new Enemy;
		e->Load("enemy.txt");
		e->SetTarget(GetActor<Player>());
		e->SetSpeed(nc::random(50, 100));

		e->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };

		scene.AddActor(e);
	}
	*/

	/*
	if (Core::Input::IsPressed(VK_SPACE))
	{
		auto enemies = GetActors<Enemy>();
		for (Enemy* enemy : enemies)
		{
			scene.RemoveActor(enemy);
		}
	}
	*/

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x, y;
	Core::Input::GetMousePos(x,y);

	scene.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 1,1,1 });
	graphics.DrawString(10, 10,std::to_string(frameTime).c_str());
	graphics.DrawString(10, 20,std::to_string(1.0f / frameTime).c_str());

	scene.Draw(graphics);
}

int main()
{
	scene.Startup();

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

	scene.Shutdown();

	Core::GameLoop();
	Core::Shutdown();
};

