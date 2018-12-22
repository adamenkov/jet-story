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
