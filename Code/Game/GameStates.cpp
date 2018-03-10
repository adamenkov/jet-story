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
	using GameStates = std::map<std::string, GameState*>;
	GameStates gameStates;

	GameState* pCurrentGameState;

}	// namespace


namespace GameStates
{
	bool Init()
	{
		gameStates["intro"]        = new Intro;
		gameStates["menu"]         = new Menu;
		gameStates["session"]      = new Session;
		gameStates["game_over"]    = new GameOver;
		gameStates["accomplished"] = new Accomplished;
		gameStates["score"]        = new Score;

		pCurrentGameState = gameStates["session"];
		pCurrentGameState->OnEnter();

		return true;
	}


	void ShutDown()
	{
		struct DeleteFunctor
		{
			void operator()(const GameStates::value_type& it) const
			{
				delete it.second;
			}
		};

		std::for_each(gameStates.rbegin(), gameStates.rend(), DeleteFunctor());
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
