#include "Audio.h"
#include "../Shared/Engine.h"
#include <cassert>
#include <map>
#include <string>
#include "fmod.hpp"
#include "Sound.h"


namespace
{
	FMOD_SYSTEM* g_pFMOD_system;

	std::map<std::string, std::unique_ptr<Sound>> s_mapSounds;
}	// namespace


namespace Audio
{
	bool Init()
	{
		if (g_pFMOD_system != nullptr)
		{
			Engine::LogError("Calling Audio::Audio again!");
			assert(false);
			return false;
		}

		if (FMOD_System_Create(&g_pFMOD_system) == FMOD_OK)
		{
			if (FMOD_System_Init(g_pFMOD_system, 100, FMOD_INIT_NORMAL, nullptr) == FMOD_OK)
			{
				return true;
			}
			else
			{
				Engine::LogError("Couldn't initialize FMOD.");
				assert(false);
			}
		}
		else
		{
			Engine::LogError("Couldn't create FMOD.");
			assert(false);
		}

		g_pFMOD_system = nullptr;
		return false;
	}


	void ShutDown()
	{
		for (auto& soundPair : s_mapSounds)
		{
			soundPair.second->Stop();
		}

		if (g_pFMOD_system != nullptr)
		{
			FMOD_System_Release(g_pFMOD_system);
			g_pFMOD_system = nullptr;
		}
	}


	void Update()
	{
		FMOD_System_Update(g_pFMOD_system);
	}


	bool Load(const std::string& fileName, const std::string& name)
	{
		if (fileName.empty())
			return false;

		std::unique_ptr<Sound> pSound = std::make_unique<Sound>(fileName);
		assert(pSound->IsOK());
		if (pSound->IsOK())
		{
			s_mapSounds[name] = std::move(pSound);
			return true;
		}

		return false;
	}


	bool IsPlaying(const std::string& name)
	{
		return (s_mapSounds.find(name) == s_mapSounds.end()) ? false : s_mapSounds[name]->IsPlaying();
	}


	bool Play(const std::string& name, int nLoopCount)
	{
		if (s_mapSounds.find(name) != s_mapSounds.end())
		{
			return s_mapSounds[name]->Play(nLoopCount);
		}

		return false;
	}


	void Stop(const std::string& name)
	{
		if (s_mapSounds.find(name) != s_mapSounds.end())
		{
			s_mapSounds[name]->Stop();
		}
	}


	void StopAll()
	{
		for (auto& soundPair : s_mapSounds)
		{
			soundPair.second->Stop();
		}
	}


	void PauseAll()
	{
		for (auto& soundPair : s_mapSounds)
		{
			soundPair.second->Pause();
		}
	}


	void ResumeAll()
	{
		for (auto& soundPair : s_mapSounds)
		{
			soundPair.second->Resume();
		}
	}
}
