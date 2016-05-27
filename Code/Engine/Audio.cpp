#include "../Shared/Engine.h"
#include <cassert>
#include <map>
#include <string>
#include "fmod.hpp"
#include "Sound.h"


namespace
{
	typedef std::map<std::string, Sound*> Sounds;
	Sounds sounds;

}	// namespace


namespace Audio
{
	FMOD_SYSTEM* g_pFMOD_system;
	

	bool Load(const char* szFileName, const char* szName)
	{
		if (strlen(szFileName) == 0)
			return false;
		
		Sound* pSound = new Sound(szFileName);
		assert(pSound->IsOK());
		if (pSound->IsOK())
		{
			delete sounds[szName];
			sounds[szName] = pSound;
			return true;
		}

		delete pSound;
		return false;
	}
	
	bool IsPlaying(const char* szName)
	{
		Sound* pSound = sounds[szName];
		return pSound ? pSound->IsPlaying() : false;
	}

	bool Play(const char* szName, int nLoopCount)
	{
		Sound* pSound = sounds[szName];
		return pSound ? pSound->Play(nLoopCount) : false;
	}
	
	void Stop(const char* szName)
	{
		if (Sound* pSound = sounds[szName])
		{
			pSound->Stop();
		}
	}
	
	void StopAll()
	{
		for (Sounds::iterator it = sounds.begin(), itEnd = sounds.end(); it != itEnd; ++it)
		{
			if (Sound* pSound = it->second)
			{
				pSound->Stop();
			}
		}
	}


	//////////////////////////////////////////////////////////////////////////

	bool Init()
	{
		return (FMOD_System_Create(&g_pFMOD_system) == FMOD_OK) &&
			(FMOD_System_Init(g_pFMOD_system, 100, FMOD_INIT_NORMAL, nullptr) == FMOD_OK);
	}

	void ShutDown()
	{
		for (Sounds::iterator it = sounds.begin(), itEnd = sounds.end(); it != itEnd; ++it)
		{
			if (Sound* pSound = it->second)
			{
				pSound->Stop();
				delete pSound;
			}
		}

		sounds.clear();

		FMOD_System_Release(g_pFMOD_system);
	}

	void Audio::Update()
	{
		FMOD_System_Update(g_pFMOD_system);
	}

	void PauseAll()
	{
		for (Sounds::iterator it = sounds.begin(), itEnd = sounds.end(); it != itEnd; ++it)
		{
			if (Sound* pSound = it->second)
			{
				pSound->Pause();
			}
		}
	}

	void ResumeAll()
	{
		for (Sounds::iterator it = sounds.begin(), itEnd = sounds.end(); it != itEnd; ++it)
		{
			if (Sound* pSound = it->second)
			{
				pSound->Resume();
			}
		}
	}

}	// namespace Audio
