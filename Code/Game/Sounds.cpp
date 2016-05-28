#include "Sounds.h"
#include "../Shared/Engine.h"


namespace Sounds
{
	const char* ACCOMPLISHED			= "Assets/Sounds/Accomplished.wav";
	const char* ALL_BASES_DESTROYED		= "Assets/Sounds/AllBasesDestroyed.wav";
	const char* EMPTY_ROOM				= "Assets/Sounds/EmptyRoom.ogg";
	const char* EXPLOSION				= "Assets/Sounds/Explosion.ogg";
	const char* EXPLOSION_BASE			= "Assets/Sounds/ExplosionBase.ogg";
	const char* FIRE					= "Assets/Sounds/Fire.ogg";
	const char* GAME_OVER				= "Assets/Sounds/GameOver.wav";
	const char* ITEM_COLLECTED			= "Assets/Sounds/ItemCollected.ogg";
	const char* KEY_DEFINED				= "Assets/Sounds/KeyDefined.ogg";
	const char* KEY_PRESSED				= "Assets/Sounds/KeyPressed.ogg";
	const char* LESS_SHIELD				= "Assets/Sounds/LessShield.wav";
	const char* MAIN_THEME				= "Assets/Sounds/MainTheme.ogg";
	const char* MISSION					= "Assets/Sounds/Mission.wav";
	//const char* PLAYER_BALL_COLLISION	= "Assets/Sounds/PlayerBombCollision.wav";
	const char* PLAYER_BALL_COLLISION	= "Assets/Sounds/PlayerBombLaunch.wav";
	const char* PLAYER_BOMB_LAUNCH = "Assets/Sounds/PlayerBombLaunch.wav";
	const char* REDEFINE_KEYS			= "Assets/Sounds/RedefineKeys.ogg";
	const char* SHHH					= "Assets/Sounds/Shhh.ogg";


	bool Init()
	{
		Audio::Load(ACCOMPLISHED, ACCOMPLISHED);
		Audio::Load(ALL_BASES_DESTROYED, ALL_BASES_DESTROYED);
		Audio::Load(EMPTY_ROOM, EMPTY_ROOM);
		Audio::Load(EXPLOSION, EXPLOSION);
		Audio::Load(EXPLOSION_BASE, EXPLOSION_BASE);
		Audio::Load(FIRE, FIRE);
		Audio::Load(GAME_OVER, GAME_OVER);
		Audio::Load(ITEM_COLLECTED, ITEM_COLLECTED);
		Audio::Load(KEY_DEFINED, KEY_DEFINED);
		Audio::Load(KEY_PRESSED, KEY_PRESSED);
		Audio::Load(LESS_SHIELD, LESS_SHIELD);
		Audio::Load(MAIN_THEME, MAIN_THEME);
		Audio::Load(MISSION, MISSION);
		Audio::Load(PLAYER_BALL_COLLISION, PLAYER_BALL_COLLISION);
		Audio::Load(PLAYER_BOMB_LAUNCH, PLAYER_BOMB_LAUNCH);
		Audio::Load(REDEFINE_KEYS, REDEFINE_KEYS);
		Audio::Load(SHHH, SHHH);

		return true;
	}
}
