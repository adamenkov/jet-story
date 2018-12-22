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
	Explosion(const Vector2& vInitialPos);

private:
	std::shared_ptr<Texture> m_texture;
};


class Debris : public Entity
{
public:
	Debris(const Vector2& vInitialPos);

	virtual void Render() const;
	virtual bool IsMovable() const override { return true; }
	virtual Vector2 GetSteering() const	override { return Vector2(0.f, 0.16f); }
};


class HorizontalWave : public Entity
{
public:
	HorizontalWave(Cannon* pCannon, const Vector2& vInitialPos, bool bLeft);
	HorizontalWave(Radar* pRadar, const Vector2& vInitialPos, bool bLeft);

	virtual void Render() const;
	virtual void SetGarbage() override;

	virtual void OnCollision(Player& player);
	virtual void OnCollision(bool bHorizontal, bool bVertical) override;

private:
	Cannon* m_pCannon;
	Radar* m_pRadar;
};


class Wave : public Entity
{
public:
	Wave(Radar* pRadar, const Vector2& vInitialPos, const Vector2& vel);

	virtual void Render() const;
	virtual void SetGarbage();

	virtual void OnCollision(Player& player);
	virtual void OnCollision(bool bHorizontal, bool bVertical) override;

private:
	Radar* m_pRadar;
};


class Radiation : public Entity
{
public:
	Radiation(const Vector2& vInitialPos, bool bLeft);

	virtual void OnCollision(Player& player);
	virtual void OnCollision(bool bHorizontal, bool bVertical) override;

private:
	std::shared_ptr<Texture> m_texture;
};


// MUST BE ENEMY (WITH SCORE), NOT A PROJECTILE
class VerticalRocket : public Entity
{
public:
	VerticalRocket(const Vector2& vInitialPos);

	virtual void OnCollision(Player& player);
	virtual void OnCollision(bool bHorizontal, bool bVertical) override;

private:
	std::shared_ptr<Texture> m_texture;
};


// MUST BE ENEMY (WITH SCORE), NOT A PROJECTILE
class Bomb : public Entity
{
public:
	Bomb(const Vector2& vInitialPos);

	virtual void OnCollision(Player& player);
	virtual void OnCollision(bool bHorizontal, bool bVertical) override;
	virtual void Update() { m_vel.y += 0.01f; }

private:
	Bomber* m_pBomber;
	std::shared_ptr<Texture> m_texture;
};


class PlayerBullet : public Entity
{
public:
	PlayerBullet(const Vector2& vInitialPosition);

	virtual void Render() const { Engine::DrawText(GetPos() + Vector2(0.f, -3.f), EColor::White, "`"); }
	virtual void SetGarbage() override { Entity::SetGarbage(); Player::GetPlayer()->OnNoPlayerBullet(); }
	virtual bool IsMovable() const override { return true; }
	virtual void OnCollision(bool UNUSED_PARAM(bHorizontal), bool UNUSED_PARAM(bVertical)) override { SetGarbage(); }
	virtual bool CollidesWithEnemy() const override { return true; }
	virtual void OnCollision(Enemy& enemy);
};


class PlayerBomb : public Entity
{
public:
	PlayerBomb();
	
	virtual void SetGarbage() override { Entity::SetGarbage(); Player::GetPlayer()->OnNoPlayerBomb(); }
	virtual bool IsMovable() const override { return true; }
	virtual bool CollidesWithEnemy() const override { return true; }
	virtual void SetPosNearPlayer() = 0;
};


class PlayerBall : public PlayerBomb
{
public:
	PlayerBall();
	
	virtual void Render() const;
	virtual void OnCollision(bool bHorizontal, bool bVertical) override;
	virtual void OnCollision(Enemy& enemy) { enemy.Explode(); }
	virtual void OnTimer() override { SetGarbage(); }
	virtual void SetPosNearPlayer() { SetPos(Player::GetPlayer()->GetPos() + Vector2(12.f, 0.f)); }
};


class PlayerVerticalBomb : public PlayerBomb
{
public:
	virtual void Render() const { Engine::DrawText(GetPos(), EColor::LightCyan, "c"); }
	virtual void Update();
	virtual void OnCollision(bool UNUSED_PARAM(bHorizontal), bool UNUSED_PARAM(bVertical)) override { SetGarbage(); }
	virtual void OnCollision(Enemy& enemy);
	virtual void SetPosNearPlayer() { SetPos(Player::GetPlayer()->GetPos() + Vector2(12.f, 8.f)); }
};


class PlayerHorizontalBomb : public PlayerBomb
{
public:
	PlayerHorizontalBomb(bool bLeft) : m_bLeft(bLeft) {}

	virtual void Render() const { Engine::DrawText(GetPos(), EColor::LightCyan, m_bLeft ? "b" : "a"); }
	virtual void Update();
	virtual void OnCollision(bool UNUSED_PARAM(bHorizontal), bool UNUSED_PARAM(bVertical)) override { SetGarbage(); }
	virtual void OnCollision(Enemy& enemy);
	virtual void SetPosNearPlayer() { SetPos(Player::GetPlayer()->GetPos() + Vector2(12.f, 8.f)); }

private:
	bool m_bLeft;
};


class PlayerStar : public PlayerBomb
{
public:
	PlayerStar();

	virtual void Render() const;
	virtual void Update();
	virtual void OnCollision(bool bHorizontal, bool bVertical) override;
	virtual void OnCollision(Enemy& enemy) { enemy.Explode(); }
	virtual void OnTimer() override { SetGarbage(); }
	virtual void SetPosNearPlayer() { SetPos(Player::GetPlayer()->GetPos() + Vector2(12.f, 0.f)); }
};


#endif	// #ifndef __PROJECTILES_H
