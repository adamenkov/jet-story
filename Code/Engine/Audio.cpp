#include "../Shared/Engine.h"
#include <cassert>
#include <map>
#include <string>
#include "fmod.hpp"
#include "Sound.h"


namespace
{
	using Sounds = std::map<std::string, Sound*>;
	Sounds sounds;

}	// namespace


namespace Audio
{
	FMOD_SYSTEM* g_pFMOD_system;
	

	bool Load(const std::string& fileName, const std::string& name)
	{
		if (fileName.empty())
			return false;
		
		Sound* pSound = new Sound(fileName);
		assert(pSound->IsOK());
		if (pSound->IsOK())
		{
			delete sounds[name];
			sounds[name] = pSound;
			return true;
		}

		delete pSound;
		return false;
	}
	
	bool IsPlaying(const std::string& name)
	{
		Sound* pSound = sounds[name];
		return pSound ? pSound->IsPlaying() : false;
	}

	bool Play(const std::string& name, int nLoopCount)
	{
		Sound* pSound = sounds[name];
		return pSound ? pSound->Play(nLoopCount) : false;
	}
	
	void Stop(const std::string& name)
	{
		if (Sound* pSound = sounds[name])
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
