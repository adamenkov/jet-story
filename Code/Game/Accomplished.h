#pragma once

#include "GameStates.h"


class Accomplished : public GameState
{
public:
	virtual void OnEnter() override;
	virtual void Update() override;
	virtual void Render() const override;
	virtual void KeyPressed(char key) override;

private:
	enum class EState
	{
		FadeOut,
		FadeIn,
		Explosions,
		Explosions_PressAnyKey
	};
	EState m_eState;

	unsigned char m_cBrightness;

	int m_nFrameID;
};
