#ifdef _DEBUG

#include "Debug.h"
#include <iomanip>
#include <sstream>
#include "../Shared/Engine.h"
#include "Maze.h"


namespace Debug
{
	bool bDrawPos = false;
	bool bDrawVel = false;
	bool bDrawAcc = false;

	float A = 20.f;
	float B = 100.f;

	float dA = 1.f;
	float dB = 1.f;

	void Render()
	{
		Engine::Print(0, 3, EColor::Black, "\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f"
			"\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f");

		{
			std::ostringstream os;
			os << "A=" << A << ", B=" << B;
			Engine::Print(0, 3, EColor::White, os.str());
		}

		for (std::shared_ptr<Entity>& pEntity : Maze::GetMaze().GetRoomEntities())
		{
			if (!pEntity->IsEnabled())
				continue;

			Vector2 pos = pEntity->GetPos();

			if (bDrawPos)
			{
				std::ostringstream os;
				os << int(pos.x) << "," << int(pos.y);
				Engine::DrawText(pos, EColor::White, os.str());
			}

			if (bDrawVel)
			{
				Vector2 vel = pEntity->GetVelocity();
				std::ostringstream os;
				os << std::setprecision(3) << vel.x << "," << vel.y;
				Engine::DrawText(pos + Vector2(0.f, 8.f), EColor::White, os.str());
			}

			if (bDrawAcc)
			{
				Vector2 acc = pEntity->GetSteering();
				std::ostringstream os;
				os << std::setprecision(3) << acc.x << "," << acc.y;
				Engine::DrawText(pos + Vector2(0.f, 16.f), EColor::White, os.str());
			}
		}
	}

	void KeyPressed(char key)
	{
		switch (key)
		{
		case VK_SUBTRACT:	A -= dA;	break;
		case VK_ADD:		A += dA;	break;
		
		case VK_MULTIPLY:	B += dB;	break;
		case VK_DIVIDE:		B -= dB;	break;

		case VK_F5:			bDrawPos = !bDrawPos;	break;
		case VK_F6:			bDrawVel = !bDrawVel;	break;
		case VK_F7:			bDrawAcc = !bDrawAcc;	break;
		}
	}

}	// namespace Debug


#endif	// #ifdef _DEBUG
