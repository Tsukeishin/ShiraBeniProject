//=============================================================================
//
// フェード処理 <Fade.h>
//
//=============================================================================
#ifndef __FADE_INCLUDE_H__
#define __FADE_INCLUDE_H__

#include "LinkLibrary.h"

/* フェードの状態 */
typedef enum
{
	FADE_NONE = 0,		// 何もない状態
	FADE_IN,			// フェードイン処理
	FADE_OUT,			// フェードアウト処理
	FADE_MAX
} FADE;


class CSFade
{
	static VERTEX_2D	Vertex[NUM_VERTEX];
	static D3DXCOLOR	Color;
	static GAMESCENE	GameScene;
	static FADE			Fade;
	static float		Speed;

public:
	static void Update(void);
	static void Draw(void);

	static void MakeVertex(void);
	static void SetColor(D3DCOLOR col);
	static void SetColor(void);
	static void SetFade(float spd);
	static void SetFade(float spd, D3DCOLOR col);
	static void SetFade(GAMESCENE scene);
	static void SetFade(GAMESCENE scene, float spd);
	static void SetFade(FADE fade, GAMESCENE scene, float spd);
	static FADE GetFade(void);

private:


};



#endif
