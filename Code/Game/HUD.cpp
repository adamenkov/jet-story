#include "HUD.h"
#include <algorithm>
#include <functional>
#include <iomanip>
#include <sstream>
#include "../Shared/Engine.h"
#include "Maze.h"
#include "Player.h"


HUD::HUD()
{
	for (int x = 0; x < Engine::eScreenWidthInCharacters; ++x)
	{
		m_tiles.emplace_back(std::make_shared<Tile>(x, 0));
		m_tiles.emplace_back(std::make_shared<Tile>(x, 3));
	}

	for (int y = 1; y < 3; ++y)
	{
		m_tiles.emplace_back(std::make_shared<Tile>( 0, y));
		m_tiles.emplace_back(std::make_shared<Tile>(10, y));
		m_tiles.emplace_back(std::make_shared<Tile>(13, y));
		m_tiles.emplace_back(std::make_shared<Tile>(20, y));
		m_tiles.emplace_back(std::make_shared<Tile>(21, y));
		m_tiles.emplace_back(std::make_shared<Tile>(28, y));
		m_tiles.emplace_back(std::make_shared<Tile>(31, y));
	}

	for (int x = 22; x < 28; ++x)
	{
		m_tiles.emplace_back(std::make_shared<Tile>(x, 2));
	}
}


HUD& HUD::GetHUD()
{
	static HUD hud;
	return hud;
}


void HUD::Render()
{
	std::shared_ptr<Player> player = Player::GetPlayer();

	Engine::Print(1, 1, EColor::eC_White, "FUEL");
	RenderBar(5, 1, player->GetFuel(), player->GetMaxFuel());

	Engine::Print(1, 2, EColor::eC_White, "AMMO");
	RenderBar(5, 2, player->GetAmmo(), player->GetMaxAmmo());


	int shield = player->GetShield();
	if (shield >= 0)
	{
		Engine::Print(14, 1, EColor::eC_White, "SHIELD");
		RenderBar(14, 2, player->GetShield(), player->GetMaxShield());
	}
	Engine::Print(14, 2, EColor::eC_White, ">    <");

	RenderInt(22, 1, player->GetScore(), 6);

	Engine::Print(29, 1, EColor::eC_White, "++");
	RenderInt(29, 2, Maze::GetMaze()->GetBasesLeft(), 2);

	char cBombsType = player->GetBombsType();
	char sz[3];
	sz[0] = cBombsType;
	sz[1] = cBombsType;
	sz[2] = 0;
	Engine::Print(11, 1, EColor::eC_White, sz);
	RenderInt(11, 2, player->GetBombs(), 2);

#ifdef DEBUG_MAZE
	{
		Vector2 pos = m_player.GetPos();
		std::ostringstream os;
		os << "X: " << int(pos.x) << ", Y: " << int(pos.y);
		Engine::Print(1, 22, EColor::eC_White, os.str());
	}
#endif	// #ifdef DEBUG_MAZE

	for (std::shared_ptr<Tile>& tile : m_tiles)
	{
		tile->Render();
	}
}


void HUD::Update()
{
	if (rand() % 2)
	{
		m_tiles[rand() % m_tiles.size()]->eColor = EColor::eC_LightCyan;
	}
	else
	{
		EColor eNewColor;
		do
		{
			eNewColor = static_cast<EColor>(rand() % static_cast<int>(EColor::eC_TotalColors));
		} while ((eNewColor == EColor::eC_LightCyan)  ||
				 (eNewColor == EColor::eC_Black)      ||
				 (eNewColor == EColor::eC_Grey)       ||
				 (eNewColor == EColor::eC_LightBlack) ||
				 (eNewColor == EColor::eC_White));

		m_tiles[rand() % m_tiles.size()]->eColor = eNewColor;
	}
}


void HUD::RenderBar(int x, int y, int value, int maxValue) const
{
	for (int i = 0; i < (value << 5) / maxValue; ++i)
	{
		Engine::DrawText(8 * x + i + 1, 8 * y, EColor::eC_White, "H");
	}

	Engine::DrawText(8 * x + 1, 8 * y, EColor::eC_Black, "#");
}


void HUD::RenderInt(int x, int y, int value, int width) const
{
	std::ostringstream os;
	os << std::setw(width) << std::setfill('0') << value;
	Engine::Print(x, y, EColor::eC_White, os.str());
}
