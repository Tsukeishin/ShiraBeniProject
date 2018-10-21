#include "Dx9Line.h"
#include "Color.h"


LPD3DXLINE Dx9Line::pLine;
SDXLINE Dx9Line::Coord2D[DX2DLINE_MAX] = { Vector2() };
Vector3 Dx9Line::Coord3D[DX3DLINE_MAX][2] = { Vector3() };
int Dx9Line::CoordCnt2D = 0;
int Dx9Line::CoordCnt3D = 0;

HRESULT Dx9Line::Init()
{
	for (int i = 0; i < DX2DLINE_MAX; i++)
	{
		Coord2D[i].LinePoint[0] = Vector2();
		Coord2D[i].LinePoint[1] = Vector2();
	}
	for (int i = 0; i < DX3DLINE_MAX; i++)
	{
		Coord3D[i][0] = Vector3();
		Coord3D[i][1] = Vector3();
	}
	D3DXCreateLine(Direct3D::GetD3DDevice(), &pLine);

	pLine->SetWidth(2);
	return S_OK;
}
void Dx9Line::Uninit()
{
	if (pLine != NULL)
	{
		pLine->Release();
		pLine = NULL;
	}
}
void Dx9Line::Draw()
{
	pLine->Begin();
	
	for (int i = 0; i < DX2DLINE_MAX; i++)
	{
		pLine->Draw((D3DXVECTOR2*)Coord2D[i].LinePoint, 1, Coord2D[i].Color);
	}

	pLine->End();

	CoordCnt2D = 0;
	CoordCnt3D = 0;
}

int Dx9Line::SetLine(Vector2 v1, Vector2 v2, DxColor color)
{
	if (CoordCnt2D >= DX2DLINE_MAX)
		return 1;

	Coord2D[CoordCnt2D].LinePoint[0] = v1;
	Coord2D[CoordCnt2D].LinePoint[1] = v2;
	Coord2D[CoordCnt2D].Color = color;
	CoordCnt2D++;
	return 0;
}
int Dx9Line::SetBoxLine(Vector2 pos, Vector2 siz, DxColor color)
{
	if (CoordCnt2D >= DX2DLINE_MAX - 4)
		return 1;

	Coord2D[CoordCnt2D    ].LinePoint[0] = Vector2(-siz.x, -siz.y) + pos;	// 左上
	Coord2D[CoordCnt2D    ].LinePoint[1] = Vector2( siz.x, -siz.y) + pos;	// 右上
	Coord2D[CoordCnt2D    ].Color = color;

	Coord2D[CoordCnt2D + 1].LinePoint[0] = Vector2( siz.x, -siz.y) + pos;	// 右上
	Coord2D[CoordCnt2D + 1].LinePoint[1] = Vector2( siz.x,  siz.y) + pos;	// 右下
	Coord2D[CoordCnt2D + 1].Color = color;

	Coord2D[CoordCnt2D + 2].LinePoint[0] = Vector2( siz.x,  siz.y) + pos;	// 右下
	Coord2D[CoordCnt2D + 2].LinePoint[1] = Vector2(-siz.x,  siz.y) + pos;	// 左下
	Coord2D[CoordCnt2D + 2].Color = color;

	Coord2D[CoordCnt2D + 3].LinePoint[0] = Vector2(-siz.x,  siz.y) + pos;	// 左下
	Coord2D[CoordCnt2D + 3].LinePoint[1] = Vector2(-siz.x, -siz.y) + pos;	// 左上
	Coord2D[CoordCnt2D + 3].Color = color;
	CoordCnt2D += 4;
	return 0;
}


