#ifndef __MAZE_H
#define __MAZE_H

#pragma once

#define _USING_V110_SDK71_ 1

#include <vector>
#include <Windows.h>
#include "Room.h"


class Maze
{
	Maze() {}
	Maze(const Maze&);
	Maze& operator=(const Maze&);

public:
	static Maze& GetMaze();

	void Init();
	void ShutDown();

	void Reset();

	void Update();
	void Render() const;

	void AddDebrisFor(const Vec2& pos)		{ m_room[m_curRow][m_curColumn].AddDebris(pos); }
	void AddEntity(Entity* pEntity)			{ m_room[m_curRow][m_curColumn].AddEntity(pEntity); }

	int  GetBasesLeft() const { return m_nBasesLeft; }

	void OnBaseDestroyed();

	void SetBrightness(unsigned char cBrightness);

	// For "Mission Accomplished"
	void ExplodeAllEntititiesExceptPlayer()	{ m_room[m_curRow][m_curColumn].ExplodeAllEntititiesExceptPlayer(); }
	void AddRoomExplosion()					{ m_room[m_curRow][m_curColumn].AddExplosion(); }

#ifdef _DEBUG
	Entities& GetRoomEntities()				{ return m_room[m_curRow][m_curColumn].GetEntities(); }
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

	struct DeleteFunctor
	{
		template<typename T>
		void operator()(const T* ptr) const
		{
			delete ptr;
		}
	};

	//////////////////////////////////////////////////////////////////////////
	Room	m_room[ROWS][COLUMNS];

	int		m_curRow;
	int		m_curColumn;

	int		m_nBasesLeft;

	// Shared across all rooms
	Sprites		m_blockSprites;
	Textures	m_blockTextures;
	Textures	m_objectTextures;

	Sprite	m_spriteBlankScreen;
	Texture m_textureBlankScreen;
};


#endif	// #ifndef __MAZE_H
