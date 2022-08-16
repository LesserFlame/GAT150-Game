#pragma once
#include "Framework/Component.h"
namespace jemgine
{
	class AudioComponent : public Component
	{
	public:
		AudioComponent() = default;
		void Update() override;
		void Play();
		void Stop();


		std::string m_soundName;
		bool m_playOnAwake = false;
		float m_volume = 1.0f;
		float m_pitch = 1.0f;
		bool m_loop = false;
	};
}