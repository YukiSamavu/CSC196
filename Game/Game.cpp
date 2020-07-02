// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "core.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include <iostream>

std::vector<nc::Vector2> points = { { 0, -3 }, { 3, 3 }, { 0, 1 }, { -3, 3 }, { 0, -3 } };
nc::Color color{ 1,1,0 };

nc::Vector2 position{ 400.0f, 300.0f };
float scale = 5.0f;
float angle = 0.0f;

float speed = 5.0f;

bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	//color.r = nc::random(0.0f, 1.0f);
	//color.g = nc::random(0.0f, 1.0f);
	//color.b = nc::random(0.0f, 1.0f);

	int x, y;
	Core::Input::GetMousePos(x,y);

	nc::Vector2 target = nc::Vector2{ x, y };
	nc::Vector2 direction = target - position;// head - tail <-

	direction.Normalize();

	//if (direction.Length() < 200.0f)
	{
		//position = position + (direction * speed);
	}

	//if (Core::Input::IsPressed('A')) position += nc::Vector2{ -1.0f,0.0f } * speed;
	//if (Core::Input::IsPressed('D')) position += nc::Vector2{ 1.0f,0.0f } * speed;
	//if (Core::Input::IsPressed('S')) position += nc::Vector2{ 0.0f,1.0f } * speed;
	//if (Core::Input::IsPressed('W')) position += nc::Vector2{ 0.0f,-1.0f } * speed;

	if (Core::Input::IsPressed('A')) angle -= dt * 2.0f;
	if (Core::Input::IsPressed('D')) angle += dt * 2.0f;

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(color.pack888());

	for (size_t i = 0; i < points.size() - 1; i++)
	{
		// local/object space points
		nc::Vector2 p1 = (points[i]);
		nc::Vector2 p2 = (points[i + 1]);

		//transform
		//scale
		p1 = p1 * scale;
		p2 = p2 * scale;
		//rotate
		p1 = nc::Vector2::Rotate(p1, angle);
		p2 = nc::Vector2::Rotate(p2, angle);
		//translate
		p1 = p1 + position;
		p2 = p2 + position;

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

int main()
{
	char name[] = "Yuki's Game";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
};

