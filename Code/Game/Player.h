#ifndef __PLAYER_H
#define __PLAYER_H

#pragma once

#include "Entity.h"

class PlayerBomb;


class Player : public Entity
{
	Player();
	Player(const Player&);
	Player& operator=(const Player&);

public:
	static Player& GetPlayer();

	virtual void Reset();

	virtual void Update();

	virtual void Animate();
	virtual void Render() const;

	virtual bool IsMovable() const { return true; }
	virtual Vector2 GetSteering() const;
	virtual void OnCollision(bool bHorizontal, bool bVertical);

	
	void	Refuel()		{ m_nFuel = GetMaxFuel(); }
	void	ConsumeFuel()	{ --m_nFuel; }
	int		GetFuel() const { return m_nFuel; }
	int		GetMaxFuel() const { return 8192; }

	void	RestoreShield()		{ m_nShield = GetMaxShield(); }
	void	ConsumeShield(int nUnits = 2);
	int		GetShield() const	{ return m_nShield; }
	int		GetMaxShield() const { return 114; }

	void	ResetScore()		{ m_nScore = 0; }
	void	AddScore(int score)	{ m_nScore += score; }
	int		GetScore() const	{ return m_nScore; }

	void	RestoreAmmo()		{ m_nAmmo = GetMaxAmmo(); }
	int		GetAmmo() const		{ return m_nAmmo; }
	int		GetMaxAmmo() const	{ return 255; }

	char	GetBombsType() const { return m_cBombsType; }
	void	SetBombsType(char cBombsType) { m_cBombsType = cBombsType; }
	
	int		GetBombs() const	{ return m_nBombs; }
	void	SetBombs(int nBombs) { m_nBombs = nBombs; }

	void	OnNoPlayerBomb()	{ m_pPlayerBomb = NULL; }
	void	OnNoPlayerBullet()	{ --m_nPlayerBullets; }

	void	OnRoomChanged();

private:
	Texture m_texture;

	Sprite	m_spriteJetDownBigLeft;
	Sprite	m_spriteJetDownBigRight;
	Sprite	m_spriteJetDownSmallLeft;
	Sprite	m_spriteJetDownSmallRight;
	Sprite	m_spriteJetLeft;
	Sprite	m_spriteJetRight;

	Texture	m_textureJetDownBigLeft;
	Texture m_textureJetDownBigRight;
	Texture m_textureJetDownSmallLeft;
	Texture m_textureJetDownSmallRight;
	Texture m_textureJetLeft;
	Texture m_textureJetRight;

	int		m_nFuel;
	int		m_nAmmo;

	char	m_cBombsType;
	int		m_nBombs;

	int		m_nShield;
	int		m_nScore;

	long int m_frameIDBulletSpawned;
	long int m_frameIDBombSpawned;

	PlayerBomb*	m_pPlayerBomb;
	int		m_nPlayerBullets;
};


#endif	// #ifndef __PLAYER_H
