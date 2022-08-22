#pragma once

#include "Actor.h"
#include "../Engine.h"

#include <list>
#include <memory>

namespace jemgine
{
	//foward declaration
	class Actor;
	class Renderer;
	class Game;

	class Scene : public ISerializable
	{
	public:
		Scene() = default;
		Scene(Game* game) : m_game{ game } {}
		~Scene() = default;

		void Update();
		void Draw(Renderer& renderer);
		
		// Inherited via ISerializable
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Add(std::unique_ptr<Actor> actor);

		template<typename T>
		T* GetActor();

		Game* GetGame() { return m_game; }
	private:
		Game* m_game;
		std::list<std::unique_ptr<Actor>> m_actors;

	};
	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;
		}

		return nullptr;
	}
}