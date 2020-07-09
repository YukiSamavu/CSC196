// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Graphics/Shape.h"
#include "Object/Actor.h"
#include <iostream>
#include <string>

nc::Shape ship;
nc::Transform transform{ {400, 300}, 5,0 };

nc::Actor player;
nc::Actor enemy;

float speed = 5.0f;

float frameTime;
float roundTime{ 0 };
bool gameOver{ false };

DWORD prevTime;
DWORD deltaTime;

bool Update(float dt)
{
	frameTime = dt;
	roundTime += dt;
	if (roundTime >= 5) gameOver = true ;
	
	if (gameOver) dt = -1;
	//get delta time
	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;


	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x, y;
	Core::Input::GetMousePos(x,y);

	//nc::Vector2 target = nc::Vector2{ x, y };
	//nc::Vector2 direction = target - position;// head - tail <-
	//direction.Normalize();
	//position = position + (direction * speed);

	nc::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * speed; }
	nc::Vector2 direction = force * dt;
	direction = nc::Vector2::Rotate(direction, transform.angle);

	transform.position = transform.position + direction;

	if (transform.position.x > 800.0f) { transform.position.x = 0; }
	if (transform.position.x < 0.0f) { transform.position.x = 800; }
	if (transform.position.y > 600.0f) { transform.position.y = 0; }
	if (transform.position.y < 0.0f) { transform.position.y = 600; }

	//if (Core::Input::IsPressed('A')) position += nc::Vector2::left * speed;
	//if (Core::Input::IsPressed('D')) position += nc::Vector2::right * speed;
	//if (Core::Input::IsPressed('S')) position += nc::Vector2::down * speed;
	//if (Core::Input::IsPressed('W')) position += nc::Vector2::up * speed;

	if (Core::Input::IsPressed('A')) transform.angle -= dt * 2.0f;
	if (Core::Input::IsPressed('D')) transform.angle += dt * 2.0f;

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 1,1,1 });
	graphics.DrawString(10, 10,std::to_string(frameTime).c_str());
	graphics.DrawString(10, 20,std::to_string(1.0f / frameTime).c_str());
	graphics.DrawString(10, 30,std::to_string(deltaTime / 1000.0f).c_str());

	if (gameOver) graphics.DrawString(400, 300, "Game Over!");
	player.Draw(graphics);
	enemy.Draw(graphics);


}

int main()
{
	DWORD time = GetTickCount();
	std::cout << time / 1000 / 60 / 60 / 24 << std::endl;

	ship.Load("ship.txt");
	player.Load("Player.txt");
	enemy.Load("Enemy.txt");

	char name[] = "Yuki's Game";
	Core::Init(name, 800, 600, 90);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
};

