#pragma once
#include "Framework/Game.h"
#include "Framework/Event.h"

class Jemgame : public jemgine::Game, public jemgine::INotify
{
public:
	enum class gameState
	{
		titleScreen,
		startLevel,
		game,
		playerDead,
		gameOver
	};
public:
	// Inherited via Game
	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update() override;
	virtual void Draw(jemgine::Renderer& renderer) override;
	
	void OnAddPoints(const jemgine::Event& event);
	void OnPlayerDead(const jemgine::Event& event);
private:
	gameState m_gameState = gameState::titleScreen;
	float m_stateTimer = 0;
	int m_lives = 3;

	// Inherited via INotify
	virtual void OnNotify(const jemgine::Event& event) override;
};