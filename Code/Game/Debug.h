#ifndef __DEBUG_H
#define __DEBUG_H

#pragma once

#define _USING_V110_SDK71_ 1


namespace Debug
{
	extern float A;
	extern float B;
	
	extern float dA;
	extern float dB;

	void Render();

	void KeyPressed(char key);

}	// namespace Debug


#endif	// #ifndef __DEBUG_H
