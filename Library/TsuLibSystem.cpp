#include "TsuLibSystem.h"
#include "WindowClass.h"
#include "Direct3D.h"
#include "Dx9Line.h"
#include "DirectInput.h"
#include "Sound.h"
#include "DebugProcess.h"

HRESULT TSULibrarySystem::Initialize(HINSTANCE hInstance)
{
	// ウィンドウ初期化
	if (FAILED(WindowClass::Init(hInstance, "ShirabeniProject", "白紅プロジェクト")))
		return -1;

	// グラフィックス初期化(Direct3D)
	if (FAILED(Direct3D::Init(WindowClass::GetHWnd(), TRUE)))
		return -1;

	// インプット初期化
	if (FAILED(DirectInput::Init(WindowClass::GetHInstance(), WindowClass::GetHWnd())))
		return -1;

	// サウンド初期化
	if (FAILED(DirectSound::Init(WindowClass::GetHWnd())))
		return -1;

	// Dx9Line初期化
	if (FAILED(Dx9Line::Init()))
		return -1;

	// デバッグ表示の初期化
	InitDebugProcess();

	return S_OK;
}

void TSULibrarySystem::Uninitialize()
{
	WindowClass::Uninit();	// ウィンドウ終了
	Direct3D::Uninit();		// グラフィックス終了(Direct3D)
	DirectInput::Uninit();	// 入力の終了処理
	DirectSound::Uninit();	// サウンド終了処理
	Dx9Line::Uninit();		// Dx9Line終了処理
	UninitDebugProcess();	// デバッグ表示処理の終了処理
}

void TSULibrarySystem::CoordinateAxis()
{
	struct caLine
	{
		Vector3 coord;
		DxColor color;
	};

	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();

#define CAFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
	LPDIRECT3DVERTEXBUFFER9 lineVtxBuff;
	// オブジェクトの頂点バッファを生成
	Direct3D::GetD3DDevice()->CreateVertexBuffer(sizeof(caLine) * 6,
		D3DUSAGE_WRITEONLY,		// 頂点バッファの使用法　
		CAFVF,					// 使用する頂点フォーマット
		D3DPOOL_MANAGED,		// リソースのバッファを保持するメモリクラスを指定
		&lineVtxBuff,			// 頂点バッファインターフェースへのポインタ
		NULL);					// NULLに設定
	{//頂点バッファの中身を埋める
		caLine *pVtx;

		// 頂点データの範囲をロック
		lineVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 座標
		pVtx[0].coord = Vector3(  0, 0, 0);
		pVtx[1].coord = Vector3(100, 0, 0);
		pVtx[2].coord = Vector3(0,   0, 0);
		pVtx[3].coord = Vector3(0, 100, 0);
		pVtx[4].coord = Vector3(0, 0,   0);
		pVtx[5].coord = Vector3(0, 0, 100);

		// 色
		pVtx[0].color = DX9COLOR_RED;
		pVtx[1].color = DX9COLOR_RED;
		pVtx[2].color = DX9COLOR_GREEN;
		pVtx[3].color = DX9COLOR_GREEN;
		pVtx[4].color = DX9COLOR_BLUE;
		pVtx[5].color = DX9COLOR_BLUE;

		// 頂点データをアンロックする
		lineVtxBuff->Unlock();
	}

	// ラインティング
	DWORD lightState;
	pDevice->GetRenderState(D3DRS_LIGHTING, &lightState);
	if (lightState)
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetStreamSource(0, lineVtxBuff, 0, sizeof(caLine));
	pDevice->SetFVF(CAFVF);
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 3);

	Dx9SafeRelease(lineVtxBuff);

	// ラインティングを有効に戻す
	if (lightState)
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}



