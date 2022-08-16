#pragma once
#include "Framework/Component.h"

namespace jemgine
{
	class Renderer;
	class RenderComponent : public Component
	{
	public:
		virtual void Draw(Renderer& renderer) = 0;
	};
}