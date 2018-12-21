#include "Sound.h"
#include "Audio.h"
#include "../Shared/Engine.h"


Sound::Sound(const std::string& fileName) : m_pFMOD_sound2(nullptr), m_pFMOD_channel2(nullptr)
{
	Audio::g_pFMOD_system2->createSound(fileName.c_str(), FMOD_DEFAULT, 0, &m_pFMOD_sound2);
	return;

	try
	{
		if (FMOD_System_CreateSound(
				Audio::g_pFMOD_system,	// FMOD system
				fileName.c_str(),		// file name
				FMOD_DEFAULT,			// default audio
				nullptr,				// n/a
				&m_pFMOD_sound			// pointer to sample
			) == FMOD_OK)
		{
			return;
		}
	}
	catch (...)
	{
	}

	m_pFMOD_sound = nullptr;
}


Sound::~Sound()
{
	if (m_pFMOD_sound2 != nullptr)
	{
		m_pFMOD_sound2->release();
	}
	return;

	if (m_pFMOD_sound != nullptr)
	{
		FMOD_Sound_Release(m_pFMOD_sound);
	}
}


bool Sound::IsPlaying() const
{
	bool isPlaying = false;
	m_pFMOD_channel2->isPlaying(&isPlaying);
	return isPlaying;

	int index;
	FMOD_Channel_GetIndex(m_pFMOD_channel, &index);
	return index > 0;
}


bool Sound::Play(int nLoopCount)
{
	return (Audio::g_pFMOD_system2->playSound(m_pFMOD_sound2, 0, false, &m_pFMOD_channel2) == FMOD_OK);


	if (m_pFMOD_sound != nullptr)
	{
		try
		{
			if (FMOD_System_PlaySound(
					Audio::g_pFMOD_system,
					m_pFMOD_sound,
					nullptr,//FMOD_CHANNEL_FREE, 
					true, 
					&m_pFMOD_channel
				) == FMOD_OK)
			{
				FMOD_Channel_SetMode(m_pFMOD_channel, FMOD_DEFAULT | ((nLoopCount == -1) ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF));
				FMOD_Channel_SetLoopCount(m_pFMOD_channel, nLoopCount);
				FMOD_Channel_SetPaused(m_pFMOD_channel, false);

				return true;
			}
		}
		catch (...)
		{
		}
	}

	return false;
}


void Sound::Stop()
{
	m_pFMOD_channel2->stop();
	return;

	FMOD_Channel_Stop(m_pFMOD_channel);
}


void Sound::Pause()
{
	m_pFMOD_channel2->setPaused(true);
	return;

	FMOD_Channel_SetPaused(m_pFMOD_channel, 1);
}


void Sound::Resume()
{
	m_pFMOD_channel2->setPaused(false);
	return;

	FMOD_Channel_SetPaused(m_pFMOD_channel, 0);
}
