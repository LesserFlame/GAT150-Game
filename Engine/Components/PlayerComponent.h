#pragma once
#include "Framework/Component.h"
namespace jemgine
{
	class PlayerComponent : public Component
	{
	public:
		PlayerComponent() = default;
		void Update() override;
	};
}