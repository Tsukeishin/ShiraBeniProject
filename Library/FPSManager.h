#ifndef __MANAGER_FPS_H_INCLUDE__
#define __MANAGER_FPS_H_INCLUDE__


#include <Windows.h>


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
	static DWORD keepFPS;		// FPSKèl
	static DWORD lastTime;		// bZpß^C}[
	static DWORD nowTime;		// bZp»Ý^C}[
	static DWORD exlastTime;	// ¸§ß^C}[
	static DWORD exSecTime;		// ¸§ß^C}[(b)
	static DWORD exMilTime;		// ¸§ß^C}[(~b)
	static Display DisNomal;	// Êí
	static Display DisExact;	// ¸§

public:

	static void Init();
	static void Init(int fps);
//	static void Uninit();
	static bool FramerateControl();
	static int  ExactFPS(int time);
	static float DisplayFPS(int type);

};

#endif // !__MANAGER_FPS_H_INCLUDE__
