#ifndef __PROJECTILES_H
#define __PROJECTILES_H

#pragma once

#include "Enemies.h"
#include "Entity.h"
#include "Player.h"

class Cannon;


class Explosion : public Entity
{
public:
	Explosion(const Vec2& vInitialPos);

private:
	Texture m_texture;
};


class Debris : public Entity
{
public:
	Debris(const Vec2& vInitialPos);

	virtual void Render() const;
	virtual bool IsMovable() const		{ return true; }
	virtual Vec2 GetSteering() const	{ return Vec2(0.f, 0.16f); }
};


class HorizontalWave : public Entity
{
public:
	HorizontalWave(Cannon* pCannon, const Vec2& vInitialPos, bool bLeft);
	HorizontalWave(Radar* pRadar, const Vec2& vInitialPos, bool bLeft);

	virtual void Render() const;
	virtual void SetGarbage();

	virtual void OnCollision(Player& player);
	virtual void OnCollision(bool bHorizontal, bool bVertical);

private:
	Cannon* m_pCannon;
	Radar* m_pRadar;
};


class Wave : public Entity
{
public:
	Wave(Radar* pRadar, const Vec2& vInitialPos, const Vec2& vel);

	virtual void Render() const;
	virtual void SetGarbage();

	virtual void OnCollision(Player& player);
	virtual void OnCollision(bool bHorizontal, bool bVertical);

private:
	Radar* m_pRadar;
};


class Radiation : public Entity
{
public:
	Radiation(const Vec2& vInitialPos, bool bLeft);

	virtual void OnCollision(Player& player);
	virtual void OnCollision(bool bHorizontal, bool bVertical);

private:
	Texture m_texture;
};


// MUST BE ENEMY (WITH SCORE), NOT A PROJECTILE
class VerticalRocket : public Entity
{
public:
	VerticalRocket(const Vec2& vInitialPos);

	virtual void OnCollision(Player& player);
	virtual void OnCollision(bool bHorizontal, bool bVertical);

private:
	Texture m_texture;
};


// MUST BE ENEMY (WITH SCORE), NOT A PROJECTILE
class Bomb : public Entity
{
public:
	Bomb(const Vec2& vInitialPos);

	virtual void OnCollision(Player& player);
	virtual void OnCollision(bool bHorizontal, bool bVertical);
	virtual void Update() { m_vel.y += 0.01f; }

private:
	Bomber* m_pBomber;
	Texture m_texture;
};


class PlayerBullet : public Entity
{
public:
	PlayerBullet(const Vec2& vInitialPosition);

	virtual void Render() const { Engine::DrawText(m_pos + Vec2(0.f, -3.f), Engine::eC_White, "`"); }
	virtual void SetGarbage() { Entity::SetGarbage(); Player::GetPlayer().OnNoPlayerBullet(); }
	virtual bool IsMovable() const { return true; }
	virtual void OnCollision(bool UNUSED_PARAM(bHorizontal), bool UNUSED_PARAM(bVertical)) { SetGarbage(); }
	virtual bool CollidesWithEnemy() const { return true; }
	virtual void OnCollision(Enemy& enemy);
};


class PlayerBomb : public Entity
{
public:
	PlayerBomb();
	
	virtual void SetGarbage() { Entity::SetGarbage(); Player::GetPlayer().OnNoPlayerBomb(); }
	virtual bool IsMovable() const { return true; }
	virtual bool CollidesWithEnemy() const { return true; }
	virtual void SetPosNearPlayer() = 0;
};


class PlayerBall : public PlayerBomb
{
public:
	PlayerBall();
	
	virtual void Render() const;
	virtual void OnCollision(bool bHorizontal, bool bVertical);
	virtual void OnCollision(Enemy& enemy) { enemy.Explode(); }
	virtual void OnTimer() { SetGarbage(); }
	virtual void SetPosNearPlayer() { SetPos(Player::GetPlayer().GetPos() + Vec2(12.f, 0.f)); }
};


class PlayerVerticalBomb : public PlayerBomb
{
public:
	virtual void Render() const { Engine::DrawText(m_pos, Engine::eC_LightCyan, "c"); }
	virtual void Update();
	virtual void OnCollision(bool UNUSED_PARAM(bHorizontal), bool UNUSED_PARAM(bVertical)) { SetGarbage(); }
	virtual void OnCollision(Enemy& enemy);
	virtual void SetPosNearPlayer() { SetPos(Player::GetPlayer().GetPos() + Vec2(12.f, 8.f)); }
};


class PlayerHorizontalBomb : public PlayerBomb
{
public:
	PlayerHorizontalBomb(bool bLeft) : m_bLeft(bLeft) {}

	virtual void Render() const { Engine::DrawText(m_pos, Engine::eC_LightCyan, m_bLeft ? "b" : "a"); }
	virtual void Update();
	virtual void OnCollision(bool UNUSED_PARAM(bHorizontal), bool UNUSED_PARAM(bVertical)) { SetGarbage(); }
	virtual void OnCollision(Enemy& enemy);
	virtual void SetPosNearPlayer() { SetPos(Player::GetPlayer().GetPos() + Vec2(12.f, 8.f)); }

private:
	bool m_bLeft;
};


class PlayerStar : public PlayerBomb
{
public:
	PlayerStar();

	virtual void Render() const;
	virtual void Update();
	virtual void OnCollision(bool bHorizontal, bool bVertical);
	virtual void OnCollision(Enemy& enemy) { enemy.Explode(); }
	virtual void OnTimer() { SetGarbage(); }
	virtual void SetPosNearPlayer() { SetPos(Player::GetPlayer().GetPos() + Vec2(12.f, 0.f)); }
};


#endif	// #ifndef __PROJECTILES_H
