#include "Menu.h"
#include <cassert>
#include <fstream>
#include <string>
#include "../Shared/Engine.h"
#include "../Shared/Game.h"
#include "Settings.h"
#include "Sounds.h"


Menu::Menu() :
	m_eState(EState::MainMenu)
{
	std::ifstream fileRunningLine("Assets/RunningLine.txt");
	m_sRunningLine.assign(
		std::istreambuf_iterator<char>(fileRunningLine),
		std::istreambuf_iterator<char>()
	);
}


void Menu::OnEnter()
{
	m_eState = EState::MainMenu;

	if (Settings::bMusic)
	{
		if (!Audio::IsPlaying(Sounds::MAIN_THEME))
		{
			Audio::PlayLooped(Sounds::MAIN_THEME);
		}
	}
	else
	{
		Audio::Stop(Sounds::MAIN_THEME);
	}

	m_nFPSCounter = 0;

	m_waitFrames = 0;
}


void Menu::Update()
{
	++m_nFPSCounter;

	if (m_waitFrames > 0)
	{
		if (--m_waitFrames == 0)
		{
			switch (m_eState)
			{
			case EState::AssigningKey_Left:		m_eState = EState::AssigningKey_Right;	break;
			case EState::AssigningKey_Right:	m_eState = EState::AssigningKey_Down;	break;
			case EState::AssigningKey_Down:		m_eState = EState::AssigningKey_Up;		break;
			case EState::AssigningKey_Up:		m_eState = EState::AssigningKey_Fire;	break;
			case EState::AssigningKey_Fire:		m_eState = EState::MainMenu;			break;
			
			case EState::MainMenu:
				break;
			}
		}
	}
}


void Menu::Render() const
{
	if (m_eState == EState::AssigningKey_Fire)
	{
		if ((Settings::cKeyLeft  == 'K') &&
			(Settings::cKeyRight == 'A') &&
			(Settings::cKeyDown  == 'R') &&
			(Settings::cKeyUp    == 'E') &&
			(Settings::cKeyFire  == 'L'))
		{
			DrawBorder();

			if (m_waitFrames == 40)
			{
				Settings::bInvulnerability = true;
				Audio::Play(Sounds::SHHH);
			}
		}
	}

	switch (m_eState)
	{
	case EState::MainMenu:
	case EState::GetReadyForSession:
		Engine::Print(12,  5, EColor::White, "JET-STORY");

		Engine::Print( 2, 13, EColor::Grey,  "1.  REDEFINE KEYS");
		
		Engine::Print( 2, 15, EColor::Grey,  "2.  SOUND EFFECTS");
		Engine::Print(20, 15, Settings::bSoundEffects ? EColor::White : EColor::LightMagenta, "ON");
		Engine::Print(22, 15, EColor::Grey,  "/");
		Engine::Print(23, 15, Settings::bSoundEffects ? EColor::LightMagenta : EColor::White, "OFF");

		Engine::Print( 2, 17, EColor::Grey,  "3.  MUSIC");
		Engine::Print(12, 17, Settings::bMusic ? EColor::White : EColor::LightMagenta, "ON");
		Engine::Print(14, 17, EColor::Grey,  "/");
		Engine::Print(15, 17, Settings::bMusic ? EColor::LightMagenta : EColor::White, "OFF");

		Engine::Print( 2, 19, EColor::Grey,  "4.  START GAME");


		enum { y = 8 * (Engine::eScreenHeightInCharacters - 1) };

		Engine::DrawText(
			-m_nFPSCounter % 8,
			y,
			EColor::Cyan,
			m_sRunningLine.substr(
				(m_nFPSCounter / 8) % m_sRunningLine.length(), 
				Engine::eScreenWidthInCharacters
			)
		);

		Engine::Print(0,
			Engine::eScreenHeightInCharacters - 1, EColor::Black, '\x1F');
		Engine::Print(Engine::eScreenWidthInCharacters - 1,
			Engine::eScreenHeightInCharacters - 1, EColor::Black, '\x1F');

		break;
		
	case EState::AssigningKey_Fire:
		Engine::Print(12,  17, EColor::LightYellow, "FIRE");
		Engine::Print(18,  17, EColor::LightYellow, Settings::cKeyFire);
	case EState::AssigningKey_Up:
		Engine::Print(12,  16, EColor::LightYellow, "UP");
		Engine::Print(18,  16, EColor::LightYellow, Settings::cKeyUp);
	case EState::AssigningKey_Down:
		Engine::Print(12,  15, EColor::LightYellow, "DOWN");
		Engine::Print(18,  15, EColor::LightYellow, Settings::cKeyDown);
	case EState::AssigningKey_Right:
		Engine::Print(12,  14, EColor::LightYellow, "RIGHT");
		Engine::Print(18,  14, EColor::LightYellow, Settings::cKeyRight);
	case EState::AssigningKey_Left:
		Engine::Print(12,  13, EColor::LightYellow, "LEFT");
		Engine::Print(18,  13, EColor::LightYellow, Settings::cKeyLeft);
		break;
	}
}


