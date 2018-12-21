#pragma once

#include "../Shared/Engine.h"
#include <vector>


class HUD
{
	HUD();
	HUD(const HUD&);

public:
	static HUD& GetHUD();

	void Render();
	void Update();

private:
	void RenderBar(int x, int y, int value, int maxValue) const;
	void RenderInt(int x, int y, int value, int width) const;

	struct Tile
	{
		int x;
		int y;
		Engine::EColor eColor;

		Tile(int x, int y) : x(x), y(y), eColor(Engine::eC_LightCyan) {}
		
		void Render() { Engine::Print(x, y, eColor, '#'); }
	};
	
	std::vector<std::shared_ptr<Tile>> m_tiles;
};
