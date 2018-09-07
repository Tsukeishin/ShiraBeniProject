//=============================================================================
//
// フェード処理 <Fade.cpp>
//
//=============================================================================
#include "Fade.h"
#include "Common.h"
#include "Direct3D.h"

/* マクロ定義 */
#define	FADE_RATE		(0.1f)		// フェード係数


/* グローバル変数 */
VERTEX_2D	CSFade::Vertex[NUM_VERTEX];
D3DXCOLOR	CSFade::Color     = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
GAMESCENE	CSFade::GameScene = SCENE_MAX;
FADE		CSFade::Fade      = FADE_IN;
float		CSFade::Speed     = FADE_RATE;

//----更新--------
void CSFade::Update(void)
{
	if(Fade != FADE_NONE)
	{// フェード処理中
		if(Fade == FADE_OUT)
		{// フェードアウト処理
			Color.a += Speed;		// α値を加算して画面を消していく
			if(Color.a > 1.1f)
			{
				// モードを設定
				SetGameScene(GameScene);

				// フェードイン処理に切り替え
				Color.a = 1.0f;
				SetFade(FADE_IN, SCENE_MAX, Speed);
			}

			// 色を設定
			SetColor();
		}
		else if(Fade == FADE_IN)
		{// フェードイン処理
			Color.a -= Speed;		// α値を減算して画面を浮き上がらせる
			if(Color.a < 0.0f)
			{
				// フェード処理終了
				Color.a = 0.0f;
				SetFade(FADE_NONE, SCENE_MAX, Speed);
			}

			// 色を設定
			SetColor();
		}
	}
}

//----描画--------
void CSFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, Vertex, sizeof(VERTEX_2D));
}

//----頂点作成--------
void CSFade::MakeVertex(void)
{
	// 頂点座標の設定
	Vertex[0].vtx = D3DXVECTOR3(        0.0f,          0.0f, 0.0f);
	Vertex[1].vtx = D3DXVECTOR3(SCREEN_WIDTH,          0.0f, 0.0f);
	Vertex[2].vtx = D3DXVECTOR3(        0.0f, SCREEN_HEIGHT, 0.0f);
	Vertex[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// テクスチャのパースペクティブコレクト用
	Vertex[0].rhw = 1.0f;
	Vertex[1].rhw = 1.0f;
	Vertex[2].rhw = 1.0f;
	Vertex[3].rhw = 1.0f;

	// 反射光の設定
	Vertex[0].diffuse = Color;
	Vertex[1].diffuse = Color;
	Vertex[2].diffuse = Color;
	Vertex[3].diffuse = Color;

	// テクスチャ座標の設定
	Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//----色を設定--------
void CSFade::SetColor(D3DCOLOR col)
{
	Color = col;
}
void CSFade::SetColor(void)
{
	// 反射光の設定
	Vertex[0].diffuse = Color;
	Vertex[1].diffuse = Color;
	Vertex[2].diffuse = Color;
	Vertex[3].diffuse = Color;
}

//----フェードの設定--------
void CSFade::SetFade(float spd)
{
	Fade = FADE_OUT;
	GameScene = SCENE_MAX;
	Speed = spd;
	Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}
void CSFade::SetFade(float spd, D3DCOLOR col)
{
	Fade = FADE_OUT;
	GameScene = SCENE_MAX;
	Speed = spd;
	Color = col;
}
void CSFade::SetFade(GAMESCENE scene)
{
	Fade = FADE_OUT;
	GameScene = scene;
	Speed = FADE_RATE;
	Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}
void CSFade::SetFade(GAMESCENE scene, float spd)
{
	Fade = FADE_OUT;
	GameScene = scene;
	Speed = spd;
	Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}
void CSFade::SetFade(FADE fade, GAMESCENE scene, float spd)
{
	Fade = fade;
	GameScene = scene;
	Speed = spd;
	Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//----フェードの状態取得--------
FADE CSFade::GetFade(void)
{
	return Fade;
}

