#include "Projectiles.h"
#include "../Shared/Engine.h"
#include "../Shared/Game.h"
#include "Enemies.h"
#include "Maze.h"
#include "Player.h"
#include "Sounds.h"


const float PI = 3.141592659f;


Explosion::Explosion(const Vector2& vInitialPos) :
	Entity(vInitialPos),
	m_texture("Assets/Projectiles/Explosion.png")
{
	SetFrameTimer(2);
	SetTexture(&m_texture, 16);
	m_eLifeTime = eLT_Animation;
	Audio::Play(Sounds::EXPLOSION);	// present even if sounds are off
}


Debris::Debris(const Vector2& vInitialPos) : Entity(vInitialPos)
{
	m_nWidth = 8;
	m_nHeight = 8;

	SetFrameTimer(1);
	m_nAnimationFrames = 10;
	m_nAnimationFrame = rand() % m_nAnimationFrames;
	
	m_eLifeTime = eLT_Collision;

	float angle = float(rand()) / (RAND_MAX + 1) * 2.f * PI;
	float speed = float(rand()) / (RAND_MAX + 1) * 3.f + 1.f;
	m_vel.x = speed * cos(angle);
	m_vel.y = speed * sin(angle);
}


void Debris::Render() const
{
	Engine::DrawText(m_pos, Engine::eC_White, char(117 + m_nAnimationFrame));
}


HorizontalWave::HorizontalWave(Cannon* pCannon, const Vector2& vInitialPos, bool bLeft) :
	Entity(vInitialPos),
	m_pCannon(pCannon),
	m_pRadar(NULL)
{
	m_vel.x = bLeft ? (-.5f - (rand() / 2.f / (RAND_MAX + 1))) : (.5f + (rand() / 2.f / (RAND_MAX + 1)));

	m_nWidth = 8;
	m_nHeight = 3;
}


HorizontalWave::HorizontalWave(Radar* pRadar, const Vector2& vInitialPos, bool bLeft) :
	Entity(vInitialPos),
	m_pCannon(NULL),
	m_pRadar(pRadar)
{
	m_vel.x = bLeft ? (-.5f - (rand() / 2.f / (RAND_MAX + 1))) : (.5f + (rand() / 2.f / (RAND_MAX + 1)));

	m_nWidth = 8;
	m_nHeight = 3;
}


void HorizontalWave::Render() const
{
	Engine::DrawText(int(m_pos.x), int(m_pos.y) - 3, Engine::eC_Grey, "g");
}


void HorizontalWave::SetGarbage()
{
	Entity::SetGarbage();

	if (m_pCannon)
	{
		m_pCannon->SetBusy(false);
	}
	if (m_pRadar)
	{
		m_pRadar->SetBusy(false);
	}
}


void HorizontalWave::OnCollision(Player& player)
{
	SetGarbage();
	player.ConsumeShield(7);
}


void HorizontalWave::OnCollision(bool UNUSED_PARAM(bHorizontal), bool UNUSED_PARAM(bVertical))
{
	SetGarbage();
}


Wave::Wave(Radar* pRadar, const Vector2& vInitialPos, const Vector2& vel) :
	Entity(vInitialPos),
	m_pRadar(pRadar)
{
	m_vel = vel;

	m_nWidth = 8;
	m_nHeight = 8;
}


void Wave::Render() const
{
	Engine::DrawText(int(m_pos.x), int(m_pos.y), Engine::eC_Grey, "d");
}


void Wave::SetGarbage()
{
	Entity::SetGarbage();
	m_pRadar->SetBusy(false);
}


void Wave::OnCollision(Player& player)
{
	SetGarbage();
	player.ConsumeShield(7);
}


void Wave::OnCollision(bool UNUSED_PARAM(bHorizontal), bool UNUSED_PARAM(bVertical))
{
	SetGarbage();
}


Radiation::Radiation(const Vector2& vInitialPos, bool bLeft) :
	Entity(vInitialPos),
	m_texture("Assets/Projectiles/Radiation.png")
{
	SetFrameTimer(4);
	SetTexture(&m_texture, 16);
	m_vel.x = bLeft ? -2.f : 2.f;
}


void Radiation::OnCollision(Player& player)
{
	SetGarbage();
	player.ConsumeShield(10);
}


void Radiation::OnCollision(bool UNUSED_PARAM(bHorizontal), bool UNUSED_PARAM(bVertical))
{
	SetGarbage();
}


