//=============================================================================
//
// �t�F�[�h���� <Fade.h>
//
//=============================================================================
#ifndef __FADE_H_INCLUDE__
#define __FADE_H_INCLUDE__

//#include "Texture.h"
#include "Polygon.h"

/* �t�F�[�h�̏�� */
typedef enum
{
	FADE_NONE = 0,		// �����Ȃ����
	FADE_IN,			// �t�F�[�h�C������
	FADE_OUT,			// �t�F�[�h�A�E�g����
	FADE_MAX
} FADE;


class CSFade
{
	static Vertex2D		Vertex[RECT_NUM_VERTEX];
	static D3DXCOLOR	Color;
//	static GAMESCENE	GameScene;
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
//	static void SetFade(GAMESCENE scene);
//	static void SetFade(GAMESCENE scene, float spd);
//	static void SetFade(FADE fade, GAMESCENE scene, float spd);
	static FADE GetFade(void);

};



#endif
