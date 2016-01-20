#ifndef __GAME_H
#define __GAME_H

#pragma once


namespace Game
{
	extern const char* GetName();

	extern void Init();
	extern void ShutDown();

	extern void Render();
	extern void Update();

	extern void KeyPressed(char key);

}	// namespace Game


#endif	// #ifndef __GAME_H
