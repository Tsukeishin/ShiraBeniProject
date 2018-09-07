#ifndef __WINDOWCLASS_H_INCLUDE__
#define __WINDOWCLASS_H_INCLUDE__


#include <Windows.h>


class WindowClass
{
	static HINSTANCE    Instance;
	static HWND         Handle;
	static MSG          Message;
	static bool         WindowMode;
	static char        *ClassName;
	static char        *WindowName;

public:
	static HRESULT             Init(HINSTANCE hInstance);
	static void                Uninit(void);
	static LRESULT CALLBACK    WindowProc(HWND, UINT, WPARAM, LPARAM);
	static int                 CheckMessage(void);
	static HWND                GetHWnd(void);
	static HINSTANCE           GetHInstance(void);
	static bool                GetWindowMode(void);
	static void                SetWindowMode(bool windowMode);
	static void                SetWindowSize(int x, int y);


};

#endif // !__WINDOWCLASS_INCLUDE_H__
