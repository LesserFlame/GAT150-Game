#include "EnemyComponent.h"
#include "Engine.h"
#include <iostream>

void EnemyComponent::Initialize()
{
    CharacterComponent::Initialize();
}

void EnemyComponent::Update()
{
    auto actor = m_owner->GetScene()->GetActorFromName("Player");
    if (actor)
    {
        jemgine::Vector2 direction = actor->m_transform.position - m_owner->m_transform.position;
        jemgine::Vector2 force = direction.Normalized() * speed;

        auto component = m_owner->GetComponent<jemgine::PhysicsComponent>();
        if (component) component->ApplyForce(force);
    }
}

void EnemyComponent::OnCollisionEnter(jemgine::Actor* other)
{
    if (other->GetTag() == "Player")
    {
        jemgine::Event event;
        event.name = "EVENT_DAMAGE";
        event.data = damage;
        event.receiver = other;
        jemgine::g_eventmanager.Notify(event);
    }
}

void EnemyComponent::OnCollisionExit(jemgine::Actor* other)
{
}

void EnemyComponent::OnNotify(const jemgine::Event& event)
{
    if (event.name == "EVENT_DAMAGE")
    {
        health -= std::get<float>(event.data);
        if (health <= 0)
        {
            m_owner->SetDestroy();
        }
    }

}

bool EnemyComponent::Write(const rapidjson::Value& value) const
{
    return true;
}

bool EnemyComponent::Read(const rapidjson::Value& value)
{
    CharacterComponent::Read(value);

    return true;
}