VerticalRocket::VerticalRocket(const Vector2& vInitialPos) :
	Entity(vInitialPos),
	m_texture("Assets/Projectiles/VerticalRocket.bmp")
{
	SetFrameTimer(4);
	SetTexture(&m_texture, 16);
	m_vel.y = -2.f;
}

void VerticalRocket::OnCollision(Player& player)
{
	Maze::GetMaze().AddEntity(new Explosion(m_pos));
	SetGarbage();
	player.ConsumeShield(10);
}


void VerticalRocket::OnCollision(bool UNUSED_PARAM(bHorizontal), bool UNUSED_PARAM(bVertical))
{
	Maze::GetMaze().AddEntity(new Explosion(m_pos));
	SetGarbage();
}


Bomb::Bomb(const Vector2& vInitialPos) :
	Entity(vInitialPos),
	m_texture("Assets/Projectiles/Bomb.bmp")
{
	SetFrameTimer(2);
	SetTexture(&m_texture, 16);
}

void Bomb::OnCollision(Player& player)
{
	Maze::GetMaze().AddEntity(new Explosion(m_pos));
	SetGarbage();
	player.ConsumeShield(10);
}


void Bomb::OnCollision(bool UNUSED_PARAM(bHorizontal), bool UNUSED_PARAM(bVertical))
{
	Maze::GetMaze().AddEntity(new Explosion(m_pos));
	SetGarbage();
}


PlayerBullet::PlayerBullet(const Vector2& vInitialPosition) : Entity(vInitialPosition)
{
	m_nWidth = 7;
	m_nHeight = 2;
}


void PlayerBullet::OnCollision(Enemy& enemy)
{
	enemy.OnBulletHit();
	SetGarbage();
}


PlayerBomb::PlayerBomb() : Entity(Vector2(ZERO))
{
	m_nWidth = 8;
	m_nHeight = 8;
}


PlayerBall::PlayerBall()
{
	SetTimer(512);
	SetFrameTimer(2);
	m_nAnimationFrames = Engine::eC_White - Engine::eC_LightBlack;
}


void PlayerBall::Render() const
{
	Engine::DrawText(
		m_pos,
		(m_timer > 100)
			? Engine::eC_White
			: static_cast<Engine::EColor>(Engine::eC_White - m_nAnimationFrame),
		"l");
}


void PlayerBall::OnCollision(bool bHorizontal, bool bVertical)
{
	if (bHorizontal)
	{
		m_vel.x = -m_vel.x;
	}

	if (bVertical)
	{
		m_vel.y = -m_vel.y;
	}

	Sounds::Play(Sounds::PLAYER_BALL_COLLISION);
}


void PlayerVerticalBomb::Update()
{
	PlayerBomb::Update();

	m_vel.y += .04f;
}


void PlayerVerticalBomb::OnCollision(Enemy& enemy)
{
	enemy.Explode();
	SetGarbage();
}


void PlayerHorizontalBomb::Update()
{
	PlayerBomb::Update();
	
	if (m_vel.x > 0.f)
	{
		m_vel.x += .05f;
		if (m_vel.x > 3.f)
		{
			m_vel.x = 3.f;
		}
	}
	else
	{
		m_vel.x -= .05f;
		if (m_vel.x < -3.f)
		{
			m_vel.x = -3.f;
		}
	}

	m_vel.y -= .03f;
}


void PlayerHorizontalBomb::OnCollision(Enemy& enemy)
{
	enemy.Explode();
	SetGarbage();
}


PlayerStar::PlayerStar()
{
	SetTimer(512);
	SetFrameTimer(2);
	m_nAnimationFrames = Engine::eC_White - Engine::eC_LightBlack;
}


void PlayerStar::Render() const
{
	Engine::DrawText(
		m_pos,
		(m_timer > 100)
			? Engine::eC_LightYellow
			: static_cast<Engine::EColor>(Engine::eC_White - m_nAnimationFrame),
		"f");
}


void PlayerStar::Update()
{
	PlayerBomb::Update();

	Player& player = Player::GetPlayer();
	Vector2 playerPos = player.GetPos();
	playerPos += Vector2(16.f, 8.f);
	Vector2 vToPlayer = playerPos - m_pos;
	m_vel += vToPlayer / 1024.f;
}


void PlayerStar::OnCollision(bool bHorizontal, bool bVertical)
{
	if (bHorizontal)
	{
		m_vel.x = -m_vel.x;
	}

	if (bVertical)
	{
		m_vel.y = -m_vel.y;
	}

	Sounds::Play(Sounds::PLAYER_BALL_COLLISION);
}
