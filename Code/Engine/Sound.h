#ifndef __SOUND_H
#define __SOUND_H

#pragma once

#define _USING_V110_SDK71_ 1

#include <cstdlib>
#include "fmod.hpp"

// This is not exposed to Game


namespace Audio
{
	extern FMOD_SYSTEM* pFMOD_system;

	bool Init();
	void ShutDown();

	void Update();

}	// namespace Audio


class Sound
{
public:
	Sound(const char* szFileName);
	~Sound();

	bool IsOK() const { return m_pFMOD_sound != NULL; }

	bool IsPlaying() const;
	bool Play(int nLoopCount);
	void Stop();

	void Pause();
	void Resume();

private:
	FMOD_SOUND*		m_pFMOD_sound;
	FMOD_CHANNEL*	m_pFMOD_channel;
};


#endif	// #ifndef __SOUND_H
