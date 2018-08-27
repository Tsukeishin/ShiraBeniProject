//=============================================================================
//
// ウィンドウ処理 <WindowClass.h>
//
//=============================================================================
#ifndef __WINDOWCLASS_INCLUDE_H__
#define __WINDOWCLASS_INCLUDE_H__

#include "LinkLibrary.h"


class CWindow
{
	static HINSTANCE    Instance;
	static HWND         Handle;
	static MSG          Message;
	static bool         WindowMode;
	static bool         BigMode;
	static char        *ClassName;

public:

};


#endif