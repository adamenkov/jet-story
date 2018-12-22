#ifndef __ENEMIES_H
#define __ENEMIES_H

#pragma once

#include "Entity.h"
#include "../Shared/Engine.h"


class Enemy : public Entity
{
public:
	Enemy(const Vector2& vInitialPos) : Entity(vInitialPos) {}
	
	virtual void Reset() override;
	virtual bool IsMovable() const override { return true; }
	virtual bool IsEnemy() const override { return true; }
	virtual bool CollidesWithPlayer() const override { return true; }
	virtual void OnCollision(std::shared_ptr<Player> player) override;

	virtual bool OnBulletHit();

protected:
	int		m_health;
};


class DualCannon : public Enemy
{
public:
	DualCannon(const Vector2& vInitialPos);

	virtual void Reset() override;
	virtual void Move();
	virtual int GetScore() const override { return 90; }
};


class Platform : public Enemy
{
public:
	Platform(const Vector2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset() override;
	virtual void Explode() override;
	virtual void OnCollision(std::shared_ptr<Player> player) override;
	virtual void Move();
	virtual int GetScore() const override { return 90; }
};


class Platform2 : public Enemy
{
public:
	Platform2(const Vector2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset() override;
	virtual void Explode() override;
	virtual void OnCollision(std::shared_ptr<Player> player) override;
	virtual void Move();
	virtual int GetScore() const override { return 90; }
};


class BigBall : public Enemy
{
public:
	BigBall(const Vector2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset() override;
	virtual void Move();
	virtual int GetScore() const override { return 90; }
};


class Globe : public Enemy
{
public:
	Globe(const Vector2& vInitialPos);

	virtual void Reset() override;
	virtual void Move();
	virtual int GetScore() const override { return 30; }
};


class Medusa : public Enemy
{
public:
	Medusa(const Vector2& vInitialPos);

	virtual void Reset() override;
	virtual void Move();
	virtual int GetScore() const override { return 25; }
};


class Revolver : public Enemy
{
public:
	Revolver(const Vector2& vInitialPos);

	virtual void Reset() override;
	virtual void Move();
	virtual int GetScore() const override { return 25; }
};


class BigZ : public Enemy
{
public:
	BigZ(const Vector2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset() override;
	virtual void Animate() override;
	virtual void Move();
	virtual int GetScore() const override { return 10; }
};


class Cannon : public Enemy
{
public:
	Cannon(const Vector2& vInitialPos) : Enemy(vInitialPos), m_bBusy(false) {}

	virtual void Reset() override;
	virtual void Animate() override;
	virtual void Update() override;
	virtual int GetScore() const override { return 30; }

	void SetBusy(bool bBusy) { m_bBusy = bBusy; }

private:
	bool	m_bBusy;
};


class FlyingCannon : public Cannon
{
public:
	FlyingCannon(const Vector2& vInitialPos);

	virtual void Reset() override;
	virtual void Animate() override;
	virtual void Move();
	virtual int GetScore() const override { return 40; }
};


class Flier : public Enemy
{
public:
	Flier(const Vector2& vInitialPos);

	virtual void Reset() override;
	virtual void Animate() override;
	virtual void Move();
	virtual int GetScore() const override { return 50; }
};


class Flier2 : public Enemy
{
public:
	Flier2(const Vector2& vInitialPos);

	virtual void Reset() override;
	virtual void Animate() override;
	virtual void Move();
	virtual int GetScore() const override { return 75; }
};


class RevolvingRadar : public Enemy
{
public:
	RevolvingRadar(const Vector2& vInitialPos);

	virtual void Reset() override;
	virtual int GetScore() const override { return 95; }
};


class RocketLauncher : public Enemy
{
public:
	RocketLauncher(const Vector2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset() override;
	virtual void Update() override;
	virtual int GetScore() const override { return 75; }
};


class LeftRocket : public Enemy
{
public:
	LeftRocket(const Vector2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset() override;
	virtual int GetScore() const override { return 30; }
};


class RightRocket : public Enemy
{
public:
	RightRocket(const Vector2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset() override;
	virtual int GetScore() const override { return 30; }
};


class Brick : public Enemy
{
public:
	Brick(const Vector2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset() override;
	virtual int GetScore() const override { return 50; }
};


class Factory : public Enemy
{
public:
	Factory(const Vector2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset() override;
	virtual int GetScore() const override { return 75; }
};


class Bomber : public Enemy
{
public:
	Bomber(const Vector2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset() override;
	virtual void Update() override;
	virtual int GetScore() const override { return 45; }
};


class Rocket : public Enemy
{
public:
	Rocket(const Vector2& vInitialPos);

	virtual void Reset() override;
	virtual int GetScore() const override { return 95; }
};


class Radiator : public Enemy
{
public:
	Radiator(const Vector2& vInitialPos, bool bLeft) : Enemy(vInitialPos), m_bLeft(bLeft) {}

	virtual void Reset() override;
	virtual void Update() override;
	virtual int GetScore() const override { return 50; }

private:
	Radiator& operator=(const Radiator&);

	const bool m_bLeft;
};


class Radar : public Enemy
{
public:
	Radar(const Vector2& vInitialPos) : Enemy(vInitialPos), m_bBusy(false) {}

	virtual void Reset() override;
	virtual void Update() override;
	virtual int GetScore() const override { return 50; }

	void SetBusy(bool bBusy) { m_bBusy = bBusy; }

private:
	bool m_bBusy;
};


class Base : public Enemy
{
public:
	Base(const Vector2& vInitialPos) : Enemy(vInitialPos) {}

	virtual void Reset() override;
	virtual void Explode() override;
	virtual int GetScore() const override { return 4000; }
};


#endif	// #ifndef __ENEMIES_H
