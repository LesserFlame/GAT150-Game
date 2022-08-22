#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>
void jemgine::PlayerComponent::Update()
{
	Vector2 direction = Vector2::zero;
	//update transform with input
	if (g_inputSystem.GetKeyState(key_a) == InputSystem::State::Held)
	{
		m_owner->m_transform.rotation -= 180 * g_time.deltaTime;
		//direction = Vector2::left;
	}
	if (g_inputSystem.GetKeyState(key_d) == InputSystem::State::Held)
	{
		m_owner->m_transform.rotation += 180 * g_time.deltaTime;
		//direction = Vector2::right;
	}
	float  thrust = 0;
	if (g_inputSystem.GetKeyState(key_w) == InputSystem::State::Held)
	{
		thrust = speed;
	}
	//std::cout << m_owner->m_transform.position.x <<  " " << m_owner->m_transform.position.y << std::endl;
	auto component = m_owner->GetComponent<PhysicsComponent>();
	if (component)
	{
		Vector2 force = Vector2::Rotate({ 1, 0 }, jemgine::DegToRad(m_owner->m_transform.rotation)) * thrust;
		component->ApplyForce(force);

		//gravitational force
		//force = (Vector2{ 400, 300 } - m_owner->m_transform.position).Normalized() * 60.0f;
		//component->ApplyForce(force);
	}

	/*if (g_inputSystem.GetKeyState(key_w) == InputSystem::State::Held)
	{
		direction = Vector2::up;
	}
	if (g_inputSystem.GetKeyState(key_s) == InputSystem::State::Held)
	{
		direction = Vector2::down;
	}*/

	m_owner->m_transform.position += direction * 300 * g_time.deltaTime;

	if (g_inputSystem.GetKeyState(key_space) == InputSystem::State::Press)
	{
		auto component = m_owner->GetComponent<AudioComponent>();
		if (component)
		{
			component->Play();
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
