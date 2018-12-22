#include "Enemies.h"
#include "../Shared/Engine.h"
#include "../Shared/Game.h"
#include "Debug.h"
#include "Maze.h"
#include "Player.h"
#include "Projectiles.h"


void Enemy::Reset()
{
	Entity::Reset();

	EColor eColor = static_cast<EColor>
		(static_cast<int>(EColor::eC_LightBlue) + (rand() % (static_cast<int>(EColor::eC_White) - static_cast<int>(EColor::eC_LightBlue) + 1)));

	SetColor(eColor);
	
	if (m_pPlatform)
	{
		m_pPlatform->SetColor(eColor);
	}
}


void Enemy::OnCollision(Player& player)
{
	if ((Engine::GetFrameID() % 3) == 0)
	{
		player.ConsumeShield();
		OnBulletHit();
	}
}


bool Enemy::OnBulletHit()
{
	if (--m_health <= 0)
	{
		Explode();
	}
	return true;
}


DualCannon::DualCannon(const Vector2& vInitialPos) :
	Enemy(vInitialPos)
{
	SetFrameTimer(2);
}


void DualCannon::Reset()
{
	Enemy::Reset();
	m_health = 3;
}


void DualCannon::Move()
{
	if (IsTime())
	{
		m_vel.Set((-10.f + (rand() % 20)) / 10.f, (-10.f + (rand() % 20)) / 10.f);
		SetTimer(rand() % 100);
	}
}


void Platform::Reset()
{
	Enemy::Reset();
	m_health = 1;
}


void Platform::Explode()
{
	m_bEnabled = false;
	Player::GetPlayer()->AddScore(GetScore());
	Maze::GetMaze()->AddEntity(std::make_shared<Explosion>(m_pos + Vector2(0.f, 16.f)));
}


void Platform::OnCollision(Player& player)
{
	if (player.GetPos().y > m_pos.y)
	{
		Enemy::OnCollision(player);
	}
}


void Platform::Move()
{
	if (IsTime())
	{
		m_vel.Set((-10.f + (rand() % 20)) / 10.f, (-10.f + (rand() % 20)) / 10.f);
		SetTimer(rand() % 100);
	}
}


void Platform2::Reset()
{
	Enemy::Reset();
	m_health = 1;
}


void Platform2::Explode()
{
	m_bEnabled = false;
	Player::GetPlayer()->AddScore(GetScore());
	Maze::GetMaze()->AddEntity(std::make_shared<Explosion>(m_pos + Vector2(0.f, 16.f)));
}


void Platform2::OnCollision(Player& player)
{
	if (player.GetPos().y > m_pos.y)
	{
		Enemy::OnCollision(player);
	}
}


void Platform2::Move()
{
	if (IsTime())
	{
		m_vel.Set((-10.f + (rand() % 20)) / 10.f, (-10.f + (rand() % 20)) / 10.f);
		SetTimer(rand() % 100);
	}
}


void BigBall::Reset()
{
	Enemy::Reset();
	m_health = 4;
}


void BigBall::Move()
{
	if (IsTime())
	{
		m_vel.Set((-10.f + (rand() % 20)) / 10.f, (-10.f + (rand() % 20)) / 10.f);
		SetTimer(rand() % 100);
	}
}


Globe::Globe(const Vector2& vInitialPos) :
	Enemy(vInitialPos)
{
	SetFrameTimer(4);
}


void Globe::Reset()
{
	Enemy::Reset();
	m_health = 1;
}


void Globe::Move()
{
	if (IsTime())
	{
		m_vel.Set((-10.f + (rand() % 20)) / 10.f, (-10.f + (rand() % 20)) / 10.f);
		SetTimer(rand() % 100);
	}
}


Medusa::Medusa(const Vector2& vInitialPos) :
	Enemy(vInitialPos)
{
	SetFrameTimer(4);
}

void Medusa::Reset()
{
	Enemy::Reset();
	m_health = 1;
}


void Medusa::Move()
{
	if (IsTime())
	{
		//m_acc.Set((-Debug::A + (rand() % int(2 * Debug::A))) / 100.f, (-Debug::A + (rand() % int(2 * Debug::A))) / 100.f);
		//TODO Move to GetSteering()
		SetTimer(rand() % int(Debug::B));
	}
}


Revolver::Revolver(const Vector2& vInitialPos) :
	Enemy(vInitialPos)
{
	SetFrameTimer(4);
}


