#ifndef __DX9_POLYGON_H_INCLUDE__
#define __DX9_POLYGON_H_INCLUDE__


#include "Vector.h"
#include "Color.h"
#include <d3dx9.h>


// ２Ｄポリゴン頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)


/* 矩形ポリゴン */
#define RECT_NUM_VERTEX		(4)		// 頂点数
#define RECT_NUM_POLYGON	(2)		// ポリゴン数


// 上記２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct VERTEX_2D
{
	Vector3 coord;		// 頂点座標
	float   rhw;		// テクスチャのパースペクティブコレクト用
	DxColor diffuse;	// 反射光
	Vector2 uv;			// テクスチャ座標
} Vertex2D;

// 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct VERTEX_3D
{
	Vector3 coord;		// 頂点座標
	Vector3 normal;		// 法線ベクトル
	DxColor diffuse;	// 反射光
	Vector2 uv;			// テクスチャ座標
} Vertex3D;



#endif // !__DX9_POLYGON_H_INCLUDE__
