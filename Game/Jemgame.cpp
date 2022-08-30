#include "Jemgame.h"
#include "Engine.h"
#include "GameComponents/EnemyComponent.h"


void Jemgame::Initialize()
{
	REGISTER_CLASS(EnemyComponent);
	m_scene = std::make_unique<jemgine::Scene>();

	rapidjson::Document document;
	std::vector<std::string> sceneNames = { "Scenes/Prefabs.txt", "Scenes/Tilemap.txt", "Scenes/Level.txt" };

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

	

	jemgine::g_eventmanager.Subscribe("EVENT_ADD_POINTS", std::bind(&Jemgame::OnAddPoints, this, std::placeholders::_1));
}

void Jemgame::Shutdown()
{
	m_scene->RemoveAll();
}

void Jemgame::Update()
{
	switch (m_gameState)
	{
	case Jemgame::gameState::titleScreen:
		if (jemgine::g_inputSystem.GetKeyState(jemgine::key_space) == jemgine::InputSystem::State::Press)
		{
			m_scene->GetActorFromName("Title")->SetActive(false);
			m_gameState = gameState::startLevel;
		}
		break;
	case Jemgame::gameState::startLevel:
		for (int i = 0; i < 10; i++)
		{
			auto actor = jemgine::Factory::Instance().Create<jemgine::Actor>("Coin");
			actor->m_transform.position = { jemgine::randomf(0, 800), 100.0f };
			actor->Initialize();
			m_scene->Add(std::move(actor));
		}
		for (int i = 0; i < 3; i++)
		{
			auto actor = jemgine::Factory::Instance().Create<jemgine::Actor>("Fly");
			actor->m_transform.position = { jemgine::randomf(0, 300), jemgine::randomf(0, 400) };
			actor->Initialize();
			m_scene->Add(std::move(actor));
		}
		for (int i = 0; i < 20; i++)
		{
			auto actor = jemgine::Factory::Instance().Create<jemgine::Actor>("Stone");
			actor->m_transform.position = { jemgine::randomf(0, 800), 100.0f };
			actor->Initialize();
			m_scene->Add(std::move(actor));
		}
		m_gameState = Jemgame::gameState::game;
		break;
	case Jemgame::gameState::game:
		
		break;
	case Jemgame::gameState::playerDead:
		m_stateTimer -= jemgine::g_time.deltaTime;
		if (m_stateTimer <= 0)
		{
			m_gameState = (m_lives > 0) ? gameState::startLevel : gameState::gameOver;
		}
		break;
	case Jemgame::gameState::gameOver:
	break;
	}
	m_scene->Update();

}

void Jemgame::Draw(jemgine::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void Jemgame::OnAddPoints(const jemgine::Event& event)
{
	AddPoints(std::get<int>(event.data));

	std::cout << event.name << std::endl;
	std::cout << std::get<int>(event.data) << std::endl;
}

void Jemgame::OnPlayerDead(const jemgine::Event& event)
{
	m_gameState = gameState::playerDead;
	m_stateTimer = 3.0f;
}

void Jemgame::OnNotify(const jemgine::Event& event)
{
	m_gameState = gameState::playerDead;
	m_lives--;
	m_stateTimer = 3.0f;
}
