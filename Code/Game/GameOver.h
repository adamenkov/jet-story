#pragma once

#include "GameStates.h"


class GameOver : public GameState
{
public:
	virtual void OnEnter() override;
	virtual void Update() override;
	virtual void Render() const override;

private:
	int m_nFrameID;
};
