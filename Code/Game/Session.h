#pragma once

#include "GameStates.h"


class Session : public GameState
{
public:
	virtual void OnEnter() override;
	virtual void Update() override;
	virtual void Render() const override;
};
