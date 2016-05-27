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
	typedef std::map<std::string, GameState*> States;
	States states;

	GameState* pCurrentState;

}	// namespace


namespace GameStates
{
	bool Init()
	{
		states["intro"]        = new Intro;
		states["menu"]         = new Menu;
		states["session"]      = new Session;
		states["game_over"]    = new GameOver;
		states["accomplished"] = new Accomplished;
		states["score"]        = new Score;

		pCurrentState = states["session"];
		pCurrentState->OnEnter();

		return true;
	}


	void ShutDown()
	{
		struct DeleteFunctor
		{
			void operator()(const States::value_type& it) const
			{
				delete it.second;
			}
		};

		std::for_each(states.rbegin(), states.rend(), DeleteFunctor());
	}


	void KeyPressed(char key)
	{
		assert(pCurrentState);
		if (pCurrentState)
		{
			pCurrentState->KeyPressed(key);
		}

		Debug::KeyPressed(key);
	}


	void Render()
	{
		assert(pCurrentState);
		if (pCurrentState)
		{
			pCurrentState->Render();
		}
	}


	void Update()
	{
		assert(pCurrentState);
		if (pCurrentState)
		{
			pCurrentState->Update();
		}
	}


	void SwitchTo(const char* szNewState)
	{
		pCurrentState = states[szNewState];
		assert(pCurrentState);
		if (pCurrentState)
		{
			pCurrentState->OnEnter();
		}
	}

}	// namespace GameStates
