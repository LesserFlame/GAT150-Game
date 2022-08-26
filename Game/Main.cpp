#include "Engine.h"
#include "Jemgame.h"
#include <iostream>

int main()
{
	jemgine::InitializeMemory();
	jemgine::SetFilePath("../Assets");



	//initialize jemgine engine
	//renderer.Initialize();
	jemgine::g_inputSystem.Initialize();
	jemgine::g_renderer.Initialize();
	jemgine::g_audioSystem.Initialize();
	jemgine::g_resources.Initialize();
	jemgine::g_physicsSystem.Initialize();

	jemgine::Engine::Instance().Register();

	jemgine::g_renderer.CreateWindow("EV3RY  BUDDY  'S FAVORITE [[Number 1 Rated Salesman1997]]", 800, 600);
	jemgine::g_renderer.SetClearColor(jemgine::Color{ 10, 10, 10, 255 });
	std::cout << "HEY EVERY       !\nIT'S ME, SPAMTON G. SPAMTON!" << std::endl;

	//create scene
	std::unique_ptr<Jemgame> game = std::make_unique<Jemgame>();
	game->Initialize();
	


	bool quit = false;
	while (!quit)
	{
		//update (engine)
		jemgine::g_time.Tick();
		jemgine::g_inputSystem.Update();
		jemgine::g_audioSystem.Update();
		jemgine::g_physicsSystem.Update();

		if (jemgine::g_inputSystem.GetKeyDown(jemgine::key_escape)) quit = true;

		//update game objects

		game->Update();

		//render
		jemgine::g_renderer.BeginFrame();

		game->Draw(jemgine::g_renderer);
		//jemgine::g_renderer.Draw(texture, { 200, 150 }, angle, { 1, 1 }, {0.5f, 1.0f});

		jemgine::g_renderer.EndFrame();
	}

	game->Shutdown();
	game.reset();

	jemgine::Factory::Instance().Shutdown();

	jemgine::g_physicsSystem.Shutdown();
	jemgine::g_resources.Shutdown();
	jemgine::g_inputSystem.Shutdown();
	jemgine::g_audioSystem.Shutdown();
	jemgine::g_renderer.Shutdown();

}