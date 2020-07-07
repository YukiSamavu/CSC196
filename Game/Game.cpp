// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "core.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include <iostream>
#include <string>

std::vector<nc::Vector2> points = { { -2, 3 }, { -3, 2 }, { -3, 1 }, { -1, -3 }, {1, -3 }, {3, 1}, {3,2}, {2,3}, {-2,3} };
nc::Color color{ 1,0,0 };

nc::Vector2 position{ 400.0f, 300.0f };
float scale = 5.0f;
float angle = 0.0f;

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
	
	if (gameOver) dt = 0;
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
	direction = nc::Vector2::Rotate(direction, angle);

	position = position + direction;

	if (position.x > 800.0f) { position.x = 0; }
	if (position.x < 0.0f) { position.x = 800; }
	if (position.y > 600.0f) { position.y = 0; }
	if (position.y < 0.0f) { position.y = 600; }

	if (Core::Input::IsPressed('A')) position += nc::Vector2::left * speed;
	if (Core::Input::IsPressed('D')) position += nc::Vector2::right * speed;
	if (Core::Input::IsPressed('S')) position += nc::Vector2::down * speed;
	if (Core::Input::IsPressed('W')) position += nc::Vector2::up * speed;

	//if (Core::Input::IsPressed('A')) angle -= dt * 2.0f;
	//if (Core::Input::IsPressed('D')) angle += dt * 2.0f;

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10,std::to_string(frameTime).c_str());
	graphics.DrawString(10, 20,std::to_string(1.0f / frameTime).c_str());
	graphics.DrawString(10, 30,std::to_string(deltaTime / 1000.0f).c_str());

	if (gameOver) graphics.DrawString(400, 300, "Game Over!");
	graphics.SetColor(color.pack888());

	for (size_t i = 0; i < points.size() - 1; i++)
	{

		// local/object space points
		nc::Vector2 p1 = (points[i]);
		nc::Vector2 p2 = (points[i + 1]);

		//transform
		//scale
		p1 = p1 * 5.0f;
		p2 = p2 * 5.0f;
		//rotate
		p1 = nc::Vector2::Rotate(p1, 0.0f);
		p2 = nc::Vector2::Rotate(p2, 0.0f);
		//translate
		p1 = p1 + position;
		p2 = p2 + position;

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}

}

int main()
{
	DWORD time = GetTickCount();
	std::cout << time / 1000 / 60 / 60 / 24 << std::endl;

	char name[] = "Yuki's Game";
	Core::Init(name, 800, 600, 90);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
};

