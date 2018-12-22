#include "Player.h"
#include <cassert>
#include "GameStates.h"
#include "Maze.h"
#include "Projectiles.h"
#include "Settings.h"
#include "Sounds.h"


const float PI = 3.141592659f;
const float PIover2 = 1.570796327f;


Player::Player() :
	//TODO temporary for Mission Accomplished
	//Entity(Vector2(48.f, 72.f)),
	Entity(Vector2(80.f, 72.f)),
	m_texture(std::make_shared<Texture>("Assets/Player/Player.png")),

	m_textureJetDownBigLeft(std::make_shared<Texture>("Assets/Player/JetDownBigLeft.png")),
	m_textureJetDownBigRight(std::make_shared<Texture>("Assets/Player/JetDownBigRight.png")),
	
	m_textureJetDownSmallLeft (std::make_shared<Texture>("Assets/Player/JetDownSmallLeft.png")),
	m_textureJetDownSmallRight(std::make_shared<Texture>("Assets/Player/JetDownSmallRight.png")),
	
	m_textureJetLeft (std::make_shared<Texture>("Assets/Player/JetLeft.png")),
	m_textureJetRight(std::make_shared<Texture>("Assets/Player/JetRight.png")),

	m_frameIDBulletSpawned(0),
	m_frameIDBombSpawned(0),

	m_nPlayerBullets(0)
{
	SetTexture(m_texture, 32);

	m_spriteJetDownBigLeft .SetTexture(m_textureJetDownBigLeft,  16);
	m_spriteJetDownBigRight.SetTexture(m_textureJetDownBigRight, 16);

	m_spriteJetDownSmallLeft .SetTexture(m_textureJetDownSmallLeft,  16);
	m_spriteJetDownSmallRight.SetTexture(m_textureJetDownSmallRight, 16);

	m_spriteJetLeft .SetTexture(m_textureJetLeft,  16);
	m_spriteJetRight.SetTexture(m_textureJetRight, 16);


	m_spriteJetDownBigLeft .SetFrameTimer(2);
	m_spriteJetDownBigRight.SetFrameTimer(2);

	m_spriteJetDownSmallLeft .SetFrameTimer(2);
	m_spriteJetDownSmallRight.SetFrameTimer(2);

	m_spriteJetLeft .SetFrameTimer(2);
	m_spriteJetRight.SetFrameTimer(2);

	SetLifeTime(ELifeTime::Game);
}


std::shared_ptr<Player> Player::GetPlayer()
{
	static std::shared_ptr<Player> player(new Player);
	return player;
}


void Player::Reset()
{
	Entity::Reset();

	Refuel();
	RestoreAmmo();

	m_cBombsType = 'l';
	m_nBombs = 4;

	RestoreShield();
	ResetScore();

	m_frameIDBulletSpawned = 0;
	m_frameIDBombSpawned  = 0;

	m_pPlayerBomb = nullptr;
	m_nPlayerBullets = 0;
}


void Player::Animate()
{
	if (m_nShield < 0)
		return;

	bool bKeyLeftPressed = Engine::IsKeyDown(VK_LEFT) || Engine::IsKeyDown(Settings::cKeyLeft);
	bool bKeyRightPressed = Engine::IsKeyDown(VK_RIGHT) || Engine::IsKeyDown(Settings::cKeyRight);
	bool bKeyUpPressed = Engine::IsKeyDown(VK_UP) || Engine::IsKeyDown(Settings::cKeyUp);

	if (bKeyLeftPressed)
	{
		m_iAnimationFrame = 1;
	}

	if (bKeyRightPressed)
	{
		m_iAnimationFrame = 0;
	}

	if (m_nFuel > 0)
	{
		if (m_iAnimationFrame == 0)
		{
			if (bKeyRightPressed && !bKeyLeftPressed)
			{
				m_spriteJetLeft.Animate();
			}

			if (bKeyUpPressed)
			{
				m_spriteJetDownBigLeft.Animate();
				m_spriteJetDownSmallLeft.Animate();
			}
		}
		else
		{
			if (bKeyLeftPressed && !bKeyRightPressed)
			{
				m_spriteJetRight.Animate();
			}

			if (bKeyUpPressed)
			{
				m_spriteJetDownBigRight.Animate();
				m_spriteJetDownSmallRight.Animate();
			}
		}
	}
}


