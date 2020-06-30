// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "core.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Random.h"
#include <iostream>

const size_t NUM_POINTS = 40;
std::vector<nc::Vector2> points;

bool Update(float dt)
{
	for (size_t i = 0; i < NUM_POINTS; i++)
	{
		points[i] = nc::Vector2{ nc::random(0.0f, 800.0f), nc::random(0.0f, 600.0f) };
	}

	return false;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(RGB(rand() % 256, rand() % 256, rand() % 256));
	graphics.DrawLine(nc::random(0.0f, 800.0f), nc::random(0.0f, 600.0f), nc::random(0.0f, 800.0f), nc::random(0.0f, 600.0f));

	for (size_t i = 0; i < NUM_POINTS - 1; i++)
	{
		nc::Vector2 p1 = points[i];
		nc::Vector2 p2 = points[i + 1];

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

int main()
{
	for (size_t i = 0; i < NUM_POINTS; i++)
	{
		points.push_back(nc::Vector2{ nc::random(0.0f, 800.0f), nc::random(0.0f, 600.0f) });
	}

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
};

