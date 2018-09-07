#include "FPSManager.h"


DWORD FPSManager::keepFPS     = 60;	// FPS規定値
DWORD FPSManager::lastTime    = 0;	// メッセ用過去タイマー
DWORD FPSManager::nowTime     = 0;	// メッセ用現在タイマー
DWORD FPSManager::exlastTime  = 0;	// 精密過去タイマー
DWORD FPSManager::exSecTime   = 0;	// 精密過去タイマー(秒)
DWORD FPSManager::exMilTime   = 0;	// 精密過去タイマー(ミリ秒)
FPSManager::Display FPSManager::DisNomal = { 0, 0, 0.0f };	// 通常用表記
FPSManager::Display FPSManager::DisExact = { 0, 0, 0.0f };	// 精密用表記

void FPSManager::Init()
{
	nowTime = exSecTime = exMilTime = timeGetTime();
}
void FPSManager::Init(int fps)
{
	keepFPS = fps;
	nowTime = exSecTime = exMilTime = timeGetTime();
}

bool FPSManager::FramerateControl()
{
	nowTime = timeGetTime();
	if ((nowTime - lastTime) >= 1000 / keepFPS)
	{
		lastTime = nowTime;
		DisNomal.Count++;
		return true;
	}
	return false;
}

int FPSManager::ExactFPS(int time)
{
	nowTime = timeGetTime();

	/* 1sCheck */
	if (nowTime - exSecTime >= 1000)
	{
		exSecTime += 1000;
		return (time - DisExact.Count);
	}

	/* Check */
	if ((nowTime - exlastTime) >= (DWORD)(1000 / time))
	{
		exlastTime = nowTime;
		// 100msCheck
		if ((nowTime - exMilTime) >= 100)
		{
			exMilTime += 100;
			if ((DisExact.Count % 10) > (DWORD)(time / 10))
			{
				return 0;
			}
		}
		DisExact.Count++;
		return 1;
	}
	return 0;
}

float FPSManager::DisplayFPS(int type)
{
	nowTime = timeGetTime();
	switch (type)
	{
	case FPS_NORMAL:
		if ((nowTime - DisNomal.LastTime) >= 2000)
		{
			DisNomal.Display = (float)DisNomal.Count * 1000.0f / (float)(nowTime - DisNomal.LastTime);
			DisNomal.LastTime = nowTime;
			DisNomal.Count = 0;
		}
		return DisNomal.Display;

	case FPS_EXACT:
		if ((nowTime - DisExact.LastTime) >= 2000)
		{
			DisExact.Display = (float)DisExact.Count * 1000.0f / (float)(nowTime - DisExact.LastTime);
			DisExact.LastTime = nowTime;
			DisExact.Count = 0;
		}
		return DisExact.Display;
	}
	return -1;
}

