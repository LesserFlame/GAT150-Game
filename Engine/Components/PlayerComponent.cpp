#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

namespace jemgine
{

void PlayerComponent::Initialize()
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
void PlayerComponent::Update()
{
	attackCooldown -= g_time.deltaTime;
	if (attackCooldown <= 0)
	{
		attackCooldown = 0;
		isAttacking = false;
	}
	damageCooldown -= g_time.deltaTime;
	if (damageCooldown <= 0)
	{
		damageCooldown = 0;
		isHit = false;
	}
	Vector2 direction = Vector2::zero;
	//update transform with input
	if (g_inputSystem.GetKeyState(key_a) == InputSystem::State::Held)
	{
		facingLeft = true;
		direction = Vector2::left;
	}
	if (g_inputSystem.GetKeyState(key_d) == InputSystem::State::Held)
	{
		facingLeft = false;
		direction = Vector2::right;
	}

	Vector2 velocity;
	auto component = m_owner->GetComponent<PhysicsComponent>();
	if (component)
	{
		// if in the air (m_groundCount == 0) then reduce force 
		float multiplier = (m_groundCount > 0) ? 1 : 0.5f;

		component->ApplyForce(direction * speed * multiplier);
		velocity = component->velocity;
	}

	if ((m_groundCount > 0 || doubleJump) && g_inputSystem.GetKeyState(key_space) == InputSystem::State::Press)
	{
		if (m_groundCount) g_audioSystem.PlayAudio("jump");
		if (m_groundCount <= 0)
		{
			g_audioSystem.PlayAudio("doublejump");
			doubleJump = false;
		}
		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			component->ApplyForce(Vector2::up * jump);
		}
	}
	
	auto animComponent = m_owner->GetComponent<SpriteAnimComponent>();
	if (animComponent)
	{
		if (velocity.x != 0) animComponent->SetFlipHorizontal(facingLeft);
		if (std::fabs(velocity.x) > 0 && m_groundCount >= 1)
		{
			animComponent->SetSequence("run");
		}
		else
		{
			animComponent->SetSequence("idle");
		}
		if (m_groundCount <= 0 && doubleJump)
		{
			animComponent->SetSequence("jump");
		}
		if (!doubleJump)
		{
			animComponent->SetSequence("doublejump");
		}
		if (isAttacking)
		{
			animComponent->SetSequence("attack");
		}
		if (isHit)
		{
			animComponent->SetSequence("hit");
		}
	}

	// set camera 
	auto camera = m_owner->GetScene()->GetActorFromName("Camera");
	if (camera)
	{
		camera->m_transform.position = jemgine::Lerp(camera -> m_transform.position, m_owner->m_transform.position, 2 * g_time.deltaTime);
	}
}


bool PlayerComponent::Write(const rapidjson::Value& value) const
{
	return true;
}

bool PlayerComponent::Read(const rapidjson::Value& value)
{
	CharacterComponent::Read(value);
	READ_DATA(value, jump);
	return true;
}

void PlayerComponent::OnNotify(const Event& event)
{
	if (event.name == "EVENT_DAMAGE")
	{
		if (isHit) return;
		health -= std::get<float>(event.data);
		
		isHit = true;
		damageCooldown = 0.1f;
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
	/*if (event.name == "EVENT_ATTACK")
	{
		isAttacking = true;
	}*/
}


void PlayerComponent::OnCollisionEnter(Actor* other)
{
	if (other->GetName() == "Coin")
	{
		Event event;
		event.name = "EVENT_ADD_POINTS";
		event.data = 100;
		g_audioSystem.PlayAudio("coin");
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
	if (other->GetTag() == "Ground")
	{
		m_groundCount++;
		doubleJump = true;
	}
}

void PlayerComponent::OnCollisionExit(Actor* other)
{
	if (other->GetTag() == "Ground")
	{
		m_groundCount--;
	}
}
}
