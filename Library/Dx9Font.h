#ifndef __Dx9_FONT_H_INCLUDE__
#define __Dx9_FONT_H_INCLUDE__


#include "Color.h"
#include <d3dx9core.h>
#include <Windows.h>


class Dx9Font
{
	LPD3DXFONT FontPointer;
	UINT       Format;
	DxColor    Color;

public:
	HRESULT Create(INT height, UINT width, UINT weight, LPCSTR fontName = "Terminal");
	void Draw(int x, int y, LPCSTR string);
	void Draw(int x, int y, LPCSTR string, D3DCOLOR color);
	void Release();

};


#endif