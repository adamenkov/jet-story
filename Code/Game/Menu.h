#ifndef __MENU_H
#define __MENU_H

#pragma once

#define _USING_V110_SDK71_ 1

#include <string>
#include "../Shared/Engine.h"
#include "GameStates.h"


class Menu : public GameState
{
public:
	Menu();

	virtual void OnEnter();
	virtual void Update();
	virtual void Render() const;
	virtual void KeyPressed(char key);

private:
	void			DrawBorder() const;
	Engine::EColor	GetRandomBorderColor() const { return static_cast<Engine::EColor>(rand() % 8); }

	enum EState
	{
		eMS_MainMenu,
		eMS_GetReadyForSession,
		eMS_AssigningKey_Left,
		eMS_AssigningKey_Right,
		eMS_AssigningKey_Down,
		eMS_AssigningKey_Up,
		eMS_AssigningKey_Fire,
	};
	EState m_eState;

	std::string m_sRunningLine;
	int m_nFPSCounter;

	int m_waitFrames;
};


#endif	// #ifndef __MENU_H
