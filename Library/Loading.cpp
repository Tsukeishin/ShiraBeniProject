//=============================================================================
//
// ローディング画面処理 <Loading.cpp>
//
//=============================================================================
#include "Loading.h"
#include "Input.h"
#include "Fade.h"


#define LOADING_TEX_BACK "data/TEXTURE/SCENE/LoadBack.jpg"
#define LOADING_TEX_GAGE "data/TEXTURE/SCENE/LoadBox.jpg"
#define LOADING_TEX_TEXT "data/TEXTURE/SCENE/load.png"


//----初期化--------
void CNowLoading::Init(GAMESCENE scene)
{
	Back.LoadTexture(LOADING_TEX_BACK);
	Text.Init(RelativeSX(0.8f), RelativeSY(0.8f), 200, 10, LOADING_TEX_TEXT);
	PercentGage.Init(LOADING_TEX_GAGE, LOADING_TEX_GAGE);
	PercentGage.Init(RelativeSX(0.8f), RelativeSY(0.85f), 200, 20);
	PercentGage.Frame.SetVertex(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
	PercentGage.Gage.SetVertex(D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
}

//----終了--------
void CNowLoading::Uninit(void)
{
	Back.Release();
	Text.Release();
	PercentGage.Uninit();
}

//----更新--------
void CNowLoading::Progress(int per)
{
	/* 更新 */
	float percent = (float)per / 100.0f;
	PercentGage.Update(percent);

	/* 描画 */
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// バックバッファ＆Ｚバッファのクリア
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0x66, 0x88, 0xFF, 0xFF), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(pDevice->BeginScene()))
	{

		Back.Draw();
		PercentGage.Draw();
		Text.Draw();

		// Direct3Dによる描画の終了
		pDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	pDevice->Present(NULL, NULL, NULL, NULL);
}


