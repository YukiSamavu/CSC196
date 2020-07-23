#include "core.h"
#include "Game.h"
#include <time.h>

Game game;

bool Update(float dt)
{
	bool quit = game.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{	
	game.Draw(graphics);
}

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	game.Initialize();

	char name[] = "Yuki's Game";
	Core::Init(name, 800, 600, 90);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();

	// shutdown engine
	//g_particlesSystem.Shutdown();
	//scene.Shutdown();
};

