#include "Settings.h"
#include "../Common/Engine.h"


namespace Settings
{
	bool	bInvulnerability = false;

	bool	bSoundEffects	= true;
	bool	bMusic			= (WinMain != 0);	// Ad-hoc: I need to reference Engine somehow to make the linker happy

	char	cKeyLeft	= '6';
	char	cKeyRight	= '7';
	char	cKeyDown	= '8';
	char	cKeyUp		= '9';
	char	cKeyFire	= '0';

}	// namespace Settings
