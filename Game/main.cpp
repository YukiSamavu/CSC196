#include "core.h"
#include "Game.h"
#include <time.h>
#include "Graphics/PartilcesSystem.h"
#include "Audio/AudioSystem.h"

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
	g_particlesSystem.Startup();
	g_audioSystem.Startup();

	srand(static_cast<unsigned int>(time(NULL)));
	game.Initialize();

	char name[] = "Yuki's Game";
	Core::Init(name, 800, 600, 90);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();

	// shutdown engine
	g_audioSystem.Shutdown();
	g_particlesSystem.Shutdown();
	//scene.Shutdown();
};

