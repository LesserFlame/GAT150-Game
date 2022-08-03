#pragma once
#include "Core/Memory.h"
#include "Core/File.h"
#include "Core/Time.h"

#include "Math/MathUtils.h"
#include "Math/Random.h"

#include "Framework/Scene.h"
#include "Framework/Game.h"

#include "Input/InputSystem.h"

#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"

#include "Audio/AudioSystem.h"

#include <memory>

namespace jemgine
{
	extern Renderer g_renderer;
	extern InputSystem g_inputSystem;
	extern Time g_time;
	extern AudioSystem g_audioSystem;
}