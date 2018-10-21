#ifndef __WINDOWCLASS_H_INCLUDE__
#define __WINDOWCLASS_H_INCLUDE__


#include <Windows.h>


class WindowClass
{
	static HINSTANCE    Instance;
	static HWND         Handle;
	static MSG          Message;
	static LPCSTR       ClassName;
	static LPCSTR       WindowName;
	static bool         WindowMode;

public:
	static HRESULT          Init(HINSTANCE hInstance, LPCSTR className, LPCSTR windowName);
	static void             Uninit(void);
	static LRESULT CALLBACK WindowProcess(HWND, UINT, WPARAM, LPARAM);
	static int              CheckMessage(void);
	static HWND             GetHWnd(void);
	static HINSTANCE        GetHInstance(void);
	static bool             GetWindowMode(void);
	static void             SetWindowMode(bool windowMode);
	static void             SetWindowSize(int x, int y);

	static RECT GetRect();
};

#endif // !__WINDOWCLASS_INCLUDE_H__
