#ifndef __SOUNDS_H
#define __SOUNDS_H

#pragma once


namespace Sounds
{
	extern const char* ACCOMPLISHED;
	extern const char* ALL_BASES_DESTROYED;
	extern const char* EMPTY_ROOM;
	extern const char* EXPLOSION;
	extern const char* FIRE;
	extern const char* GAME_OVER;
	extern const char* ITEM_COLLECTED;
	extern const char* KEY_DEFINED;
	extern const char* KEY_PRESSED;
	extern const char* LESS_SHIELD;
	extern const char* MAIN_THEME;
	extern const char* MISSION;
	extern const char* PLAYER_BALL_COLLISION;
	extern const char* PLAYER_BOMB_LAUNCH;
	extern const char* REDEFINE_KEYS;
	extern const char* SHHH;

	bool Init();

	bool IsPlaying(...);
	void Play(...);
	void Stop(...);
}


#endif	// #ifndef __SOUNDS_H
