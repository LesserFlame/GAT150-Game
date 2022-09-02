#pragma once
#include "Framework/Component.h"
#include "Physics/Collision.h"
#include "CharacterComponent.h"

namespace jemgine
{
	class PlayerComponent : public CharacterComponent
	{
	public:
		PlayerComponent() = default;
		CLASS_DECLARATION(PlayerComponent)

		void Update() override;

		void Initialize() override;

		virtual void OnNotify(const Event& event) override;
		virtual void OnCollisionEnter(Actor* other) override;
		virtual void OnCollisionExit(Actor* other) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void SetAttack(bool attack = true) { isAttacking = attack; }

	public:
		bool facingLeft = false;

		bool isAttacking = false;
		float attackCooldown = 0.0f;

		bool isHit = false;
		float damageCooldown = 0.0f;

		int m_groundCount = 0;
		bool doubleJump = true;

		float jump = 250.0f;

		// Inherited via CharacterComponent
	};
}