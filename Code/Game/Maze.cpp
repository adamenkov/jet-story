#include "Maze.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>
#include "../Shared/Engine.h"
#include "Debug.h"
#include "GameStates.h"
#include "HUD.h"
#include "Player.h"
#include "Room.h"
#include "Settings.h"
#include "Sounds.h"


Maze& Maze::GetMaze()
{
	static Maze maze;
	return maze;
}


void Maze::Init()
{
	for (int i = 0; i < OBJECTS; ++i)
	{
		Texture* pObjectTexture = NULL;

		switch (i)
		{
		case 0:
		case 5:
		case 6:
		case 7:
		case 8:
			break;

		default:
			{
				std::ostringstream os;
				os << "Assets/Objects/Object" << i << ".bmp";
				pObjectTexture = new Texture(os.str().c_str());
			}
		}

		m_objectTextures.push_back(pObjectTexture);
	}


	for (int i = 0; i < BLOCKS; ++i)
	{
		Sprite* pBlockSprite = new Sprite;
		
		std::ostringstream os;
		os << "Assets/Maze/Block" << i << ".bmp";

		Texture* pBlockTexture = new Texture(os.str().c_str());
		pBlockSprite->SetTexture(pBlockTexture);

		m_blockSprites .push_back(pBlockSprite);
		m_blockTextures.push_back(pBlockTexture);
	}


	const char* MAZE_FILE = "Assets/Maze/Maze.map";
	std::ifstream ifs(MAZE_FILE);
	std::string sComressedMap((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	if (!ifs)
	{
		Engine::LogError("Could not load file %s.", MAZE_FILE);
	}

	const char* pByteStream = sComressedMap.c_str();

	const char* GAME_OBJECTS_FILE = "Assets/Maze/GameObjects.bin";
	std::ifstream ifs2("Assets/Maze/GameObjects.bin", std::ios::binary);
	std::vector<char> vGameObjectsSpawnParams((std::istreambuf_iterator<char>(ifs2)), std::istreambuf_iterator<char>());
	if (!ifs2)
	{
		Engine::LogError("Could not load file %s.", GAME_OBJECTS_FILE);
	}

	if (ifs && ifs2)
	{
		for (int row = 0; row < ROWS; ++row)
		{
			for (int column = 0; column < COLUMNS; ++column)
			{
				m_room[row][column].Init(
					(const unsigned char*) pByteStream,
					(const unsigned char*) &vGameObjectsSpawnParams[32 * ((16 * row) + column)],
					m_objectTextures);
				pByteStream += strlen(pByteStream) + 1;
			}
		}
	}
	else
	{
		assert(false);
	}

	m_room[0][0].AddGameEntity(&Player::GetPlayer());

	m_textureBlankScreen.LoadFromFile("Assets/BlankScreen.png", D3DCOLOR_RGBA(1, 2, 3, 4));	// opaque black screen
	m_spriteBlankScreen.SetTexture(&m_textureBlankScreen);
}


void Maze::ShutDown()
{
	std::for_each(m_blockSprites  .begin(), m_blockSprites  .end(), DeleteFunctor());
	std::for_each(m_blockTextures .begin(), m_blockTextures .end(), DeleteFunctor());
	std::for_each(m_objectTextures.begin(), m_objectTextures.end(), DeleteFunctor());
}


void Maze::Reset()
{
	for (int row = 0; row < ROWS; ++row)
	{
		for (int column = 0; column < COLUMNS; ++column)
		{
			m_room[row][column].Reset();
		}
	}

	SetCurrentRoom(0, 0);

	m_nBasesLeft = 47;

	SetBrightness(255);
}


void Maze::Update()
{
	m_room[m_curRow][m_curColumn].Update();
	
	UpdateCurrentRowAndColumn();
	
	HUD::GetHUD().Update();
}


void Maze::Render() const
{
	m_room[m_curRow][m_curColumn].Render(m_blockSprites);
	
	HUD::GetHUD().Render();

	m_spriteBlankScreen.Render();

	Debug::Render();
}


void Maze::OnBaseDestroyed()
{
	if (--m_nBasesLeft <= 0)
	{
		if (Sounds::IsPlaying(Sounds::LESS_SHIELD))
		{
			Sounds::Stop(Sounds::LESS_SHIELD);
		}

		GameStates::SwitchTo("accomplished");
	}
}


void Maze::SetBrightness(unsigned char cBrightness)
{
	m_spriteBlankScreen.SetAlpha(255 - cBrightness);
}


void Maze::UpdateCurrentRowAndColumn()
{
	Player& player = Player::GetPlayer();
	Vector2 pos = player.GetPos();

	float x = pos.x;
	float y = pos.y;
	
	int width  = player.GetWidth();
	int height = player.GetHeight();

	if (x > 0.999f + static_cast<float>(Engine::eScreenWidthInPixels - width))
	{
		x = 0.f;
		player.SetPos(x, y);
		SetCurrentRoom(m_curRow, m_curColumn + 1);
	}
	else
	{
		if (x < 0.f)
		{
			x = 0.999f + static_cast<float>(Engine::eScreenWidthInPixels - width);
			player.SetPos(x, y);
			SetCurrentRoom(m_curRow, m_curColumn - 1);
		}
	}

	if (y > 0.999f + static_cast<float>(Engine::eScreenHeightInPixels - height))
	{
		y = 32.f;
		player.SetPos(x, y);
		SetCurrentRoom(m_curRow + 1, m_curColumn);
	}
	else
	{
		if (y < 32.f)
		{
			y = 0.999f + static_cast<float>(Engine::eScreenHeightInPixels - height);
			player.SetPos(x, y);
			SetCurrentRoom(m_curRow - 1, m_curColumn);
		}
	}
}


void Maze::SetCurrentRoom(int row, int column)
{
	assert((0 <= row) && (row < ROWS));
	assert((0 <= column) && (column < COLUMNS));

	m_room[m_curRow][m_curColumn].OnPlayerExit();
	m_curRow = row;
	m_curColumn = column;
	m_room[m_curRow][m_curColumn].OnPlayerEnter();

	Player::GetPlayer().OnRoomChanged();
}
