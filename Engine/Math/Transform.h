#pragma once
#include "Vector2.h"

namespace jemgine
{
	struct Transform
	{
		Vector2 position;
		float rotation = 0.0f;
		float scale = 1.0f;
	};
}