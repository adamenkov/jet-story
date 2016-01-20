#include "Accomplished.h"
#include <cassert>
#include "../Common/Game.h"
#include "Debug.h"
#include "GameStates.h"
#include "HUD.h"
#include "Maze.h"
#include "Player.h"
#include "Sounds.h"


void Accomplished::OnEnter()
{
	Maze& maze = Maze::GetMaze();
	maze.ExplodeAllEntititiesExceptPlayer();

	Sounds::Play(Sounds::ALL_BASES_DESTROYED);

	m_cBrightness = 255;

	m_eState = eS_FadeOut;

	m_nFrameID = 0;
}


void Accomplished::Update()
{
	Maze& maze = Maze::GetMaze();

	switch (m_eState)
	{
	case eS_FadeOut:
		--m_cBrightness;
		if (m_cBrightness == 0)
		{
			Player::GetPlayer().Disable();
			m_eState = eS_FadeIn;
		}
		break;

	case eS_FadeIn:
		++m_cBrightness;
		if (m_cBrightness == 255)
		{
			m_eState = eS_Explosions;
		}
		break;

	case eS_Explosions:
	case eS_Explosions_PressAnyKey:
		++m_nFrameID;
		if ((m_nFrameID % 16) == (rand() % 16))
		{
			maze.AddRoomExplosion();
		}
		if (m_nFrameID >= 500)
		{
			if (m_nFrameID == 500)
			{
				Sounds::Play(Sounds::MISSION);
			}
			if (m_nFrameID == 1000)
			{
				Sounds::Play(Sounds::ACCOMPLISHED);
			}
			if (m_nFrameID == 2500)
			{
				m_eState = eS_Explosions_PressAnyKey;
			}
			if ((m_nFrameID % 8) == 0)
			{
				if (m_cBrightness > 0)
				{
					--m_cBrightness;
				}
			}
		}
		break;

	default:
		assert(!"Should not be here!");
	}

	maze.Update();
}


void Accomplished::Render() const
{
	Maze& maze = Maze::GetMaze();

	maze.SetBrightness(m_cBrightness);
	maze.Render();

	if (m_nFrameID >= 500)
	{
		Engine::Print(7, 7, Engine::eC_White, "MISSION");
		
		if (m_nFrameID >= 1000)
		{
			Engine::Print(14, 14, Engine::eC_White, "ACCOMPLISHED");
		}
	}
}


void Accomplished::KeyPressed(char key)
{
	if (m_eState == eS_Explosions_PressAnyKey)
	{
		GameStates::SwitchTo("score");
	}
}
