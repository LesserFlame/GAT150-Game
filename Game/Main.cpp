#include "Engine.h"
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


	jemgine::g_renderer.CreateWindow("EV3RY  BUDDY  'S FAVORITE [[Number 1 Rated Salesman1997]]", 800, 600);
	jemgine::g_renderer.SetClearColor(jemgine::Color{ 10, 10, 10, 255 });
	std::cout << "HEY EVERY       !\nIT'S ME, SPAMTON G. SPAMTON!" << std::endl;

	std::shared_ptr<jemgine::Texture> texture = std::make_shared<jemgine::Texture>();
	texture->Create(jemgine::g_renderer, "Spamton.bmp");
	bool quit = false;
	while (!quit)
	{
		//update (engine)
		jemgine::g_inputSystem.Update();
		jemgine::g_time.Tick();
		jemgine::g_audioSystem.Update();


		if (jemgine::g_inputSystem.GetKeyDown(jemgine::key_escape)) quit = true;

		//update game objects


		//render
		jemgine::g_renderer.BeginFrame();

		jemgine::g_renderer.Draw(texture, { 200, 150 }, 0);

		jemgine::g_renderer.EndFrame();
	}
	jemgine::g_renderer.Shutdown();

	jemgine::g_audioSystem.Shutdown();
}