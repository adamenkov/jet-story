#pragma once

#include "fmod.hpp"


namespace Audio
{
	bool Init();
	void ShutDown();

	void Update();


	extern FMOD_SYSTEM* g_pFMOD_system;
	extern FMOD::System* g_pFMOD_system2;
}
