#include "Session.h"
#include "../Shared/Engine.h"
#include "Maze.h"


void Session::OnEnter()
{
	Maze::GetMaze()->Reset();
}


void Session::Update()
{
	Maze::GetMaze()->Update();
}


void Session::Render() const
{
	Maze::GetMaze()->Render();
}
