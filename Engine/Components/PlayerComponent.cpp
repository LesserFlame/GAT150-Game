#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

namespace jemgine
{

}
void jemgine::PlayerComponent::Initialize()
{
	auto component = m_owner->GetComponent<CollisionComponent>();
	if (component)
	{
		component->SetCollisionEnter(std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1));
		component->SetCollisionExit(std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1));
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

	auto component = m_owner->GetComponent<PhysicsComponent>();
	if (component)
	{
		component->ApplyForce(direction * speed);
	}

	if (g_inputSystem.GetKeyState(key_space) == InputSystem::State::Press)
	{
		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			component->ApplyForce(Vector2::up * 500);
		}
	}
}


bool jemgine::PlayerComponent::Write(const rapidjson::Value& value) const
{
	return true;
}

bool jemgine::PlayerComponent::Read(const rapidjson::Value& value)
{
	READ_DATA(value, speed);
	return true;
}

void jemgine::PlayerComponent::OnCollisionEnter(Actor* other)
{
	std::cout << "player enter\n";
}

void jemgine::PlayerComponent::OnCollisionExit(Actor* other)
{
	std::cout << "player exit\n";
}
