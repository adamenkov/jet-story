#pragma once

#include "../Shared/Game.h"


struct GameState
{
	virtual void OnEnter() {}
	virtual void Update() {}
	virtual void Render() const = 0;
	virtual void KeyPressed(char UNUSED_PARAM(key)) {}
};


namespace GameStates
{
	bool Init();
	void ShutDown();

	void Update();
	void Render();
	void KeyPressed (char key);
	void SwitchTo(const char* szNewState);

}	// namespace GameStates