void Player::Render() const
{
	Entity::Render();

	if ((m_nShield >= 0) && (m_nFuel > 0))
	{
		bool bKeyLeftPressed = Engine::IsKeyDown(VK_LEFT) || Engine::IsKeyDown(Settings::cKeyLeft);
		bool bKeyRightPressed = Engine::IsKeyDown(VK_RIGHT) || Engine::IsKeyDown(Settings::cKeyRight);
		bool bKeyUpPressed = Engine::IsKeyDown(VK_UP) || Engine::IsKeyDown(Settings::cKeyUp);
	
		if (m_iAnimationFrame == 0)
		{
			if (bKeyRightPressed && !bKeyLeftPressed)
			{
				m_spriteJetLeft.Render();
			}

			if (bKeyUpPressed)
			{
				m_spriteJetDownBigLeft.Render();
				m_spriteJetDownSmallLeft.Render();
			}
		}
		else
		{
			if (bKeyLeftPressed && !bKeyRightPressed)
			{
				m_spriteJetRight.Render();
			}

			if (bKeyUpPressed)
			{
				m_spriteJetDownBigRight.Render();
				m_spriteJetDownSmallRight.Render();
			}
		}
	}
}


Vector2 Player::GetSteering() const
{
	// Apply gravity
	Vector2 vSteering(0.f, 0.015f);

	if ((m_nShield >= 0) && (m_nFuel > 0))
	{
		bool bKeyLeftPressed = Engine::IsKeyDown(VK_LEFT) || Engine::IsKeyDown(Settings::cKeyLeft);
		bool bKeyRightPressed = Engine::IsKeyDown(VK_RIGHT) || Engine::IsKeyDown(Settings::cKeyRight);
		bool bKeyUpPressed = Engine::IsKeyDown(VK_UP) || Engine::IsKeyDown(Settings::cKeyUp);

		// Apply thrust
		const float fThrust = 0.016f;

		if (bKeyLeftPressed && !bKeyRightPressed)
		{
			vSteering.x = -fThrust;
		}
		if (bKeyRightPressed && !bKeyLeftPressed)
		{
			vSteering.x = fThrust;
		}
		if (bKeyUpPressed)
		{
			vSteering.y -= 0.03f;
		}
	}

	return vSteering;
}


