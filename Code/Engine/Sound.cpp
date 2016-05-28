#include "Sound.h"
#include "../Shared/Engine.h"


Sound::Sound(const std::string& fileName)
{
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
	if (m_pFMOD_sound != nullptr)
	{
		FMOD_Sound_Release(m_pFMOD_sound);
	}
}


bool Sound::IsPlaying() const
{
	int index;
	FMOD_Channel_GetIndex(m_pFMOD_channel, &index);
	return index > 0;
}


bool Sound::Play(int nLoopCount)
{
	if (m_pFMOD_sound != nullptr)
	{
		try
		{
			if (FMOD_System_PlaySound(
					Audio::g_pFMOD_system,
					FMOD_CHANNEL_FREE, 
					m_pFMOD_sound, 
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
	FMOD_Channel_Stop(m_pFMOD_channel);
}


void Sound::Pause()
{
	FMOD_Channel_SetPaused(m_pFMOD_channel, 1);
}


void Sound::Resume()
{
	FMOD_Channel_SetPaused(m_pFMOD_channel, 0);
}
