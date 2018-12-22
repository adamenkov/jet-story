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