void Player::Update()
{
	if (m_nShield < 0)
		return;

	Entity::Update();

	const float fMaxVelocity = 2.55f;
	if (m_vel.GetLength() > fMaxVelocity)
	{
		m_vel.SetLength(fMaxVelocity);
	}

	if (m_nFuel > 0)
	{
		bool bKeyLeftPressed = Engine::IsKeyDown(VK_LEFT) || Engine::IsKeyDown(Settings::cKeyLeft);
		bool bKeyRightPressed = Engine::IsKeyDown(VK_RIGHT) || Engine::IsKeyDown(Settings::cKeyRight);
		if (bKeyLeftPressed ^ bKeyRightPressed)
		{
			ConsumeFuel();
		}

		bool bKeyUpPressed = Engine::IsKeyDown(VK_UP) || Engine::IsKeyDown(Settings::cKeyUp);
		if (bKeyUpPressed)
		{
			ConsumeFuel();
		}

		m_spriteJetDownBigLeft .SetPos(m_pos.x,        m_pos.y + 15.f);
		m_spriteJetDownBigRight.SetPos(m_pos.x + 16.f, m_pos.y + 15.f);

		m_spriteJetDownSmallLeft .SetPos(m_pos.x + 16.f, m_pos.y + 15.f);
		m_spriteJetDownSmallRight.SetPos(m_pos.x,        m_pos.y + 15.f);

		m_spriteJetLeft .SetPos(m_pos.x - 15.f, m_pos.y);
		m_spriteJetRight.SetPos(m_pos.x + 31.f, m_pos.y);
	}

	
	long int frameID = Engine::GetFrameID();

	if (!m_pPlayerBomb && (m_nBombs > 0) && (frameID - m_frameIDBombSpawned >= 4))
	{
		bool bKeyDownPressed = Engine::IsKeyDown(VK_DOWN) || Engine::IsKeyDown(Settings::cKeyDown);
		if (bKeyDownPressed)
		{
			bool bLeft = (m_iAnimationFrame == 1);
			switch (m_cBombsType)
			{
			case 'c':	// Vertical bomb
				m_pPlayerBomb = std::make_shared<PlayerVerticalBomb>();
				m_pPlayerBomb->SetVelocity(m_vel.x, 1.f);
				m_pPlayerBomb->SetLifeTime(ELifeTime::Room);
				break;

			case 'a':	// Horizontal bomb
				m_pPlayerBomb = std::make_shared<PlayerHorizontalBomb>(bLeft);
				m_pPlayerBomb->SetVelocity(bLeft ? -.5f : .5f, 1.5f);
				m_pPlayerBomb->SetLifeTime(ELifeTime::Room);
				break;

			case 'l':	// Ball
				m_pPlayerBomb = std::make_shared<PlayerBall>();
				m_pPlayerBomb->SetVelocity(bLeft ? -1.6f : 1.6f, 2.f + ((rand() % 400) / 1000.f));
				m_pPlayerBomb->SetLifeTime(ELifeTime::FollowPlayer);
				break;

			case 'f':	// Star
			{
				m_pPlayerBomb = std::make_shared<PlayerStar>();
				float r = float(rand()) / RAND_MAX;
				float angle = (bLeft ? PIover2 : -PIover2) + PI * r;
				m_pPlayerBomb->SetVelocity(cosf(angle), sinf(angle));
				m_pPlayerBomb->SetLifeTime(ELifeTime::FollowPlayer);
				break;
			}

			default:
				assert(false);
			}

			if (m_pPlayerBomb)
			{
				m_pPlayerBomb->SetPosNearPlayer();
				Maze::GetMaze()->AddEntity(m_pPlayerBomb);
				Audio::Play(Sounds::PLAYER_BOMB_LAUNCH);

				--m_nBombs;
				m_frameIDBombSpawned = frameID;
			}
		}
	}

	if ((m_nAmmo > 0) && (m_nPlayerBullets < 2) && (frameID - m_frameIDBulletSpawned >= 16))
	{
		bool bKeyFirePressed = Engine::IsKeyDown(VK_SPACE) || Engine::IsKeyDown(Settings::cKeyFire);
		if (bKeyFirePressed)
		{
			bool bLeft = (m_iAnimationFrame == 1);
			std::shared_ptr<PlayerBullet> pBullet = std::make_shared<PlayerBullet>(m_pos + Vector2(bLeft ? 0.f : 24.f, 7.f));
			pBullet->SetVelocity(bLeft ? -6.f : 6.f, 0.f);
			pBullet->SetLifeTime(ELifeTime::Room);

			Maze::GetMaze()->AddEntity(pBullet);
			Audio::Play(Sounds::FIRE);

			--m_nAmmo;
			++m_nPlayerBullets;
			m_frameIDBulletSpawned = frameID;
		}
	}
}


void Player::OnCollision(bool bHorizontal, bool bVertical)
{
	// Apply friction if appropriate
	if (bVertical)
	{
		const float fFrictionDeceleration = 0.0035f;

		if (m_vel.x > 0.f)
		{
			m_vel.x = max(0.f, m_vel.x - fFrictionDeceleration);
		}
		else
		{
			if (m_vel.x < 0.f)
			{
				m_vel.x = min(0.f, m_vel.x + fFrictionDeceleration);
			}
		}
	}

	if (bHorizontal)
	{
		m_vel.x *= -0.3f;
		if (fabs(m_vel.x) < 0.15f)
		{
			m_vel.x = 0.f;
		}
	}

	if (bVertical)
	{
		m_vel.y *= -0.233f;
		if (fabs(m_vel.y) < 0.2f)
		{
			m_vel.y = 0.f;
		}

		if ((m_nFuel <= 0) && (m_nShield >= 0))
		{
			ConsumeShield(1);
		}
	}
}


void Player::ConsumeShield(int nUnits)
{
	if (Settings::bInvulnerability)
		return;

	m_nShield -= nUnits;

	if (m_nShield < 0)
	{
		if (Audio::IsPlaying(Sounds::LESS_SHIELD))
		{
			Audio::Stop(Sounds::LESS_SHIELD);
		}

		GameStates::SwitchTo("game_over");
	}
}


void Player::OnRoomChanged()
{
	if (m_pPlayerBomb && (m_pPlayerBomb->GetLifeTime() == ELifeTime::FollowPlayer))
	{
		m_pPlayerBomb->SetPosNearPlayer();
		Maze::GetMaze()->AddEntity(m_pPlayerBomb);
	}
}
