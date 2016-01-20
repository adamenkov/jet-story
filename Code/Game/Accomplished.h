#ifndef __ACCOMPLISHED_H
#define __ACCOMPLISHED_H

#pragma once

#include "GameStates.h"


class Accomplished : public GameState
{
public:
	virtual void OnEnter();
	virtual void Update();
	virtual void Render() const;
	virtual void KeyPressed(char key);

private:
	enum EState
	{
		eS_FadeOut,
		eS_FadeIn,
		eS_Explosions,
		eS_Explosions_PressAnyKey
	};
	EState m_eState;

	unsigned char m_cBrightness;

	int m_nFrameID;
};


#endif	// #ifndef __ACCOMPLISHED_H
