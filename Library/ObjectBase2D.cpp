#include "ObjectBase2D.h"
#include <math.h>
#include "Math.h"


/* 最基底クラス */
_ObjectBase2D::_ObjectBase2D()
{
	Texture = NULL;

	Vertex[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Vertex[1].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Vertex[2].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Vertex[3].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Vertex[0].rhw = 1.0f;
	Vertex[1].rhw = 1.0f;
	Vertex[2].rhw = 1.0f;
	Vertex[3].rhw = 1.0f;

	Vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

int  _ObjectBase2D::Init()
{
	Texture = NULL;

	Vertex[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Vertex[1].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Vertex[2].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Vertex[3].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Vertex[0].rhw = 1.0f;
	Vertex[1].rhw = 1.0f;
	Vertex[2].rhw = 1.0f;
	Vertex[3].rhw = 1.0f;

	Vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return 0;
}
void _ObjectBase2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, Texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, Vertex, sizeof(VERTEX_2D));
}
void _ObjectBase2D::Draw(LPDIRECT3DTEXTURE9 texture)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, Vertex, sizeof(VERTEX_2D));
}

void _ObjectBase2D::MakeVertex(float sizeX, float sizeY, float posX, float posY)
{
	// 頂点座標の設定
	Vertex[0].vtx = D3DXVECTOR3(-sizeX + posX, -sizeY + posY, 0.0f);
	Vertex[1].vtx = D3DXVECTOR3( sizeX + posX, -sizeY + posY, 0.0f);
	Vertex[2].vtx = D3DXVECTOR3(-sizeX + posX,  sizeY + posY, 0.0f);
	Vertex[3].vtx = D3DXVECTOR3( sizeX + posX,  sizeY + posY, 0.0f);

	// テクスチャのパースペクティブコレクト用
	Vertex[0].rhw =
	Vertex[1].rhw =
	Vertex[2].rhw =
	Vertex[3].rhw = 1.0f;

	// 反射光の設定
	Vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}
void _ObjectBase2D::MakeVertex(float sizeX, float sizeY)
{
	// 頂点座標の設定
	Vertex[0].vtx = D3DXVECTOR3(-sizeX, -sizeY, 0.0f);
	Vertex[1].vtx = D3DXVECTOR3(sizeX, -sizeY, 0.0f);
	Vertex[2].vtx = D3DXVECTOR3(-sizeX, sizeY, 0.0f);
	Vertex[3].vtx = D3DXVECTOR3(sizeX, sizeY, 0.0f);

	// テクスチャのパースペクティブコレクト用
	Vertex[0].rhw =
	Vertex[1].rhw =
	Vertex[2].rhw =
	Vertex[3].rhw = 1.0f;

	// 反射光の設定
	Vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}
void _ObjectBase2D::SetVertex(float sizeX, float sizeY, float posX, float posY)
{
	Vertex[0].vtx = D3DXVECTOR3(-sizeX + posX, -sizeY + posY, 0.0f);
	Vertex[1].vtx = D3DXVECTOR3( sizeX + posX, -sizeY + posY, 0.0f);
	Vertex[2].vtx = D3DXVECTOR3(-sizeX + posX,  sizeY + posY, 0.0f);
	Vertex[3].vtx = D3DXVECTOR3( sizeX + posX,  sizeY + posY, 0.0f);
}
void _ObjectBase2D::SetVertex(float sizeX, float sizeY)
{
	Vertex[0].vtx = D3DXVECTOR3(-sizeX, -sizeY, 0.0f);
	Vertex[1].vtx = D3DXVECTOR3( sizeX, -sizeY, 0.0f);
	Vertex[2].vtx = D3DXVECTOR3(-sizeX,  sizeY, 0.0f);
	Vertex[3].vtx = D3DXVECTOR3( sizeX,  sizeY, 0.0f);
}
void _ObjectBase2D::SetVertex(D3DXCOLOR color)
{
	Vertex[0].diffuse = color;
	Vertex[1].diffuse = color;
	Vertex[2].diffuse = color;
	Vertex[3].diffuse = color;
}
void _ObjectBase2D::SetTexture(int num, int ix, int iy)
{
	int x = num % ix;
	int y = num / ix;
	float sizeX = 1.0f / ix;
	float sizeY = 1.0f / iy;
	Vertex[0].tex = D3DXVECTOR2((float)(x) * sizeX,         (float)(y) * sizeY);
	Vertex[1].tex = D3DXVECTOR2((float)(x) * sizeX + sizeX, (float)(y) * sizeY);
	Vertex[2].tex = D3DXVECTOR2((float)(x) * sizeX,         (float)(y) * sizeY + sizeY);
	Vertex[3].tex = D3DXVECTOR2((float)(x) * sizeX + sizeX, (float)(y) * sizeY + sizeY);
}

