#ifndef __GAME_STATES_H
#define __GAME_STATES_H

#pragma once


struct GameState
{
	virtual void OnEnter() {}
	virtual void Update() {}
	virtual void Render() const = 0;
	virtual void KeyPressed(char key) {}
};


namespace GameStates
{
	void Init();
	void ShutDown();

	void Update();
	void Render();
	void KeyPressed (char key);
	void SwitchTo(const char* szNewState);

}	// namespace GameStates


#endif	// #ifndef __GAME_STATES_H
