// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "core.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Random.h"
#include <iostream>

bool Update(float dt)
{
	return false;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(RGB(rand() % 256, rand() % 256, rand() % 256));
	graphics.DrawLine(nc::random(0.0f, 800.0f), nc::random(0.0f, 600.0f), nc::random(0.0f, 800.0f), nc::random(0.0f, 600.0f));
}

int main()
{

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}

