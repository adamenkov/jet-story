#pragma once

#define _USING_V110_SDK71_ 1
#include <string>
#include "fmod.hpp"


class Sound final
{
public:
	Sound(const std::string& fileName);
	~Sound();

	bool IsOK() const { return m_pFMOD_sound != nullptr; }

	bool IsPlaying() const;
	bool Play(int nLoopCount);
	void Stop();

	void Pause();
	void Resume();

private:
	FMOD_SOUND*		m_pFMOD_sound;
	FMOD_CHANNEL*	m_pFMOD_channel;
};
