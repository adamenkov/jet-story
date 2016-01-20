#ifndef __ITEMS_H
#define __ITEMS_H

#pragma once

#include "Entity.h"
#include "Player.h"


class RandomCollectible : public Entity
{
public:
	RandomCollectible(const Vec2& vInitialPos);

	virtual void OnCollision(Player& player);

	virtual bool CollidesWithPlayer() const { return true; }

protected:
	void CollectFuel    (Player& player);
	void CollectAmmo    (Player& player);
	void CollectBombs   (Player& player);
	void CollectMissiles(Player& player);
	void CollectBalls   (Player& player);
	void CollectShield  (Player& player);
	void CollectStars   (Player& player);
};


class Fuel : public RandomCollectible
{
public:
	Fuel(const Vec2& vInitialPos) : RandomCollectible(vInitialPos) {}

	virtual void OnCollision(Player& player);
};


class Ammo : public RandomCollectible
{
public:
	Ammo(const Vec2& vInitialPos) : RandomCollectible(vInitialPos) {}

	virtual void OnCollision(Player& player);
};


class Bombs : public RandomCollectible
{
public:
	Bombs(const Vec2& vInitialPos) : RandomCollectible(vInitialPos) {}

	virtual void OnCollision(Player& player);
};


class Missiles : public RandomCollectible
{
public:
	Missiles(const Vec2& vInitialPos) : RandomCollectible(vInitialPos) {}

	virtual void OnCollision(Player& player);
};


class Balls : public RandomCollectible
{
public:
	Balls(const Vec2& vInitialPos) : RandomCollectible(vInitialPos) {}

	virtual void OnCollision(Player& player);
};


class Shield : public RandomCollectible
{
public:
	Shield(const Vec2& vInitialPos) : RandomCollectible(vInitialPos) {}

	virtual void OnCollision(Player& player);
};


class Stars : public RandomCollectible
{
public:
	Stars(const Vec2& vInitialPos) : RandomCollectible(vInitialPos) {}

	virtual void OnCollision(Player& player);
};


#endif	// #ifndef __ITEMS_H
