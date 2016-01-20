#include "../Common/Game.h"
#include "../Common/Engine.h"
#include "Debug.h"
#include "GameStates.h"
#include "Maze.h"
#include "Sounds.h"


namespace
{
	bool bExitDialog = false;

}	// namespace


namespace Game
{
	const char* GetName()
	{
		return "Jet-Story";
	}

	
	void Init()
	{
		Sounds::Init();
		Maze::GetMaze().Init();
		GameStates::Init();
	}


	void ShutDown()
	{
		GameStates::ShutDown();
		Maze::GetMaze().ShutDown();
	}


	void Render()
	{
		if (bExitDialog)
		{
			Engine::Print(8, 9, Engine::eC_White, "EXIT JET-STORY?");
			Engine::Print(5, 13, Engine::eC_White, "ENTER=YES       ESC=NO");
		}
		else
		{
			GameStates::Render();
		}
	}


	void Update()
	{
		if (!bExitDialog)
		{
			GameStates::Update();
		}
	}


	void KeyPressed(char key)
	{
		if (key == VK_ESCAPE)
		{
			bExitDialog = !bExitDialog;

			if (bExitDialog)
			{
				Audio::PauseAll();
			}
			else
			{
				Audio::ResumeAll();
			}

			return;
		}

		if (bExitDialog)
		{
			if (key == VK_RETURN)
			{
				Engine::Exit();
			}
		}
		else
		{
			GameStates::KeyPressed(key);

			Debug::KeyPressed(key);
		}
	}

}	// namespace Game
