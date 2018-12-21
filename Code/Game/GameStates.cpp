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
	using GameStates = std::map<std::string, std::shared_ptr<GameState>>;
	GameStates gameStates;

	std::shared_ptr<GameState> pCurrentGameState;

}	// namespace


namespace GameStates
{
	bool Init()
	{
		gameStates["intro"]        = std::make_shared<Intro>();
		gameStates["menu"]         = std::make_shared<Menu>();
		gameStates["session"]      = std::make_shared<Session>();
		gameStates["game_over"]    = std::make_shared<GameOver>();
		gameStates["accomplished"] = std::make_shared<Accomplished>();
		gameStates["score"]        = std::make_shared<Score>();

		pCurrentGameState = gameStates["intro"];
		pCurrentGameState->OnEnter();

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
		pCurrentGameState = gameStates[szNewState];
		assert(pCurrentGameState);
		if (pCurrentGameState)
		{
			pCurrentGameState->OnEnter();
		}
	}

}	// namespace GameStates
