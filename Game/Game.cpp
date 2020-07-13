// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Graphics/Shape.h"
#include "Object/Actor.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include <iostream>
#include <string>

Player player;
Enemy enemy;

float speed = 300.0f;

nc::Vector2 velocity;
float thrust = 300.0f;

float frameTime;
float roundTime{ 0 };
bool gameOver{ false };

float t{ 0 };

DWORD prevTime;
DWORD deltaTime;

bool Update(float dt)
{
	frameTime = dt;
	roundTime += dt;
	//if (roundTime >= 5) gameOver = true ;
	
	//if (gameOver) dt = 0;

	t = t + (dt * 1.0f);

	//get delta time
	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x, y;
	Core::Input::GetMousePos(x,y);

	//Player
	player.Update(dt);

	//Enemy
	enemy.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 1,1,1 });
	graphics.DrawString(10, 10,std::to_string(frameTime).c_str());
	graphics.DrawString(10, 20,std::to_string(1.0f / frameTime).c_str());
	/*
	graphics.DrawString(10, 30,std::to_string(deltaTime / 1000.0f).c_str());

	float v = (std::sin(t) + 1.0f) * 0.5f;

	nc::Color c = nc::Lerp(nc::Color{ 1,0,0 }, nc::Color{ .5,.25,1 }, v);
	graphics.SetColor(c);
	nc::Vector2 p = nc::Lerp(nc::Vector2{ 100, 200 }, nc::Vector2{ 500,200 }, v);
	graphics.DrawString(p.x, p.y, "Here Comes The Grim Reaper");

	if (gameOver) graphics.DrawString(400, 300, "Game Over!");
	*/

	player.Draw(graphics);
	enemy.Draw(graphics);
}

int main()
{
	DWORD time = GetTickCount();
	std::cout << time / 1000 / 60 / 60 / 24 << std::endl;

	player.Load("Player.txt");
	enemy.Load("Enemy.txt");

	char name[] = "Yuki's Game";
	Core::Init(name, 800, 600, 90);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
};

