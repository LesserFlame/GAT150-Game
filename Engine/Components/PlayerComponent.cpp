#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

namespace jemgine
{

}
void jemgine::PlayerComponent::Initialize()
{
	CharacterComponent::Initialize();

	// bind events
	g_eventmanager.Subscribe("EVENT_PICKUP", std::bind(&CharacterComponent::OnNotify, this, std::placeholders::_1), m_owner);
	g_eventmanager.Subscribe("EVENT_HEALTH", std::bind(&CharacterComponent::OnNotify, this, std::placeholders::_1), m_owner);

	// bind collision events
	auto component = m_owner->GetComponent<CollisionComponent>();
	if (component)
	{
		component->SetCollisionEnter(std::bind(&CharacterComponent::OnCollisionEnter, this, std::placeholders::_1));
		component->SetCollisionExit(std::bind(&CharacterComponent::OnCollisionExit, this, std::placeholders::_1));
	}
}
void jemgine::PlayerComponent::Update()
{
	Vector2 direction = Vector2::zero;
	//update transform with input
	if (g_inputSystem.GetKeyState(key_a) == InputSystem::State::Held)
	{
		direction = Vector2::left;
	}
	if (g_inputSystem.GetKeyState(key_d) == InputSystem::State::Held)
	{
		direction = Vector2::right;
	}

	Vector2 velocity;
	auto component = m_owner->GetComponent<PhysicsComponent>();
	if (component)
	{
		component->ApplyForce(direction * speed);
		velocity = component->velocity;
	}

	if (g_inputSystem.GetKeyState(key_space) == InputSystem::State::Press)
	{
		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			component->ApplyForce(Vector2::up * 30);
		}
	}
	auto renderComponent = m_owner->GetComponent<RenderComponent>();
	if (renderComponent)
	{
		if (velocity.x != 0) renderComponent->SetFlipHorizontal(velocity.x < 0);
	}
}


bool jemgine::PlayerComponent::Write(const rapidjson::Value& value) const
{
	return true;
}

bool jemgine::PlayerComponent::Read(const rapidjson::Value& value)
{
	CharacterComponent::Read(value);
	READ_DATA(value, jump);
	return true;
}

void jemgine::PlayerComponent::OnNotify(const Event& event)
{
	if (event.name == "EVENT_DAMAGE")
	{
		health -= std::get<float>(event.data);
		std::cout << health << std::endl;
		if (health <= 0)
		{
			m_owner->SetDestroy();

			Event event;
			event.name = "EVENT_PLAYER_DEAD";

			g_eventmanager.Notify(event);
		}
	}
	if (event.name == "EVENT_HEALTH")
	{
		health += std::get<float>(event.data);
		if (health > 3)
		{
			health = 3;
		}
	}
}


void jemgine::PlayerComponent::OnCollisionEnter(Actor* other)
{
	if (other->GetName() == "Coin")
	{
		Event event;
		event.name = "EVENT_ADD_POINTS";
		event.data = 100;

		g_eventmanager.Notify(event);
		other->SetDestroy();
	}

	if (other->GetTag() == "Enemy")
	{
		Event event;
		event.name = "EVENT_DAMAGE";
		event.data = damage;
		event.receiver = other;

		g_eventmanager.Notify(event);
		other->SetDestroy();
	}
	//std::cout << "player enter\n";
}

void jemgine::PlayerComponent::OnCollisionExit(Actor* other)
{
	//std::cout << "player exit\n";
}
