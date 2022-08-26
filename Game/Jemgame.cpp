#include "Jemgame.h"
#include "Engine.h"

void Jemgame::Initialize()
{
	m_scene = std::make_unique<jemgine::Scene>();

	rapidjson::Document document;
	std::vector<std::string> sceneNames = { "Scenes/Prefabs.txt", "Scenes/tilemap.txt", "Scenes/Level.txt" };

	for (auto sceneName : sceneNames)
	{
		bool success = jemgine::json::Load(sceneName, document);
		if (!success)
		{
			LOG("could not load scene %s", sceneName.c_str());
			continue;
		}
		m_scene->Read(document);
	}

	m_scene->Initialize();

	for (int i = 0; i < 10; i++)
	{
		auto actor = jemgine::Factory::Instance().Create<jemgine::Actor>("Coin");
		actor->m_transform.position = { jemgine::randomf(0, 800), 100.0f };
		actor->Initialize();
		m_scene->Add(std::move(actor));
	}
}

void Jemgame::Shutdown()
{
	m_scene->RemoveAll();
}

void Jemgame::Update()
{
	m_scene->Update();
}

void Jemgame::Draw(jemgine::Renderer& renderer)
{
	m_scene->Draw(renderer);
}