LPDIRECT3DTEXTURE9 _ObjectBase2D::GetTexture(LPDIRECT3DTEXTURE9 *texture)
{
	*texture = Texture;
	return Texture;
}

void _ObjectBase2D::Release(void)
{
	if (Texture != NULL)
	{
		Texture->Release();
		Texture = NULL;
	}
}
void _ObjectBase2D::LoadTexture(const char *texture)
{
	if (Texture != NULL)
	{
		Texture->Release();
		Texture = NULL;
	}
	D3DXCreateTextureFromFile(GetDevice(), texture, &Texture);
}
void _ObjectBase2D::LoadTexture(LPDIRECT3DTEXTURE9 texture)
{
	// テクスチャの読み込み
	Texture = texture;
}


/* 2Dオブジェクト */
int  C2DObject::Init(const char *texture)
{
	this->ObjectBase2D::Init();
	this->Texture = NULL;
	this->Position = D3DXVECTOR2(0.0f, 0.0f);
	this->Size = D3DXVECTOR2(0.0f, 0.0f);
	this->Scale = 1.0f;
	this->Angle = 0.0f;
	this->LoadTexture(texture);
	SetVertex();
	return 0;
}
int  C2DObject::Init(D3DXCOLOR color)
{
	this->ObjectBase2D::Init();
	SetVertex();
	SetVertex(color);
	return 0;
}
int  C2DObject::Init(float posX, float posY, float sizX, float sizY, const char *texture)
{
	this->_ObjectBase2D::Init();
	this->Texture = NULL;
	this->Position = D3DXVECTOR2(posX, posY);
	this->Size = D3DXVECTOR2(sizX, sizY);
	this->Scale = 1.0f;
	this->Angle = 0.0f;
	this->LoadTexture(texture);
	SetVertex();
	return 0;
}
int  C2DObject::Init(float posX, float posY, float sizX, float sizY)
{
	this->_ObjectBase2D::Init();
	this->Texture = NULL;
	this->Position = D3DXVECTOR2(posX, posY);
	this->Size = D3DXVECTOR2(sizX, sizY);
	this->Scale = 1.0f;
	this->Angle = 0.0f;
	SetVertex();
	return 0;
}
void C2DObject::SetVertex()
{
	Vertex[0].vtx.x = Position.x - cosf((D3DX_PI * 0.25f) + Angle) * ROOT2 * Size.x * Scale;
	Vertex[0].vtx.y = Position.y - sinf((D3DX_PI * 0.25f) + Angle) * ROOT2 * Size.y * Scale;
	Vertex[0].vtx.z = 0.0f;
	Vertex[1].vtx.x = Position.x + cosf((D3DX_PI * 0.25f) - Angle) * ROOT2 * Size.x * Scale;
	Vertex[1].vtx.y = Position.y - sinf((D3DX_PI * 0.25f) - Angle) * ROOT2 * Size.y * Scale;
	Vertex[1].vtx.z = 0.0f;
	Vertex[2].vtx.x = Position.x - cosf((D3DX_PI * 0.25f) - Angle) * ROOT2 * Size.x * Scale;
	Vertex[2].vtx.y = Position.y + sinf((D3DX_PI * 0.25f) - Angle) * ROOT2 * Size.y * Scale;
	Vertex[2].vtx.z = 0.0f;
	Vertex[3].vtx.x = Position.x + cosf((D3DX_PI * 0.25f) + Angle) * ROOT2 * Size.x * Scale;
	Vertex[3].vtx.y = Position.y + sinf((D3DX_PI * 0.25f) + Angle) * ROOT2 * Size.y * Scale;
	Vertex[3].vtx.z = 0.0f;
}
void C2DObject::SetVertex(int no, D3DXVECTOR3 vtx)
{
	Vertex[no].vtx = vtx;
}
void C2DObject::SetVertex(        D3DCOLOR    dif)
{
	Vertex[0].diffuse = dif;
	Vertex[1].diffuse = dif;
	Vertex[2].diffuse = dif;
	Vertex[3].diffuse = dif;
}
void C2DObject::SetVertex(int no, D3DCOLOR    dif)
{
	Vertex[0].diffuse = dif;
}
void C2DObject::SetVertex(int no, D3DXVECTOR2 tex)
{
	Vertex[0].tex = tex;
}

