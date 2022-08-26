#pragma once
#include "Framework/Game.h"

class Jemgame : public jemgine::Game
{
public:
	// Inherited via Game
	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update() override;
	virtual void Draw(jemgine::Renderer& renderer) override;
};