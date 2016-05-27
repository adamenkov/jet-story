#ifndef __ENTITY_H
#define __ENTITY_H

#pragma once

#define _USING_V110_SDK71_ 1

#include <vector>
#include "../Shared/Engine.h"

class Enemy;
class Player;


class Entity : public Sprite
{
public:
	Entity(const Vector2& vInitialPos);

	virtual void Reset();

	virtual void Update();

	virtual void Animate();

	enum ELifeTime	// From more to less persistent
	{
		eLT_Game,		// Removed only on application exit
		eLT_Session,	// Removed on new game start (e.g. spawned new flyers)
		eLT_FollowPlayer,// Not removed when the player leaves the room (player ball/star)
		eLT_Room,		// Removed when the player leaves the room (e.g. radiation)
		eLT_Collision,	// Removed on collision with walls (e.g. debris)
		eLT_Animation,	// Removed after its animation has been played (e.g. explosion)
		eLT_Garbage		// Remove ASAP
	};
	ELifeTime	GetLifeTime() const { return m_eLifeTime; }
	void		SetLifeTime(ELifeTime eLifeTime) { m_eLifeTime = eLifeTime; }

	bool		IsGarbage() const { return m_eLifeTime == eLT_Garbage; }
	virtual void SetGarbage() { m_eLifeTime = eLT_Garbage; }

	bool		IsEnabled() const { return m_bEnabled; }
	void		Disable() { m_bEnabled = false; }

	virtual void Explode();
	void		ForceExplode() { Explode(); }	// "Mission Accomplished" stuff

	virtual bool IsMovable() const { return false; }
	virtual Vector2 GetSteering() const { return Vector2(ZERO); }

	Vector2		GetVelocity() const { return m_vel; }
	void		SetVelocity(const Vector2& vel) { m_vel = vel; }
	void		SetVelocity(float x, float y) { m_vel.x = x; m_vel.y = y; }

	void		SetTimer(int timer) { m_timer = timer; }
	bool		IsTime() const { return m_timer <= 0; }
	virtual void OnTimer() {}

	Entity*		GetPlatform() const { return m_pPlatform; }
	void		SetPlatform(Entity* pPlatform) { m_pPlatform = pPlatform; }

	//////////////////////////////////////////////////////////////////////////
	virtual void OnCollision(bool UNUSED_PARAM(bHorizontal), bool UNUSED_PARAM(bVertical)) {}

	virtual	bool IsEnemy() const { return false; }
	virtual bool CollidesWithEnemy() const { return false; }
	virtual void OnCollision(Enemy& UNUSED_PARAM(enemy)) {}

	virtual bool CollidesWithPlayer() const { return false; }
	virtual void OnCollision(Player& UNUSED_PARAM(player)) {}

	virtual int GetScore() const { return 0; }

protected:
	ELifeTime	m_eLifeTime;

	Vector2		m_vInitialPos;
	
	Vector2		m_vel;	// pixels per frame

	bool		m_bEnabled;

	int			m_timer;

	Entity*		m_pPlatform;
};


typedef	std::vector<Entity*>	Entities;


#endif	// #ifndef __ENTITY_H
