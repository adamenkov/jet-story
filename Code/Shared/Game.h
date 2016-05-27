#ifndef __GAME_H
#define __GAME_H

#pragma once

#define _USING_V110_SDK71_ 1


namespace Game
{
	extern const char* GetName();

	extern void Init();
	extern void ShutDown();

	extern void Render();
	extern void Update();

	extern void KeyPressed(char key);
}	// namespace Game


#define UNUSED_PARAM(x)


#endif	// #ifndef __GAME_H
