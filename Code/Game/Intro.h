#ifndef __INTRO_H
#define __INTRO_H

#pragma once

#include "../Shared/Engine.h"
#include "GameStates.h"


class Intro : public GameState
{
public:
	Intro();

	virtual void Render() const;
	virtual void KeyPressed(char key);

private:
	enum EIntroState
	{
		eIS_FirstScreen,
		eIS_SecondScreen,
		eIS_ThirdScreen,
	};
	EIntroState m_eIntroState;

	Sprite* m_pScreenSprite;
};


#endif	// #ifndef __INTRO_H