void Revolver::Reset()
{
	Enemy::Reset();
	m_health = 1;
}


void Revolver::Move()
{
	if (IsTime())
	{
		m_vel.Set((-10.f + (rand() % 20)) / 10.f, (-10.f + (rand() % 20)) / 10.f);
		SetTimer(rand() % 100);
	}
}


void BigZ::Reset()
{
	Enemy::Reset();
	m_health = 1;
}


void BigZ::Animate()
{
	Enemy::Animate();
	SetAnimationFrame((Player::GetPlayer()->GetPos().x >= m_pos.x) ? 0 : 1);
}


void BigZ::Move()
{
	if (IsTime())
	{
		m_vel.Set((-10.f + (rand() % 20)) / 10.f, (-10.f + (rand() % 20)) / 10.f);
		SetTimer(rand() % 100);
	}
}


void Cannon::Reset()
{
	Enemy::Reset();
	m_health = 3;
	m_bBusy = false;
}


void Cannon::Animate()
{
	Enemy::Animate();

	bool bLeft = Player::GetPlayer()->GetPos().x < m_pos.x;
	SetAnimationFrame(bLeft ? 1 : 0);
}


void Cannon::Update()
{
	Enemy::Update();

	//Player& player = Player::GetPlayer();
	//bool bLeft = player.GetPos().x < m_pos.x;

	if (!m_bBusy && ((rand() % 200) == 0))
	{
		/*
		if (player.OverlapsHorizontally(this))
		{
			m_bBusy = true;

			Vector2 pos = m_pos;
			if (bLeft)
			{
				pos += Vector2(-7.f, 6.f);
			}
			else
			{
				pos += Vector2(16.f, 6.f);
			}

			Maze::GetMaze()->AddEntity(new HorizontalWave(this, pos, bLeft));
		}
		*/
	}
}


FlyingCannon::FlyingCannon(const Vector2& vInitialPos) : Cannon(vInitialPos)
{
	SetFrameTimer(2);
}


void FlyingCannon::Reset()
{
	Cannon::Reset();
	m_health = 1;
}


void FlyingCannon::Animate()
{
	Enemy::Animate();

	if ((Player::GetPlayer()->GetPos().x >= m_pos.x))
	{
		if (m_iAnimationFrame == 2)
		{
			SetAnimationFrame(0);
		}
	}
	else
	{
		if (m_iAnimationFrame == 0)
		{
			SetAnimationFrame(2);
		}
	}
}


void FlyingCannon::Move()
{
	if (IsTime())
	{
		m_vel.Set((-10.f + (rand() % 20)) / 10.f, (-10.f + (rand() % 20)) / 10.f);
		SetTimer(rand() % 100);
	}
}


Flier::Flier(const Vector2& vInitialPos) :
	Enemy(vInitialPos)
{
	SetFrameTimer(2);
}


void Flier::Reset()
{
	Enemy::Reset();
	m_health = 1;
}


void Flier::Animate()
{
	Enemy::Animate();

	if ((Player::GetPlayer()->GetPos().x >= m_pos.x))
	{
		if (m_iAnimationFrame == 2)
		{
			SetAnimationFrame(0);
		}
	}
	else
	{
		if (m_iAnimationFrame == 0)
		{
			SetAnimationFrame(2);
		}
	}
}

	
void Flier::Move()
{
	if (IsTime())
	{
		m_vel.Set((-10.f + (rand() % 20)) / 10.f, (-10.f + (rand() % 20)) / 10.f);
		SetTimer(rand() % 100);
	}
}


Flier2::Flier2(const Vector2& vInitialPos) :
	Enemy(vInitialPos)
{
	SetFrameTimer(2);
}


void Flier2::Reset()
{
	Enemy::Reset();
	m_health = 1;
}


void Flier2::Animate()
{
	Enemy::Animate();

	if ((Player::GetPlayer()->GetPos().x >= m_pos.x))
	{
		if (m_iAnimationFrame == 2)
		{
			SetAnimationFrame(0);
		}
	}
	else
	{
		if (m_iAnimationFrame == 0)
		{
			SetAnimationFrame(2);
		}
	}
}

	
void Flier2::Move()
{
	if (IsTime())
	{
		m_vel.Set((-10.f + (rand() % 20)) / 10.f, (-10.f + (rand() % 20)) / 10.f);
		SetTimer(rand() % 100);
	}
}


