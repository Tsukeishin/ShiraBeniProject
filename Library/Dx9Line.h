#ifndef __Dx9_LINE_H_INCLUDE__
#define __Dx9_LINE_H_INCLUDE__


#include "Direct3D.h"
#include "Vector.h"
#include "Color.h"


#define DX2DLINE_MAX (64)
#define DX3DLINE_MAX (128)


struct SDXLINE
{
	Vector2 LinePoint[2];
	DxColor Color;
};

class Dx9Line
{
	static LPD3DXLINE pLine;
	static SDXLINE Coord2D[DX2DLINE_MAX];
	static Vector3 Coord3D[DX3DLINE_MAX][2];
	static int CoordCnt2D;
	static int CoordCnt3D;

public:
	static HRESULT Init();
	static void Uninit();
	static void Draw();

	static int SetLine(Vector2 v1, Vector2 v2, DxColor color = DX9COLOR_WHITE);
	static int SetBoxLine(Vector2 pos, Vector2 siz, DxColor color = DX9COLOR_WHITE);

};



#endif // !__COMMON_H_INCLUDE__

