#ifndef __AUDIO_H
#define __AUDIO_H

#pragma once

// This is exposed to Game


namespace Audio
{
	bool Load(const char* szFileName, const char* szName);

	bool IsPlaying(const char* szName);
	bool Play(const char* szName, int nLoopCount = 1);
	void Stop(const char* szName);
	void StopAll();

	void PauseAll();
	void ResumeAll();

}	// namespace Audio


#endif	// #ifndef __AUDIO_H
