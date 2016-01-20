#ifndef __GAME_OVER_H
#define __GAME_OVER_H

#pragma once

#include "GameStates.h"


class GameOver : public GameState
{
public:
	virtual void OnEnter();
	virtual void Update();
	virtual void Render() const;

private:
	int m_nFrameID;
};


#endif	// #ifndef __GAME_OVER_H
