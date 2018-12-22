#ifndef __ITEMS_H
#define __ITEMS_H

#pragma once

#include "Entity.h"
#include "Player.h"


class RandomCollectible : public Entity
{
public:
	RandomCollectible(const Vector2& vInitialPos);

	virtual void OnCollision(std::shared_ptr<Player> player) override;

	virtual bool CollidesWithPlayer() const override { return true; }

protected:
	void CollectFuel    (std::shared_ptr<Player> player);
	void CollectAmmo    (std::shared_ptr<Player> player);
	void CollectBombs   (std::shared_ptr<Player> player);
	void CollectMissiles(std::shared_ptr<Player> player);
	void CollectBalls   (std::shared_ptr<Player> player);
	void CollectShield  (std::shared_ptr<Player> player);
	void CollectStars   (std::shared_ptr<Player> player);
};


class Fuel : public RandomCollectible
{
public:
	Fuel(const Vector2& vInitialPos) : RandomCollectible(vInitialPos) {}

	virtual void OnCollision(std::shared_ptr<Player> player) override;
};


class Ammo : public RandomCollectible
{
public:
	Ammo(const Vector2& vInitialPos) : RandomCollectible(vInitialPos) {}

	virtual void OnCollision(std::shared_ptr<Player> player) override;
};


class Bombs : public RandomCollectible
{
public:
	Bombs(const Vector2& vInitialPos) : RandomCollectible(vInitialPos) {}

	virtual void OnCollision(std::shared_ptr<Player> player) override;
};


class Missiles : public RandomCollectible
{
public:
	Missiles(const Vector2& vInitialPos) : RandomCollectible(vInitialPos) {}

	virtual void OnCollision(std::shared_ptr<Player> player) override;
};


class Balls : public RandomCollectible
{
public:
	Balls(const Vector2& vInitialPos) : RandomCollectible(vInitialPos) {}

	virtual void OnCollision(std::shared_ptr<Player> player) override;
};


class Shield : public RandomCollectible
{
public:
	Shield(const Vector2& vInitialPos) : RandomCollectible(vInitialPos) {}

	virtual void OnCollision(std::shared_ptr<Player> player) override;
};


class Stars : public RandomCollectible
{
public:
	Stars(const Vector2& vInitialPos) : RandomCollectible(vInitialPos) {}

	virtual void OnCollision(std::shared_ptr<Player> player) override;
};


#endif	// #ifndef __ITEMS_H
