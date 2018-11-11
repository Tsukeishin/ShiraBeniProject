#include "Direct3D.h"
#include "Common.h"


LPDIRECT3D9             Direct3D::dx_pD3D       = NULL;	// Direct3Dオブジェクト
LPDIRECT3DDEVICE9       Direct3D::dx_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)
D3DPRESENT_PARAMETERS   Direct3D::dxD3Dpp       = {};	// プレゼンテーションパラメータ


//----初期化処理--------
HRESULT Direct3D::Init(HWND hWnd, bool bWindowMode)
{
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	dx_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (dx_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(dx_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&dxD3Dpp, sizeof(dxD3Dpp));			// ワークをゼロクリア
	dxD3Dpp.BackBufferCount  = 1;					// バックバッファの数
	dxD3Dpp.BackBufferWidth  = SCREEN_WIDTH;		// ゲーム画面サイズ(幅)
	dxD3Dpp.BackBufferHeight = SCREEN_HEIGHT;		// ゲーム画面サイズ(高さ)
	dxD3Dpp.BackBufferFormat = d3ddm.Format;		// カラーモードの指定
	dxD3Dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	dxD3Dpp.Windowed = bWindowMode;				// ウィンドウモード
	dxD3Dpp.EnableAutoDepthStencil = TRUE;		// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	dxD3Dpp.AutoDepthStencilFormat = D3DFMT_D16;	// デプスバッファとして16bitを使う

	if (bWindowMode)
	{// ウィンドウモード
		dxD3Dpp.FullScreen_RefreshRateInHz = 0;						// リフレッシュレート
		dxD3Dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		dxD3Dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
		dxD3Dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル
	}

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(dx_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&dxD3Dpp, &dx_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(dx_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&dxD3Dpp, &dx_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(dx_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&dxD3Dpp, &dx_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}


	/* レンダリングステートパラメータの設定 */
	dx_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
//	dx_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);			// 裏面も表示
	dx_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	dx_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// αブレンドを行う(offにすると軽くなる)
	dx_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	dx_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
//	dx_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);		// αディストネーションカラーの指定

	/* サンプラーステートパラメータの設定 */
	dx_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	dx_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	dx_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	dx_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	/* テクスチャステージ加算合成処理 */
	dx_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	dx_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	dx_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

	/* ライティングモードを有効 */
	dx_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


	return S_OK;
}

//----終了処理--------
void Direct3D::Uninit()
{
	if (dx_pD3DDevice != NULL)
	{// デバイスの開放
		dx_pD3DDevice->Release();
		dx_pD3DDevice = NULL;
	}

	if (dx_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		dx_pD3D->Release();
		dx_pD3D = NULL;
	}
}

//----デバイスのリセット
void Direct3D::ResetDevice()
{
	dx_pD3DDevice->Reset(&dxD3Dpp);

	/* レンダリングステートパラメータの設定 */
	dx_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
//	dx_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);			// 裏面も表示
	dx_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	dx_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// αブレンドを行う(offにすると軽くなる)
	dx_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	dx_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
//	dx_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);		// αディストネーションカラーの指定

	/* サンプラーステートパラメータの設定 */
	dx_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	dx_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	dx_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	dx_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	/* テクスチャステージ加算合成処理 */
	dx_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	dx_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	dx_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

	/* ライティングモードを有効 */
	dx_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}


//----取得関数--------
LPDIRECT3DDEVICE9 Direct3D::GetD3DDevice()
{
	return Direct3D::dx_pD3DDevice;
}

