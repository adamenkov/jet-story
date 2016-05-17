#ifndef __ENEMIES_H
#define __ENEMIES_H

#pragma once

#include "Entity.h"
#include "../Common/Engine.h"


class Enemy : public Entity
{
public:
	Enemy(const Vec2& vInitialPos) : Entity(vInitialPos) {}
	
	virtual void Reset();
	virtual bool IsMovable() const { return true; }
	virtual bool IsEnemy() const { return true; }
	virtual bool CollidesWithPlayer() const { return true; }
	virtual void OnCollision(Player& player);

	virtual bool OnBulletHit();

protected:
	int		m_health;
};


class DualCannon : public Enemy
{
public:
	DualCannon(const Vec2& vInitialPos);

	virtual void Reset();
	virtual void Move();
	virtual int GetScore() const { return 90; }
};


class Platform : public Enemy
{
public:
	Platform(const Vec2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset();
	virtual void Explode();
	virtual void OnCollision(Player& player);
	virtual void Move();
	virtual int GetScore() const { return 90; }
};


class Platform2 : public Enemy
{
public:
	Platform2(const Vec2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset();
	virtual void Explode();
	virtual void OnCollision(Player& player);
	virtual void Move();
	virtual int GetScore() const { return 90; }
};


class BigBall : public Enemy
{
public:
	BigBall(const Vec2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset();
	virtual void Move();
	virtual int GetScore() const { return 90; }
};


class Globe : public Enemy
{
public:
	Globe(const Vec2& vInitialPos);

	virtual void Reset();
	virtual void Move();
	virtual int GetScore() const { return 30; }
};


class Medusa : public Enemy
{
public:
	Medusa(const Vec2& vInitialPos);

	virtual void Reset();
	virtual void Move();
	virtual int GetScore() const { return 25; }
};


class Revolver : public Enemy
{
public:
	Revolver(const Vec2& vInitialPos);

	virtual void Reset();
	virtual void Move();
	virtual int GetScore() const { return 25; }
};


class BigZ : public Enemy
{
public:
	BigZ(const Vec2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset();
	virtual void Animate();
	virtual void Move();
	virtual int GetScore() const { return 10; }
};


class Cannon : public Enemy
{
public:
	Cannon(const Vec2& vInitialPos) : Enemy(vInitialPos), m_bBusy(false) {}

	virtual void Reset();
	virtual void Animate();
	virtual void Update();
	virtual int GetScore() const { return 30; }

	void SetBusy(bool bBusy) { m_bBusy = bBusy; }

private:
	bool	m_bBusy;
};


class FlyingCannon : public Cannon
{
public:
	FlyingCannon(const Vec2& vInitialPos);

	virtual void Reset();
	virtual void Animate();
	virtual void Move();
	virtual int GetScore() const { return 40; }
};


class Flier : public Enemy
{
public:
	Flier(const Vec2& vInitialPos);

	virtual void Reset();
	virtual void Animate();
	virtual void Move();
	virtual int GetScore() const { return 50; }
};


class Flier2 : public Enemy
{
public:
	Flier2(const Vec2& vInitialPos);

	virtual void Reset();
	virtual void Animate();
	virtual void Move();
	virtual int GetScore() const { return 75; }
};


class RevolvingRadar : public Enemy
{
public:
	RevolvingRadar(const Vec2& vInitialPos);

	virtual void Reset();
	virtual int GetScore() const { return 95; }
};


class RocketLauncher : public Enemy
{
public:
	RocketLauncher(const Vec2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset();
	virtual void Update();
	virtual int GetScore() const { return 75; }
};


class LeftRocket : public Enemy
{
public:
	LeftRocket(const Vec2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset();
	virtual int GetScore() const { return 30; }
};


class RightRocket : public Enemy
{
public:
	RightRocket(const Vec2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset();
	virtual int GetScore() const { return 30; }
};


class Brick : public Enemy
{
public:
	Brick(const Vec2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset();
	virtual int GetScore() const { return 50; }
};


class Factory : public Enemy
{
public:
	Factory(const Vec2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset();
	virtual int GetScore() const { return 75; }
};


class Bomber : public Enemy
{
public:
	Bomber(const Vec2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset();
	virtual void Update();
	virtual int GetScore() const { return 45; }
};


class Rocket : public Enemy
{
public:
	Rocket(const Vec2& vInitialPos);

	virtual void Reset();
	virtual int GetScore() const { return 95; }
};


class Radiator : public Enemy
{
public:
	Radiator(const Vec2& vInitialPos, bool bLeft) : Enemy(vInitialPos), m_bLeft(bLeft) {}

	virtual void Reset();
	virtual void Update();
	virtual int GetScore() const { return 50; }

private:
	Radiator& operator=(const Radiator&);

	const bool m_bLeft;
};


class Radar : public Enemy
{
public:
	Radar(const Vec2& vInitialPos) : Enemy(vInitialPos), m_bBusy(false) {}

	virtual void Reset();
	virtual void Update();
	virtual int GetScore() const { return 50; }

	void SetBusy(bool bBusy) { m_bBusy = bBusy; }

private:
	bool m_bBusy;
};


class Base : public Enemy
{
public:
	Base(const Vec2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset();
	virtual void Explode();
	virtual int GetScore() const { return 4000; }
};


#endif	// #ifndef __ENEMIES_H
