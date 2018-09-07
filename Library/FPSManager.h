#ifndef __MANAGER_FPS_H_INCLUDE__
#define __MANAGER_FPS_H_INCLUDE__


#include <windows.h>


#define FPS_NORMAL  (0)
#define FPS_EXACT   (1)


class FPSManager
{
public:
	typedef struct
	{
		DWORD Count;
		DWORD LastTime;
		float Display;
	}Display;

private:
	static DWORD keepFPS;		// FPS規定値
	static DWORD lastTime;		// メッセ用過去タイマー
	static DWORD nowTime;		// メッセ用現在タイマー
	static DWORD exlastTime;	// 精密過去タイマー
	static DWORD exSecTime;		// 精密過去タイマー(秒)
	static DWORD exMilTime;		// 精密過去タイマー(ミリ秒)
	static Display DisNomal;	// 通常
	static Display DisExact;	// 精密

public:

	static void Init();
	static void Init(int fps);
//	static void Uninit();
	static bool FramerateControl();
	static int  ExactFPS(int time);
	static float DisplayFPS(int type);

};

#endif // !__MANAGER_FPS_H_INCLUDE__
