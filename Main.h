//=============================================================================
//
// メイン処理 [main.h]
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS		// warning防止

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include <d3dx9.h>
#include <tchar.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <conio.h>

#define DIRECTINPUT_VERSION (0x0800)	// 警告対策
#include <dinput.h>			// DirectInput関連のヘッダー
#include <xaudio2.h>		// XAudio2関連のヘッダー

#include "Library\DebugProcess.h"


//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ２Ｄポリゴン頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)


#define	NUM_VERTEX		(4)		// 頂点数
#define	NUM_POLYGON		(2)		// ポリゴン数


/* ゲーム状態の種類 */
typedef enum
{
	SCENE_TITLE = 0,	// タイトル画面
	SCENE_STAGESELECT,	// ステージ選択画面
	SCENE_TUTORIAL,		// チュートリアル
	SCENE_GAME,			// メインゲーム
	SCENE_RESULT,		// リザルト画面
	SCENE_PAUSE,		// ポーズ画面
	SCENE_MAX,
	SCENE_END,	// アプリ終了
} GAMESCENE;


//*****************************************************************************
// 構造体定義
//*****************************************************************************
// 上記２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	float rhw;				// テクスチャのパースペクティブコレクト用
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_2D;

// 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	D3DXVECTOR3 normal;		// 法線ベクトル
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_3D;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
GAMESCENE SetGameScene(GAMESCENE scene);


#endif