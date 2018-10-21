//=============================================================================
//
// メイン処理 [main.cpp]
//
//=============================================================================
#include "Library/Common.h"
#include "Library/TsuLibSystem.h"
#include "Library/WindowClass.h"
#include "Library/Direct3D.h"
#include "Library/FPSManager.h"
#include "Library/Input.h"
#include "Library/Sound.h"
#include "Library/Fade.h"
#include "Library/Camera.h"
#include "Library/Light.h"
#include "Library/Dx9Line.h"
#include "Library/DebugProcess.h"
#include "SceneManager.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Init();
void Uninit(void);
void Update(void);
void Draw(void);


//*****************************************************************************
// グローバル変数:
//*****************************************************************************
bool g_bDispDebug = true;	// デバッグ表示ON/OFF


//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	// TSUシステムを初期化
	if (FAILED(TsuSystem::Initialize(hInstance)))
		return -1;

	// その他初期化
	if (FAILED(Init()))
		return -1;

	//フレームカウント初期化
	timeBeginPeriod(1);	// 分解能設定
	FPSManager::Init();	// FPS制御

	/* メッセージループ */
	while (1)
	{
		if (WindowClass::CheckMessage())
			break;

		if (FPSManager::FramerateControl())
		{
			PrintDebugProcess("FPS : %f\n", FPSManager::DisplayFPS(FPS_NORMAL));
			PrintDebugProcess("SCENE : ");
			switch (Scene::SetScene(SCENE_MAX))
			{
			case SCENE_TITLE:   PrintDebugProcess("Title\n");   break;
			case SCENE_GAME:    PrintDebugProcess("Game\n");   break;
			case SCENE_RESULT:  PrintDebugProcess("Result\n");   break;
			case SCENE_MAX:     PrintDebugProcess("処理中...\n");   break;
			case SCENE_END:     PrintDebugProcess("終了処理です(表示されないはずだよ)\n");   break;
			}

			Update();	// 更新処理
			Draw();		// 描画処理
		}
	}

	TsuSystem::Uninitialize();	// TSUシステムを初期化
	Uninit();					// その他終了処理

	timeEndPeriod(1);	// 分解能を戻す

	return 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init()
{
	// フェード
	CSFade::MakeVertex();

	// タイトルシーンにセット
	Scene::SetScene(SCENE_GAME);

	// カメラ
	InitCamera();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	Scene::SetScene(SCENE_END);

}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// 入力の更新処理
	UpdateInput();

	if (GetKeyboardTrigger(DIK_F3))
	{// デバッグ表示ON/OFF
		g_bDispDebug = g_bDispDebug ? false : true;
	}

	// シーンの更新
	Scene::Update();

	// フェード処理の更新
	CSFade::Update();

}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	Direct3D::GetD3DDevice()->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0x66, 0x88, 0xFF, 0xFF), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(Direct3D::GetD3DDevice()->BeginScene()))
	{
		// シーンの描画
		Scene::Draw();

		// フェード描画
		CSFade::Draw();
		TsuSystem::CoordinateAxis();

		// デバッグ表示の描画処理
		if (g_bDispDebug)
		{
			DrawDebugProcess();
		}
		Dx9Line::Draw();

		// Direct3Dによる描画の終了
		Direct3D::GetD3DDevice()->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	Direct3D::GetD3DDevice()->Present(NULL, NULL, NULL, NULL);
}


