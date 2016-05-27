#include "Collectibles.h"
#include "../Shared/Game.h"
#include "Player.h"
#include "Sounds.h"


RandomCollectible::RandomCollectible(const Vec2& vInitialPos) :
	Entity(vInitialPos)
{
	SetFrameTimer(16);
}


void RandomCollectible::OnCollision(Player& player)
{
	switch (rand() % 7)
	{
	case 0:	CollectFuel    (player);		break;
	case 1:	CollectAmmo    (player);		break;
	case 2:	CollectBombs   (player);		break;
	case 3:	CollectMissiles(player);		break;
	case 4:	CollectBalls   (player);		break;
	case 5:	CollectShield  (player);		break;
	case 6:	CollectStars   (player);		break;
	}
}


void RandomCollectible::CollectFuel(Player& player)
{
	player.Refuel();
	m_bEnabled = false;
	Sounds::Play(Sounds::ITEM_COLLECTED);
}


void RandomCollectible::CollectAmmo(Player& player)
{
	player.RestoreAmmo();
	m_bEnabled = false;
	Sounds::Play(Sounds::ITEM_COLLECTED);
}


void RandomCollectible::CollectBombs(Player& player)
{
	player.SetBombsType('c');
	player.SetBombs(50);
	player.RestoreAmmo();
	m_bEnabled = false;
	Sounds::Play(Sounds::ITEM_COLLECTED);
}


void RandomCollectible::CollectMissiles(Player& player)
{
	player.SetBombsType('a');
	player.SetBombs(50);
	player.RestoreAmmo();
	m_bEnabled = false;
	Sounds::Play(Sounds::ITEM_COLLECTED);
}


void RandomCollectible::CollectBalls(Player& player)
{
	player.SetBombsType('l');
	player.SetBombs(20);
	player.RestoreAmmo();
	m_bEnabled = false;
	Sounds::Play(Sounds::ITEM_COLLECTED);
}


void RandomCollectible::CollectShield(Player& player)
{
	player.RestoreShield();
	m_bEnabled = false;
	Sounds::Play(Sounds::ITEM_COLLECTED);
}


void RandomCollectible::CollectStars(Player& player)
{
	player.SetBombsType('f');
	player.SetBombs(20);
	player.RestoreAmmo();
	m_bEnabled = false;
	Sounds::Play(Sounds::ITEM_COLLECTED);
}


void Fuel::OnCollision(Player& player)
{
	CollectFuel(player);
}


void Ammo::OnCollision(Player& player)
{
	CollectAmmo(player);
}


void Bombs::OnCollision(Player& player)
{
	CollectBombs(player);
}


void Missiles::OnCollision(Player& player)
{
	CollectMissiles(player);
}


void Balls::OnCollision(Player& player)
{
	CollectBalls(player);
}


void Shield::OnCollision(Player& player)
{
	CollectShield(player);
}


void Stars::OnCollision(Player& player)
{
	CollectStars(player);
}
