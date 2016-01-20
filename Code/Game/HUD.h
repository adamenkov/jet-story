#ifndef __HUD_H
#define __HUD_H

#pragma once

#include "../Common/Engine.h"
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
	
	typedef std::vector<Tile> Tiles;
	Tiles m_tiles;
};


#endif	// #ifndef __HUD_H
