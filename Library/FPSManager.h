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
	static DWORD keepFPS;		// FPS�K��l
	static DWORD lastTime;		// ���b�Z�p�ߋ��^�C�}�[
	static DWORD nowTime;		// ���b�Z�p���݃^�C�}�[
	static DWORD exlastTime;	// �����ߋ��^�C�}�[
	static DWORD exSecTime;		// �����ߋ��^�C�}�[(�b)
	static DWORD exMilTime;		// �����ߋ��^�C�}�[(�~���b)
	static Display DisNomal;	// �ʏ�
	static Display DisExact;	// ����

public:

	static void Init();
	static void Init(int fps);
//	static void Uninit();
	static bool FramerateControl();
	static int  ExactFPS(int time);
	static float DisplayFPS(int type);

};

#endif // !__MANAGER_FPS_H_INCLUDE__
