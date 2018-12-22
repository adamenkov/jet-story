#pragma once

#include "GameStates.h"


class Session : public GameState
{
public:
	virtual void OnEnter();
	virtual void Update();
	virtual void Render() const;
};
