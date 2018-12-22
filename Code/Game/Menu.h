#pragma once

#define _USING_V110_SDK71_ 1

#include <string>
#include "../Shared/Engine.h"
#include "GameStates.h"


class Menu : public GameState
{
public:
	Menu();

	virtual void OnEnter() override;
	virtual void Update() override;
	virtual void Render() const override;
	virtual void KeyPressed(char key) override;

private:
	void	DrawBorder() const;
	EColor	GetRandomBorderColor() const { return static_cast<EColor>(rand() % 8); }

	enum class EState
	{
		MainMenu,
		GetReadyForSession,
		AssigningKey_Left,
		AssigningKey_Right,
		AssigningKey_Down,
		AssigningKey_Up,
		AssigningKey_Fire,
	};
	EState m_eState;

	std::string m_sRunningLine;
	int m_nFPSCounter;

	int m_waitFrames;
};
