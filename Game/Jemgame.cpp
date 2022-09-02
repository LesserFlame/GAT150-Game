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

	jemgine::g_audioSystem.AddAudio("sword", "audio/sword.wav");
	jemgine::g_audioSystem.AddAudio("coin", "audio/coin.wav");
	jemgine::g_audioSystem.AddAudio("hit", "audio/hit.wav");
	jemgine::g_audioSystem.AddAudio("damage", "audio/damage.wav");
	jemgine::g_audioSystem.AddAudio("jump", "audio/jump.wav");
	jemgine::g_audioSystem.AddAudio("doublejump", "audio/doublejump.wav");


	jemgine::g_eventmanager.Subscribe("EVENT_ADD_POINTS", std::bind(&Jemgame::OnAddPoints, this, std::placeholders::_1));
	//jemgine::g_eventmanager.Subscribe("EVENT_ATTACK", std::bind(&Jemgame::OnPlayerAttack, this, std::placeholders::_1));

	for (int i = 0; i < 1; i++)
	{
		auto actor = jemgine::Factory::Instance().Create<jemgine::Actor>("Stone");
		actor->m_transform.position = { jemgine::randomf(400, 300), 100.0f };
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
	{
		m_stateTimer = 3.0f;
		auto actor = jemgine::Factory::Instance().Create<jemgine::Actor>("Player");
		actor->m_transform.position = { jemgine::randomf(100, 700), jemgine::randomf( 400, 500) };
		actor->Initialize();
		m_scene->Add(std::move(actor));
	}
		m_gameState = Jemgame::gameState::game;
		break;
	case Jemgame::gameState::game:
	{
		m_gameTimer += jemgine::g_time.deltaTime;
		m_score += jemgine::g_time.deltaTime;
		m_flySpawner -= jemgine::g_time.deltaTime;
		if (m_flySpawner <= 0)
		{
			for (int i = 0; i < ((int)m_gameTimer / 20); i++)
			{
				auto actor = jemgine::Factory::Instance().Create<jemgine::Actor>("Fly");
				actor->m_transform.position = { jemgine::randomf(0, 800), jemgine::randomf(0, 600) };
				actor->GetComponent<jemgine::CharacterComponent>()->health = (((int)m_gameTimer / 60) + 1);
				actor->Initialize();
				m_scene->Add(std::move(actor));
				m_flySpawner = jemgine::randomf(7, 10);
			}

			for (int i = 0; i < jemgine::randomf(0, 2); i++)
			{
				auto actor = jemgine::Factory::Instance().Create<jemgine::Actor>("Coin");
				actor->m_transform.position = { jemgine::randomf(100, 700), jemgine::randomf(0, 100) };
				actor->Initialize();
				m_scene->Add(std::move(actor));
				m_flySpawner = jemgine::randomf(7, 10);
			}
		}

		auto actor = m_scene->GetActorFromName("Score");
		auto component = actor->GetComponent<jemgine::TextComponent>();
		component->SetText(std::to_string((int)m_score));
	}
	{
		auto actor = m_scene->GetActorFromName("Health");
		auto component = actor->GetComponent<jemgine::TextComponent>();
		
		auto player = m_scene->GetActorFromName("Player");
		if (player)
		{
			m_playerX = player->m_transform.position.x;
			m_playerY = player->m_transform.position.y;
			auto playerComponent = player->GetComponent<jemgine::PlayerComponent>();
			component->SetText(std::to_string((int)playerComponent->health));
		}
		if (!player)
		{
			auto actor = jemgine::Factory::Instance().Create<jemgine::Actor>("PlayerDead");
			actor->m_transform.position = { m_playerX, m_playerY };
			actor->Initialize();
			m_scene->Add(std::move(actor));
			m_lives--;
			m_gameState = gameState::playerDead;
		}
	}
	{
		auto actor = m_scene->GetActorFromName("Lives");
		auto component = actor->GetComponent<jemgine::TextComponent>();
		component->SetText(std::to_string((int)m_lives));
	}
	if (jemgine::g_inputSystem.GetKeyState(jemgine::key_e) == jemgine::InputSystem::State::Press)
	{
		OnPlayerAttack();
	}
	
		break;
	case Jemgame::gameState::playerDead:
		m_stateTimer -= jemgine::g_time.deltaTime;
		if (m_stateTimer <= 0)
		{
			m_gameState = (m_lives > 0) ? gameState::startLevel : gameState::gameOver;
			m_score -= 300;
			if (m_score <= 0) m_score = 0;
		}
		break;
	case Jemgame::gameState::gameOver:
		m_scene->GetActorFromName("GameOver")->SetActive(true);
		if (jemgine::g_inputSystem.GetKeyState(jemgine::key_space) == jemgine::InputSystem::State::Press)
		{
			m_scene->GetActorFromName("GameOver")->SetActive(false);
			m_score = 0;
			m_lives = 3;
			m_gameTimer = 0;
			m_gameState = gameState::titleScreen;
		}
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
}

void Jemgame::OnPlayerAttack()
{
	auto player = m_scene->GetActorFromName("Player");
	if (player)
	{
		if (player->GetComponent<jemgine::PlayerComponent>()->doubleJump == false) return;
		if (player->GetComponent<jemgine::PlayerComponent>()->isAttacking == true) return;
		float attackY = player->m_transform.position.y;
		float attackX = player->m_transform.position.x + 30;
		auto actor = jemgine::Factory::Instance().Create<jemgine::Actor>("Attack");

		if (player->GetComponent<jemgine::PlayerComponent>()->facingLeft)
		{
			actor->m_transform.rotation = 180;
			attackX -= 60;
			attackY += 9;
		}
		jemgine::g_audioSystem.PlayAudio("sword");
		player->GetComponent<jemgine::PlayerComponent>()->isAttacking = true;
		player->GetComponent<jemgine::PlayerComponent>()->attackCooldown = 0.33f;
		actor->m_transform.position = { attackX, attackY };
		actor->Initialize();
		m_scene->Add(std::move(actor));
	}
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