void C2DObject::SetStatus(float posX, float posY, float sizX, float sizY)
{
	this->Position.x = posX;
	this->Position.y = posY;
	this->Size.x = sizX;
	this->Size.y = sizY;
}
void C2DObject::SetStatus(D3DXVECTOR2 pos, D3DXVECTOR2 siz, float scl, float ang)
{
	this->Position = pos;
	this->Size = siz;
	this->Scale = scl;
	this->Angle = ang;
}
void C2DObject::SetStatus(D3DXVECTOR2 pos, D3DXVECTOR2 siz)
{
	this->Position = pos;
	this->Size = siz;
}
void C2DObject::SetStatus(float scl, float ang)
{
	this->Scale = scl;
	this->Angle = ang;
}


/* 背景UI */
UIBackGround::UIBackGround()
{
	Vertex[0].vtx = D3DXVECTOR3(        0.0f,          0.0f, 0.0f);
	Vertex[1].vtx = D3DXVECTOR3(SCREEN_WIDTH,          0.0f, 0.0f);
	Vertex[2].vtx = D3DXVECTOR3(        0.0f, SCREEN_HEIGHT, 0.0f);
	Vertex[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
}
UIBackGround::UIBackGround(const char *texture)
{
	this->LoadTexture(texture);
	Vertex[0].vtx = D3DXVECTOR3(        0.0f,          0.0f, 0.0f);
	Vertex[1].vtx = D3DXVECTOR3(SCREEN_WIDTH,          0.0f, 0.0f);
	Vertex[2].vtx = D3DXVECTOR3(        0.0f, SCREEN_HEIGHT, 0.0f);
	Vertex[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
}


/* 2DUIアニメーション */
int  UI2DAnimation::Init(const char *texture)
{
	this->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	this->Curve = 0.0f;
	this->C2DObject::Init(texture);
	return 0;
}
int  UI2DAnimation::Init(float posX, float posY, float sizX, float sizY, const char *texture)
{
	this->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	this->Curve = 0.0f;
	this->C2DObject::Init(posX, posY, sizX, sizY, texture);
	return 0;
}
void UI2DAnimation::ResetData(int type)
{
	if (type)
	{
		this->Position = D3DXVECTOR2(0.0f, 0.0f);
		this->Size = D3DXVECTOR2(0.0f, 0.0f);
	}
	this->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	this->Scale = 1.0f;
	this->Angle = 0.0f;
	this->Curve = 0.0f;
}
void UI2DAnimation::Animation01()
{
	Curve += 0.0625f;
	Scale = sinf(Curve) * 0.1f + 1.0f;
	SetVertex();
}


/* 2DUI数字 */
void UI2DNumber::SetNumber(int num)
{
	this->SetTexture(num, 10, 1);
}


/* パーセントゲージ */
void UI2DPercentGauge::Init(const char *textureF, const char *textureG)
{
	Frame.Init(textureF);
	Gage.Init(textureG);
}
void UI2DPercentGauge::Init(float posX, float posY, float sizeX, float sizeY)
{
	float cor = sizeX * 0.04f;
	Position = D3DXVECTOR2(posX, posY);
	Size = D3DXVECTOR2(sizeX - cor, sizeY - cor);
	Frame.SetStatus(D3DXVECTOR2(sizeX, sizeY), D3DXVECTOR2(posX, posY));
	Gage.SetStatus(D3DXVECTOR2(sizeX - cor, sizeY - cor), D3DXVECTOR2(posX, posY));
}
void UI2DPercentGauge::Uninit(void)
{
	Frame.Release();
	Gage.Release();
}
void UI2DPercentGauge::Update(float per)
{
	Gage.SetVertex(0, D3DXVECTOR3(Position.x - Size.x, Position.y - Size.y, 0.0f));
	Gage.SetVertex(1, D3DXVECTOR3(Position.x - Size.x + Size.x * 2 * per, Position.y - Size.y, 0.0f));
	Gage.SetVertex(2, D3DXVECTOR3(Position.x - Size.x, Position.y + Size.y, 0.0f));
	Gage.SetVertex(3, D3DXVECTOR3(Position.x - Size.x + Size.x * 2 * per, Position.y + Size.y, 0.0f));
}
void UI2DPercentGauge::Draw(void)
{
	Frame.Draw();
	Gage.Draw();
}

