#include "Sounds.h"
#include "../Shared/Engine.h"
#include <algorithm>


namespace Sounds
{
	const char* ACCOMPLISHED			= "Accomplished.wav";
	const char* ALL_BASES_DESTROYED		= "AllBasesDestroyed.wav";
	const char* EMPTY_ROOM				= "EmptyRoom.ogg";
	const char* EXPLOSION				= "Explosion.ogg";
	const char* EXPLOSION_BASE			= "ExplosionBase.ogg";
	const char* FIRE					= "Fire.ogg";
	const char* GAME_OVER				= "GameOver.wav";
	const char* ITEM_COLLECTED			= "ItemCollected.ogg";
	const char* KEY_DEFINED				= "KeyDefined.ogg";
	const char* KEY_PRESSED				= "KeyPressed.ogg";
	const char* LESS_SHIELD				= "LessShield.wav";
	const char* MAIN_THEME				= "MainTheme.ogg";
	const char* MISSION					= "Mission.wav";
	//const char* PLAYER_BALL_COLLISION	= "PlayerBombCollision.wav";
	const char* PLAYER_BALL_COLLISION	= "PlayerBombLaunch.wav";
	const char* PLAYER_BOMB_LAUNCH		= "PlayerBombLaunch.wav";
	const char* REDEFINE_KEYS			= "RedefineKeys.ogg";
	const char* SHHH					= "Shhh.ogg";


	bool Init()
	{
		std::vector<std::string> sounds{
			ACCOMPLISHED,
			ALL_BASES_DESTROYED,
			EMPTY_ROOM,
			EXPLOSION,
			EXPLOSION_BASE,
			FIRE,
			GAME_OVER,
			ITEM_COLLECTED,
			KEY_DEFINED,
			KEY_PRESSED,
			LESS_SHIELD,
			MAIN_THEME,
			MISSION,
			PLAYER_BALL_COLLISION,
			PLAYER_BOMB_LAUNCH,
			REDEFINE_KEYS,
			SHHH,
		};

		struct Loader
		{
			void operator()(const std::string& name)
			{
				Audio::Load("Assets/Sounds/" + name, name);
			}
		};

		std::for_each(sounds.begin(), sounds.end(), Loader());

		return true;
	}
}
