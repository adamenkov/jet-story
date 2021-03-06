#pragma once

#define _USING_V110_SDK71_ 1

#include <vector>
#include <Windows.h>
#include "Room.h"


class Maze
{
	Maze() {}
	Maze(const Maze&) = delete;
	Maze& operator=(const Maze&) = delete;

public:
	static Maze& GetMaze();

	bool Init();
	void ShutDown();

	void Reset();

	void Update();
	void Render() const;

	void AddDebrisFor(const Vector2& pos)		{ m_room[m_currentRow][m_currentColumn].AddDebris(pos); }
	void AddEntity(std::shared_ptr<Entity> pEntity)			{ m_room[m_currentRow][m_currentColumn].AddEntity(pEntity); }

	int  GetBasesLeft() const { return m_nBasesLeft; }

	void OnBaseDestroyed();

	void SetBrightness(unsigned char cBrightness);

	// For "Mission Accomplished"
	void ExplodeAllEntititiesExceptPlayer()	{ m_room[m_currentRow][m_currentColumn].ExplodeAllEntititiesExceptPlayer(); }
	void AddRoomExplosion()					{ m_room[m_currentRow][m_currentColumn].AddExplosion(); }

#ifdef _DEBUG
	std::vector<std::shared_ptr<Entity>>& GetRoomEntities()				{ return m_room[m_currentRow][m_currentColumn].GetEntities(); }
#endif	// #ifdef _DEBUG

	//////////////////////////////////////////////////////////////////////////
	enum
	{
		BLOCKS	= 29,
	};


private:

	void UpdateCurrentRowAndColumn();
	void SetCurrentRoom(int row, int column);

	//////////////////////////////////////////////////////////////////////////
	enum
	{
		ROWS	= 8,
		COLUMNS	= 16,

		OBJECTS = 39
	};

	//////////////////////////////////////////////////////////////////////////
	Room	m_room[ROWS][COLUMNS];

	int		m_currentRow;
	int		m_currentColumn;

	int		m_nBasesLeft;

	// Shared across all rooms
	std::vector<std::shared_ptr<Sprite>>	m_blockSprites;
	std::vector<std::shared_ptr<Texture>>	m_blockTextures;
	std::vector<std::shared_ptr<Texture>>	m_objectTextures;

	Sprite	m_spriteBlankScreen;
	std::shared_ptr<Texture> m_textureBlankScreen;
};
