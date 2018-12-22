#include "Sound.h"
#include "Audio.h"
#include "../Shared/Engine.h"


Sound::Sound(const std::string& fileName) : m_pSound(nullptr), m_pChannel(nullptr)
{
	Audio::g_pFMOD_system->createSound(fileName.c_str(), FMOD_DEFAULT, 0, &m_pSound);
}


Sound::~Sound()
{
	if (m_pSound != nullptr)
	{
		//m_pSound->release();
	}
}


bool Sound::IsPlaying() const
{
	if (m_pChannel == nullptr)
		return false;

	bool isPlaying = false;
	m_pChannel->isPlaying(&isPlaying);
	return isPlaying;
}


bool Sound::Play()
{
	m_pSound->setMode(FMOD_LOOP_OFF);
	return (Audio::g_pFMOD_system->playSound(m_pSound, nullptr, false, &m_pChannel) == FMOD_OK);
}


bool Sound::PlayLooped()
{
	m_pSound->setMode(FMOD_LOOP_NORMAL);
	m_pSound->setLoopCount(-1);
	return (Audio::g_pFMOD_system->playSound(m_pSound, nullptr, false, &m_pChannel) == FMOD_OK);
}
