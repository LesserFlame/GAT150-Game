#pragma once 

namespace FMOD
{
	class Channel;
}

namespace jemgine
{
	class AudioChannel
	{
	public:
		AudioChannel() = default;
		AudioChannel(FMOD::Channel* channel) : m_channel{ channel } {} // !! set m_channel 
		bool IsPlaying();
		void Stop();

		void SetPitch(float pitch);
		float GetPitch();

		void SetVolume(float volume);
		float GetVolume();

	private:
		FMOD::Channel* m_channel{ nullptr };
	};
}