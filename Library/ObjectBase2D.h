#ifndef __CLASS_2D_OBJECT_BASE_INCLUDE_H__
#define __CLASS_2D_OBJECT_BASE_INCLUDE_H__


#include "Polygon.h"
#include "Texture.h"


/* 2D基礎クラス */
typedef class _ObjectBase2D
{
protected:
	Dx9Texture	Texture;					// テクスチャへのポインタ
	Vertex2D	Vertex[RECT_NUM_VERTEX];	// 頂点情報

	virtual void MakeVertex(float sizeX, float sizeY, float posX, float posY);	// 頂点作成
	virtual void MakeVertex(float sizeX, float sizeY);

public:
	_ObjectBase2D();

	virtual int  Init();
	virtual void Draw(void);				// 描画処理(通常)
	virtual void Draw(LPDx3DTex9 texture);	// 描画処理(指定)

	virtual void Release(void);				// バッファ系開放
	virtual void LoadTexture(const char *texture);
	virtual void LoadTexture(LPDx3DTex9 texture);

	virtual void SetVertex(float sizeX, float sizeY, float posX, float posY);	// 頂点座標設定
	virtual void SetVertex(float sizeX, float sizeY);
	virtual void SetVertex(D3DXCOLOR color);
	virtual void SetTexture(int num, int ix, int iy);	// テクスチャ座標設定

	virtual LPDx3DTex9 GetTexture(LPDx3DTex9 *texture);

}ObjectBase2D;


/* 2Dオブジェクト */
class C2DObject : public _ObjectBase2D
{
protected:
	Vector2 Position;
	Vector2 Size;
	float   Scale;
	float   Angle;

public:
	virtual int  Init(const char *texture);
	virtual int  Init(D3DXCOLOR color);
	virtual int  Init(float posX, float posY, float sizX, float sizY, const char *texture);
	virtual int  Init(float posX, float posY, float sizX, float sizY);
	virtual void SetVertex();
	        void SetVertex(int no, Vector3 vtx);
	        void SetVertex(DxColor dif);
	        void SetVertex(int no, DxColor dif);
	        void SetVertex(int no, Vector2 tex);

	virtual void SetStatus(float posX, float posY, float sizX, float sizY);
	virtual void SetStatus(Vector2 pos, Vector2 siz, float scl, float ang);
	virtual void SetStatus(Vector2 pos, Vector2 siz);
	virtual void SetStatus(float scl, float ang);

};


/* 背景UI (画面と同サイズ) */
class UIBackGround : public _ObjectBase2D
{
public:
	UIBackGround();
	UIBackGround(const char *texture);

};


/* 2DUI数字 */
class UI2DNumber : public C2DObject
{
public:
	void SetNumber(int num);

};


/* 2DUIゲージバー */
class UI2DPercentGauge
{
	Vector2 Position;
	Vector2 Size;

public:
	C2DObject   Frame;
	C2DObject   Gage;

	void Init(const char *textureF, const char *textureG);
	void Init(float sizeX, float sizeY, float posX, float posY);
	void Update(float per);
	void Draw(void);
	void Uninit(void);

};





#endif // !__CLASS_OBJECT_INCLUDE__