RevolvingRadar::RevolvingRadar(const Vector2& vInitialPos) :
	Enemy(vInitialPos)
{
	SetFrameTimer(4);
}


void RevolvingRadar::Reset()
{
	Enemy::Reset();
	m_health = 9;
}


void RocketLauncher::Reset()
{
	Enemy::Reset();
	m_health = 9;
}


void RocketLauncher::Update()
{
	Enemy::Update();

	if ((rand() % 80) == 0)
	{
		/*
		if (Player::GetPlayer()->OverlapsVertically(make shared from this))
		{
			Vector2 pos = m_pos;
			pos.y -= 12.f;
			Maze::GetMaze()->AddEntity(std::make_shared<VerticalRocket>(pos));
		}
		*/
	}
}


void LeftRocket::Reset()
{
	Enemy::Reset();
	m_health = 2;
}


void RightRocket::Reset()
{
	Enemy::Reset();
	m_health = 2;
}


void Brick::Reset()
{
	Enemy::Reset();
	m_health = 19;
}


void Factory::Reset()
{
	Enemy::Reset();
	m_health = 8;
}


void Bomber::Reset()
{
	Enemy::Reset();
	m_health = 3;
}


void Bomber::Update()
{
	Enemy::Update();

	if ((rand() % 80) == 0)
	{
		/*
		if (Player::GetPlayer()->OverlapsVertically(make shared from this))
		{
			Vector2 pos = m_pos;
			pos.y += 16.f;
			Maze::GetMaze()->AddEntity(std::make_shared<Bomb>(pos));
		}
		*/
	}
}


Rocket::Rocket(const Vector2& vInitialPos) :
	Enemy(vInitialPos)
{
	SetFrameTimer(8);
}


void Rocket::Reset()
{
	Enemy::Reset();
	m_health = 9;
}


void Radiator::Reset()
{
	Enemy::Reset();
	m_health = 6;
}


void Radiator::Update()
{
	Enemy::Update();

	if ((rand() % 50) == 0)
	{
		/*
		if (Player::GetPlayer().OverlapsHorizontally(this))
		{
			Vector2 pos = m_pos;
			pos.x += m_bLeft ? -16.f : 16.f;
			Maze::GetMaze()->AddEntity(new Radiation(pos, m_bLeft));
		}
		*/
	}
}


void Radar::Reset()
{
	Enemy::Reset();
	m_bBusy = false;
	m_health = 9;
}


void Radar::Update()
{
	Enemy::Update();

	//Player& player = Player::GetPlayer();
	//bool bLeft = player.GetPos().x < m_pos.x;

	if (!m_bBusy && ((rand() % 32) == 0))
	{

		m_bBusy = true;

		/*
		if (player.OverlapsHorizontally(this) && ((rand() % 5) == 0))
		{
			bool bLeft = player.GetPos().x < m_pos.x;
			Maze::GetMaze()->AddEntity(new HorizontalWave(this, m_pos + Vector2(4.f, 4.f), bLeft));
		}
		else
		{
			Vector2 posPredicted = player.GetPos() + Vector2(16.f, 2.f) + float(rand() % 50) * player.GetVelocity();
			Vector2 vel = posPredicted - m_pos;
			vel.SetLength(1.f + .3f * float(rand()) / RAND_MAX);
			Maze::GetMaze()->AddEntity(new Wave(this, m_pos + Vector2(4.f, 2.f), vel));
		}
		*/
	}
}


void Base::Reset()
{
	Enemy::Reset();
	m_health = 20;
}


void Base::Explode()
{
	Enemy::Explode();
	Maze::GetMaze()->OnBaseDestroyed();
}


/*
bool Player::OverlapsHorizontally(Entity* pEntity)
{
	UINT my_y = static_cast<UINT>(m_pos.y);
	UINT y = static_cast<UINT>(pEntity->GetPos().y);
	return max(my_y, y) < min(my_y + GetHeight(), y + pEntity->GetHeight());
}


bool Player::OverlapsVertically(Entity* pEntity)
{
	UINT my_x = static_cast<UINT>(m_pos.x);
	UINT x = static_cast<UINT>(pEntity->GetPos().x) - 8;
	return max(my_x, x) < min(my_x + GetWidth(), x + pEntity->GetWidth() + 16);
}
*/
