#pragma once
#include <ctime>
#include <windows.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

#ifdef _WINDLL
#define DLL_OUTPUT dllexport
#else
#define DLL_OUTPUT dllimport
#endif

class Timer
{
private:
	DWORD _InitialTime,_StartTime, _CurrentTime,_DeltaTime, _ElapsedTime;
public:
	Timer() 
	{
		_InitialTime = timeGetTime();
		_CurrentTime = _InitialTime;
		_ElapsedTime = 0x00000000;
	}
	void ResetTimer()
	{
		_StartTime = timeGetTime();
		_ElapsedTime = (DWORD)0.0;
	}
	void Update()
	{
		_DeltaTime = timeGetTime() - _CurrentTime;
		_CurrentTime = timeGetTime();
		_ElapsedTime += _DeltaTime;
	}
	double ElapsedTimer()
	{
		_ElapsedTime = (DWORD)(timeGetTime() - _StartTime * 0.001);
		return _ElapsedTime; 
	}
	double CurrentTime()
	{
		return (double)_CurrentTime * 0.001;
	}
	double InitialTime()
	{
		return (double)_InitialTime * 0.001;
	}
	double DeltaTime()
	{
		return (double)_DeltaTime * 0.001;
	}
};