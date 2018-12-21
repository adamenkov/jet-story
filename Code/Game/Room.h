#ifndef __ROOM_H
#define __ROOM_H

#pragma once

#define _USING_V110_SDK71_ 1

#include <vector>
#include "../Shared/Engine.h"
#include "Entity.h"

class Texture;


class Room
{
public:
	void Init(const unsigned char* pRoomInitSequence, const unsigned char* pEntitiesInitSequence, const std::vector<std::shared_ptr<Texture>>& textures);
	void Reset();

	void Render(const std::vector<std::shared_ptr<Sprite>>& blocks) const;
	void Update();

	//TODO Replace with more specific (lifetime-aware) versions
	void AddEntity(std::shared_ptr<Entity> pEntity);
	void AddGameEntity(std::shared_ptr<Entity> pEntity);
	
	void AddDebris(const Vector2& pos);
	
	void ExplodeAllEntititiesExceptPlayer();

	void OnPlayerEnter();
	void OnPlayerExit();

	// Mission Accomplished stuff
	void AddExplosion();

#ifdef _DEBUG
	std::vector<std::shared_ptr<Entity>>& GetEntities() { return m_entities; }
#endif	// #ifdef _DEBUG

private:
	void AddObstacle(int row, int column, int left, int top, int right, int bottom);
	bool OverlapsObstacles(std::shared_ptr<Entity> pEntity, float x, float y) const;
	
	std::shared_ptr<Entity> CreateEntity(int type, const Vector2& vInitialPos, const std::vector<std::shared_ptr<Texture>>& textures);

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

	//////////////////////////////////////////////////////////////////////////
	int m_block[ROWS][COLUMNS];

	std::vector<std::shared_ptr<Entity>>	m_entities;
	std::vector<std::shared_ptr<Entity>>	m_entitiesToAdd;
	
	using Obstacles = std::vector<RECT>;
	Obstacles	m_obstacles;
};


#endif	// #ifndef __ROOM_H
