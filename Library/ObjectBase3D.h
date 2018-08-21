#ifndef __CLASS_3D_OBJECT_BASE_H_INCLUDE__
#define __CLASS_3D_OBJECT_BASE_H_INCLUDE__

#include "LinkLibrary.h"

/* 3Dオブジェクト基礎クラス */
class _ObjectBase3D
{
protected:
	LPDIRECT3DTEXTURE9		Texture;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;

public:
	_ObjectBase3D();

	virtual int  Init() { return 1; };
	virtual int  Update() { return 1; };
	virtual void Draw() {};
	virtual void Uninit() { this->Release(); };

	virtual void LoadTexture(const char *texture);			// 前テクスチャはクリア(開放あり)
	virtual void LoadTexture(LPDIRECT3DTEXTURE9 texture);	// 前テクスチャはリリース(開放なし)
	virtual void Release();
	virtual void ReleaseVertex();
};


/* 3Dポリゴンオブジェクト */
class C3DPolygonObject : public _ObjectBase3D
{
protected:
	D3DXVECTOR3 Position;	// 位置座標
	D3DXVECTOR3 Rotation;	// 回転角度
	D3DXVECTOR2 Size;		// ポリゴンサイズ
	float       Scale;		// サイズ倍率

	int TexPattern_X;		// テクスチャパターン（横）
	int TexPattern_Y;		// テクスチャパターン（縦）
	int AnimeCount;			// アニメーションカウント
	int AnimePattern;		// 現在のアニメーションパターン番号
	int ChangeAnimeTime;	// アニメーション切り替え待時間

	virtual int  MakeVertex(void);
	virtual void SetVertex(void);				// 頂点座標設定@頂点位置のみ
	virtual void SetVertex(D3DXCOLOR color);	// 頂点座標設定@頂点色込み

public:
	C3DPolygonObject();

	virtual void Init(float posX, float posY, float posZ, float sizX, float sizY);
	virtual void Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	virtual void Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 size);
	virtual void Draw(void);

	virtual void LoadTextureStatus(float sizX, float sizY, float scale, int ptnX, int ptnY, int time);
	virtual void LoadTextureStatus(float sizX, float sizY, float scale);
	virtual void LoadObjectStatus(D3DXVECTOR3 pos);
	virtual void LoadObjectStatus(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
};

/* 3D多数板ポリオブジェクト */
class C3DMultiPolygonObject : public C3DPolygonObject
{
public:
	void Release();
};


/* 3D六面体オブジェクト *///*
class C3DCubeObject
{
	LPDIRECT3DTEXTURE9 Texture;
	VERTEX_3D          Face[6][4];
	D3DXVECTOR3 Position;	// 位置座標
	D3DXVECTOR3 Rotation;	// 回転角度
	D3DXVECTOR3 Size;		// ポリゴンサイズ

public:
	C3DCubeObject();

	void LoadTexture(const char *texture);
	void Release();

	int  Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	int  Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	int  Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float size);
	int  Init(D3DXVECTOR3 pos, float size);

	void Draw();

private:
	int  MakeVertex(void);

};







#endif // !__CLASS_OBJECT_INCLUDE__

