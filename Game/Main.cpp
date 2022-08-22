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
	jemgine::g_resources.Initialize();
	jemgine::g_physicsSystem.Initialize();

	jemgine::Engine::Instance().Register();

	jemgine::g_renderer.CreateWindow("EV3RY  BUDDY  'S FAVORITE [[Number 1 Rated Salesman1997]]", 800, 600);
	jemgine::g_renderer.SetClearColor(jemgine::Color{ 10, 10, 10, 255 });
	std::cout << "HEY EVERY       !\nIT'S ME, SPAMTON G. SPAMTON!" << std::endl;

	//create scene
	jemgine::Scene scene;

	rapidjson::Document document;
	bool success = jemgine::json::Load("level.txt", document);

	scene.Read(document);

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

		scene.Update();

		//render
		jemgine::g_renderer.BeginFrame();

		scene.Draw(jemgine::g_renderer);
		//jemgine::g_renderer.Draw(texture, { 200, 150 }, angle, { 1, 1 }, {0.5f, 1.0f});

		jemgine::g_renderer.EndFrame();
	}
	jemgine::g_renderer.Shutdown();

	jemgine::g_audioSystem.Shutdown();
}