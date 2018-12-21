#include "GameStates.h"
#include <algorithm>
#include <cassert>
#include <map>
#include "Accomplished.h"
#include "Debug.h"
#include "GameOver.h"
#include "Intro.h"
#include "Menu.h"
#include "Score.h"
#include "Session.h"


namespace
{
	using GameStates = std::map<std::string, std::unique_ptr<GameState>>;
	GameStates gameStates;

	GameState* pCurrentGameState;

}	// namespace


namespace GameStates
{
	bool Init()
	{
		gameStates["intro"]        = std::make_unique<Intro>();
		gameStates["menu"]         = std::make_unique<Menu>();
		gameStates["session"]      = std::make_unique<Session>();
		gameStates["game_over"]    = std::make_unique<GameOver>();
		gameStates["accomplished"] = std::make_unique<Accomplished>();
		gameStates["score"]        = std::make_unique<Score>();

		gameStates["session"]->OnEnter();

		return true;
	}


	void ShutDown()
	{
	}


	void KeyPressed(char key)
	{
		assert(pCurrentGameState);
		if (pCurrentGameState)
		{
			pCurrentGameState->KeyPressed(key);
		}

		Debug::KeyPressed(key);
	}


	void Render()
	{
		assert(pCurrentGameState);
		if (pCurrentGameState)
		{
			pCurrentGameState->Render();
		}
	}


	void Update()
	{
		assert(pCurrentGameState);
		if (pCurrentGameState)
		{
			pCurrentGameState->Update();
		}
	}


	void SwitchTo(const char* szNewState)
	{
		pCurrentGameState = gameStates[szNewState].get();
		assert(pCurrentGameState);
		if (pCurrentGameState)
		{
			pCurrentGameState->OnEnter();
		}
	}

}	// namespace GameStates
