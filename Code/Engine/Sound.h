#pragma once

#define _USING_V110_SDK71_ 1
#include <string>
#include "fmod.hpp"


class Sound
{
public:
	Sound(const std::string& fileName);
	~Sound();

	bool IsOK() const { return m_pSound != nullptr; }

	bool IsPlaying() const;
	bool Play();
	bool PlayLooped();
	void Stop() { m_pChannel->stop(); }

	void Pause() { m_pChannel->setPaused(true); }
	void Resume() { m_pChannel->setPaused(false); }

private:
	FMOD::Sound*	m_pSound;
	FMOD::Channel*	m_pChannel;
};