void Menu::KeyPressed(char key)
{
	if (m_waitFrames > 0)
		return;

	switch (m_eState)
	{
	case EState::MainMenu:
		Audio::Play(Sounds::KEY_PRESSED);

		switch (key)
		{
		case '1':
			Audio::Play(Sounds::REDEFINE_KEYS);
			Settings::cKeyLeft	= ' ';
			Settings::cKeyRight	= ' ';
			Settings::cKeyDown	= ' ';
			Settings::cKeyUp	= ' ';
			Settings::cKeyFire	= ' ';
			m_eState = EState::AssigningKey_Left;
			break;

		case '2':
			Settings::bSoundEffects = !Settings::bSoundEffects;
			break;

		case '3':
			Settings::bMusic = !Settings::bMusic;
			if (Settings::bMusic)
			{
				Audio::PlayLooped(Sounds::MAIN_THEME);
			}
			else
			{
				Audio::Stop(Sounds::MAIN_THEME);
			}
			break;

		case '4':
			m_eState = EState::GetReadyForSession;
			break;

		default:
			m_waitFrames = 6;
		}
		break;

	case EState::GetReadyForSession:
		Audio::Play(Sounds::KEY_DEFINED);
		GameStates::SwitchTo("session");
		break;

	case EState::AssigningKey_Left:
		Settings::cKeyLeft = key;
		Audio::Play(Sounds::KEY_DEFINED);
		m_waitFrames = 20;
		break;

	case EState::AssigningKey_Right:
		Settings::cKeyRight = key;
		Audio::Play(Sounds::KEY_DEFINED);
		m_waitFrames = 20;
		break;

	case EState::AssigningKey_Down:
		Settings::cKeyDown = key;
		Audio::Play(Sounds::KEY_DEFINED);
		m_waitFrames = 20;
		break;

	case EState::AssigningKey_Up:
		Settings::cKeyUp = key;
		Audio::Play(Sounds::KEY_DEFINED);
		m_waitFrames = 20;
		break;

	case EState::AssigningKey_Fire:
		Settings::cKeyFire = key;
		Audio::Play(Sounds::KEY_DEFINED);
		m_waitFrames =
			((Settings::cKeyLeft  == 'K') &&
			 (Settings::cKeyRight == 'A') &&
			 (Settings::cKeyDown  == 'R') &&
			 (Settings::cKeyUp    == 'E') &&
			 (Settings::cKeyFire  == 'L'))
			? 50 : 20;
		break;
	}
}


void Menu::DrawBorder() const
{
	const char* szScreenLine = "________________________________";

	for (int i = 0; i < 8; ++i)
	{
		Engine::DrawText(0, i - 7, GetRandomBorderColor(), szScreenLine);
	}
	for (int i = 8; i < Engine::eScreenHeightInPixels - 8; ++i)
	{
		Engine::DrawText(0, i - 7, GetRandomBorderColor(), "_                              _");
	}
	for (int i = Engine::eScreenHeightInPixels - 8; i < Engine::eScreenHeightInPixels; ++i)
	{
		Engine::DrawText(0, i - 7, GetRandomBorderColor(), szScreenLine);
	}
}
