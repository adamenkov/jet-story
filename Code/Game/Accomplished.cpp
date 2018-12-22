#include "Accomplished.h"
#include <cassert>
#include "../Shared/Game.h"
#include "Debug.h"
#include "GameStates.h"
#include "HUD.h"
#include "Maze.h"
#include "Player.h"
#include "Sounds.h"


void Accomplished::OnEnter()
{
	std::shared_ptr<Maze> maze = Maze::GetMaze();
	maze->ExplodeAllEntititiesExceptPlayer();

	Audio::Play(Sounds::ALL_BASES_DESTROYED);

	m_cBrightness = 255;

	m_eState = EState::FadeOut;

	m_nFrameID = 0;
}


void Accomplished::Update()
{
	std::shared_ptr<Maze> maze = Maze::GetMaze();

	switch (m_eState)
	{
	case EState::FadeOut:
		--m_cBrightness;
		if (m_cBrightness == 0)
		{
			Player::GetPlayer()->Disable();
			m_eState = EState::FadeIn;
		}
		break;

	case EState::FadeIn:
		++m_cBrightness;
		if (m_cBrightness == 255)
		{
			m_eState = EState::Explosions;
		}
		break;

	case EState::Explosions:
	case EState::Explosions_PressAnyKey:
		++m_nFrameID;
		if ((m_nFrameID % 16) == (rand() % 16))
		{
			maze->AddRoomExplosion();
		}
		if (m_nFrameID >= 500)
		{
			if (m_nFrameID == 500)
			{
				Audio::Play(Sounds::MISSION);
			}
			if (m_nFrameID == 1000)
			{
				Audio::Play(Sounds::ACCOMPLISHED);
			}
			if (m_nFrameID == 2500)
			{
				m_eState = EState::Explosions_PressAnyKey;
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

	maze->Update();
}


void Accomplished::Render() const
{
	std::shared_ptr<Maze> maze = Maze::GetMaze();

	maze->SetBrightness(m_cBrightness);
	maze->Render();

	if (m_nFrameID >= 500)
	{
		Engine::Print(7, 7, EColor::White, "MISSION");
		
		if (m_nFrameID >= 1000)
		{
			Engine::Print(14, 14, EColor::White, "ACCOMPLISHED");
		}
	}
}


void Accomplished::KeyPressed(char UNUSED_PARAM(key))
{
	if (m_eState == EState::Explosions_PressAnyKey)
	{
		GameStates::SwitchTo("score");
	}
}
