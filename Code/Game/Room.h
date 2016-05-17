#ifndef __ROOM_H
#define __ROOM_H

#pragma once

#define _USING_V110_SDK71_ 1

#include <vector>
#include "../Common/Engine.h"
#include "Entity.h"

class Texture;


class Room
{
public:
	~Room();

	void Init(const unsigned char* pRoomInitSequence, const unsigned char* pEntitiesInitSequence, const Textures& textures);
	void Reset();

	void Render(const Sprites& blocks) const;
	void Update();

	//TODO Replace with more specific (lifetime-aware) versions
	void AddEntity(Entity* pEntity);
	void AddGameEntity(Entity* pEntity);
	
	void AddDebris(const Vec2& pos);
	
	void ExplodeAllEntititiesExceptPlayer();

	void OnPlayerEnter();
	void OnPlayerExit();

	// Mission Accomplished stuff
	void AddExplosion();

#ifdef _DEBUG
	Entities& GetEntities() { return m_entities; }
#endif	// #ifdef _DEBUG

private:
	void AddObstacle(int row, int column, int left, int top, int right, int bottom);
	bool OverlapsObstacles(const Entity* pEntity, float x, float y) const;
	
	Entity* CreateEntity(int type, const Vec2& vInitialPos, const Textures& textures);

	int GetBlock(int row, int column) const { return m_block[row][column]; }

	void RemoveEntities(Entity::ELifeTime eMinimumLifeTimeToRemove);

	void MoveEntitiesAndResolveCollisions();
	void UpdateEntities();
	void CollectGarbageEntities();

	//////////////////////////////////////////////////////////////////////////
	enum
	{
		ROWS	= 5,
		COLUMNS	= 8,

		eInitialEntitiesPerRoom = 6,
		eMaxEntitiesPerRoom = 8
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
	int m_block[ROWS][COLUMNS];

	Entities m_entities;
	Entities m_entitiesToAdd;
	
	typedef std::vector<RECT>	Obstacles;
	Obstacles	m_obstacles;
};


#endif	// #ifndef __ROOM_H
