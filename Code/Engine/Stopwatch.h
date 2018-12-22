#pragma once

#include <Windows.h>


class Stopwatch
{
public:
	Stopwatch() : m_start(timeGetTime()) {}

	bool operator()(int ms)
	{
		if (timeGetTime() >= m_start + ms)
		{
			m_start = timeGetTime();
			return true;
		}
		return false;
	}
	
private:
	DWORD m_start;
};
