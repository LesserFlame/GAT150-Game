#include "AudioComponent.h"
#include "Engine.h"
namespace jemgine {
	void AudioComponent::Update()
	{
	}
	void AudioComponent::Play()
	{
		g_audioSystem.PlayAudio(m_soundName, m_loop);
	}
	void AudioComponent::Stop()
	{
	}
}
