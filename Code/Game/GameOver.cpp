#include "GameOver.h"
#include "../Shared/Game.h"
#include "GameStates.h"
#include "HUD.h"
#include "Maze.h"
#include "Player.h"
#include "Sounds.h"


void GameOver::OnEnter()
{
	Audio::PauseAll();
	Sounds::Play(Sounds::GAME_OVER);

	m_nFrameID = 0;
}


void GameOver::Update()
{
	++m_nFrameID;

	Maze& maze = Maze::GetMaze();
	Player& player = Player::GetPlayer();

	if (m_nFrameID >= 128)
	{
		if (m_nFrameID < 280)
		{
			if ((rand() % 40) == 0)
			{
				maze.AddDebrisFor(player.GetPos() + Vec2(float(rand() % (player.GetWidth() - 8)), float(rand() % (player.GetHeight() - 8))));
				Audio::Play(Sounds::EXPLOSION);	// present even if sounds are off
			}
		}
		else
		{
			if (m_nFrameID == 280)
			{
				player.Explode();
			}
		}

		maze.Update();
	}
}


void GameOver::Render() const
{
	Maze& maze = Maze::GetMaze();

	if (m_nFrameID < 128)
	{
		int fgColor = 7 - (m_nFrameID & 0x07);
		int bgColor = 7 - ((m_nFrameID & 0x38) >> 3);

		if (m_nFrameID < 64)
		{
			bgColor += 8;
			fgColor += 8;
		}

		Engine::Print(14, 1, static_cast<Engine::EColor>(bgColor), "\x1F\x1F\x1F\x1F\x1F\x1F");
		Engine::Print(14, 1, static_cast<Engine::EColor>(fgColor), "SHIELD");
	}
	else
	{
		if (m_nFrameID == 128)
		{
			Audio::ResumeAll();
		}

		maze.SetBrightness(static_cast<unsigned char>(255 - (m_nFrameID - 128)));
	}

	maze.Render();
	
	if (255 - (m_nFrameID - 128) <= 0)
	{
		GameStates::SwitchTo("score");
	}
}
