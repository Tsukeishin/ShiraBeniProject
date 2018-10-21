#include "ObjectBase2D.h"
#include "Common.h"
#include "Direct3D.h"
#include "Math.h"
#include <math.h>


/* 最基底クラス */
_ObjectBase2D::_ObjectBase2D()
{
	Texture = NULL;

	Vertex[0].coord = Vector3(0.0f, 0.0f, 0.0f);
	Vertex[1].coord = Vector3(0.0f, 0.0f, 0.0f);
	Vertex[2].coord = Vector3(0.0f, 0.0f, 0.0f);
	Vertex[3].coord = Vector3(0.0f, 0.0f, 0.0f);

	Vertex[0].rhw = 1.0f;
	Vertex[1].rhw = 1.0f;
	Vertex[2].rhw = 1.0f;
	Vertex[3].rhw = 1.0f;

	Vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	Vertex[0].uv = Vector2(0.0f, 0.0f);
	Vertex[1].uv = Vector2(1.0f, 0.0f);
	Vertex[2].uv = Vector2(0.0f, 1.0f);
	Vertex[3].uv = Vector2(1.0f, 1.0f);
}

int  _ObjectBase2D::Init()
{
	Texture = NULL;

	Vertex[0].coord = Vector3(0.0f, 0.0f, 0.0f);
	Vertex[1].coord = Vector3(0.0f, 0.0f, 0.0f);
	Vertex[2].coord = Vector3(0.0f, 0.0f, 0.0f);
	Vertex[3].coord = Vector3(0.0f, 0.0f, 0.0f);

	Vertex[0].rhw = 1.0f;
	Vertex[1].rhw = 1.0f;
	Vertex[2].rhw = 1.0f;
	Vertex[3].rhw = 1.0f;

	Vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	Vertex[0].uv = Vector2(0.0f, 0.0f);
	Vertex[1].uv = Vector2(1.0f, 0.0f);
	Vertex[2].uv = Vector2(0.0f, 1.0f);
	Vertex[3].uv = Vector2(1.0f, 1.0f);

	return 0;
}
void _ObjectBase2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, Texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, RECT_NUM_POLYGON, Vertex, sizeof(VERTEX_2D));
}
void _ObjectBase2D::Draw(LPDx3DTex9 texture)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, RECT_NUM_POLYGON, Vertex, sizeof(VERTEX_2D));
}

void _ObjectBase2D::MakeVertex(float sizeX, float sizeY, float posX, float posY)
{
	// 頂点座標の設定
	Vertex[0].coord = Vector3(-sizeX + posX, -sizeY + posY, 0.0f);
	Vertex[1].coord = Vector3( sizeX + posX, -sizeY + posY, 0.0f);
	Vertex[2].coord = Vector3(-sizeX + posX,  sizeY + posY, 0.0f);
	Vertex[3].coord = Vector3( sizeX + posX,  sizeY + posY, 0.0f);

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
	Vertex[0].uv = Vector2(0.0f, 0.0f);
	Vertex[1].uv = Vector2(1.0f, 0.0f);
	Vertex[2].uv = Vector2(0.0f, 1.0f);
	Vertex[3].uv = Vector2(1.0f, 1.0f);
}
void _ObjectBase2D::MakeVertex(float sizeX, float sizeY)
{
	// 頂点座標の設定
	Vertex[0].coord = Vector3(-sizeX, -sizeY, 0.0f);
	Vertex[1].coord = Vector3(sizeX, -sizeY, 0.0f);
	Vertex[2].coord = Vector3(-sizeX, sizeY, 0.0f);
	Vertex[3].coord = Vector3(sizeX, sizeY, 0.0f);

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
	Vertex[0].uv = Vector2(0.0f, 0.0f);
	Vertex[1].uv = Vector2(1.0f, 0.0f);
	Vertex[2].uv = Vector2(0.0f, 1.0f);
	Vertex[3].uv = Vector2(1.0f, 1.0f);
}
void _ObjectBase2D::SetVertex(float sizeX, float sizeY, float posX, float posY)
{
	Vertex[0].coord = Vector3(-sizeX + posX, -sizeY + posY, 0.0f);
	Vertex[1].coord = Vector3( sizeX + posX, -sizeY + posY, 0.0f);
	Vertex[2].coord = Vector3(-sizeX + posX,  sizeY + posY, 0.0f);
	Vertex[3].coord = Vector3( sizeX + posX,  sizeY + posY, 0.0f);
}
void _ObjectBase2D::SetVertex(float sizeX, float sizeY)
{
	Vertex[0].coord = Vector3(-sizeX, -sizeY, 0.0f);
	Vertex[1].coord = Vector3( sizeX, -sizeY, 0.0f);
	Vertex[2].coord = Vector3(-sizeX,  sizeY, 0.0f);
	Vertex[3].coord = Vector3( sizeX,  sizeY, 0.0f);
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
	Vertex[0].uv = Vector2((float)(x) * sizeX,         (float)(y) * sizeY);
	Vertex[1].uv = Vector2((float)(x) * sizeX + sizeX, (float)(y) * sizeY);
	Vertex[2].uv = Vector2((float)(x) * sizeX,         (float)(y) * sizeY + sizeY);
	Vertex[3].uv = Vector2((float)(x) * sizeX + sizeX, (float)(y) * sizeY + sizeY);
}

LPDx3DTex9 _ObjectBase2D::GetTexture(LPDx3DTex9 *texture)
{
	*texture = Texture;
	return Texture;
}

void _ObjectBase2D::Release(void)
{
	this->Texture.Release();
}
void _ObjectBase2D::LoadTexture(const char *texture)
{
	this->Texture.LoadTexture(texture);
}
void _ObjectBase2D::LoadTexture(LPDx3DTex9 texture)
{
	// テクスチャの読み込み
	Texture = texture;
}


/* 2Dオブジェクト */
int  C2DObject::Init(const char *texture)
{
	this->ObjectBase2D::Init();
	this->Texture = NULL;
	this->Position = Vector2(0.0f, 0.0f);
	this->Size = Vector2(0.0f, 0.0f);
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
	this->Position = Vector2(posX, posY);
	this->Size = Vector2(sizX, sizY);
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
	this->Position = Vector2(posX, posY);
	this->Size = Vector2(sizX, sizY);
	this->Scale = 1.0f;
	this->Angle = 0.0f;
	SetVertex();
	return 0;
}
void C2DObject::SetVertex()
{
	float cosA = cosf(Angle);
	float sinA = sinf(Angle);
	Vertex[0].coord.x = Position.x + (-cosA * Size.x - sinA * Size.y) * Scale;
	Vertex[0].coord.y = Position.y + (-cosA * Size.y + sinA * Size.x) * Scale;
	Vertex[0].coord.z = 0.0f;
	Vertex[1].coord.x = Position.x + ( cosA * Size.x - sinA * Size.y) * Scale;
	Vertex[1].coord.y = Position.y + (-cosA * Size.y - sinA * Size.x) * Scale;
	Vertex[1].coord.z = 0.0f;
	Vertex[2].coord.x = Position.x + (-cosA * Size.x + sinA * Size.y) * Scale;
	Vertex[2].coord.y = Position.y + ( cosA * Size.y + sinA * Size.x) * Scale;
	Vertex[2].coord.z = 0.0f;
	Vertex[3].coord.x = Position.x + ( cosA * Size.x + sinA * Size.y) * Scale;
	Vertex[3].coord.y = Position.y + ( cosA * Size.y - sinA * Size.x) * Scale;
	Vertex[3].coord.z = 0.0f;
}
void C2DObject::SetVertex(int no, Vector3 coord)
{
	Vertex[no].coord = coord;
}
void C2DObject::SetVertex(        DxColor dif)
{
	Vertex[0].diffuse = dif;
	Vertex[1].diffuse = dif;
	Vertex[2].diffuse = dif;
	Vertex[3].diffuse = dif;
}
void C2DObject::SetVertex(int no, DxColor dif)
{
	Vertex[0].diffuse = dif;
}
void C2DObject::SetVertex(int no, Vector2 uv)
{
	Vertex[0].uv = uv;
}

void C2DObject::SetStatus(float posX, float posY, float sizX, float sizY)
{
	this->Position.x = posX;
	this->Position.y = posY;
	this->Size.x = sizX;
	this->Size.y = sizY;
	this->SetVertex();
}
void C2DObject::SetStatus(Vector2 pos, Vector2 siz, float scl, float ang)
{
	this->Position = pos;
	this->Size = siz;
	this->Scale = scl;
	this->Angle = ang;
	this->SetVertex();
}
void C2DObject::SetStatus(Vector2 pos, Vector2 siz)
{
	this->Position = pos;
	this->Size = siz;
	this->SetVertex();
}
void C2DObject::SetStatus(float scl, float ang)
{
	this->Scale = scl;
	this->Angle = ang;
	this->SetVertex();
}


/* 背景UI */
UIBackGround::UIBackGround()
{
	Vertex[0].coord = Vector3(        0.0f,          0.0f, 0.0f);
	Vertex[1].coord = Vector3(SCREEN_WIDTH,          0.0f, 0.0f);
	Vertex[2].coord = Vector3(        0.0f, SCREEN_HEIGHT, 0.0f);
	Vertex[3].coord = Vector3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
}
UIBackGround::UIBackGround(const char *texture)
{
	this->LoadTexture(texture);
	Vertex[0].coord = Vector3(        0.0f,          0.0f, 0.0f);
	Vertex[1].coord = Vector3(SCREEN_WIDTH,          0.0f, 0.0f);
	Vertex[2].coord = Vector3(        0.0f, SCREEN_HEIGHT, 0.0f);
	Vertex[3].coord = Vector3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
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
	Position = Vector2(posX, posY);
	Size = Vector2(sizeX - cor, sizeY - cor);
	Frame.SetStatus(Vector2(sizeX, sizeY), Vector2(posX, posY));
	Gage.SetStatus(Vector2(sizeX - cor, sizeY - cor), Vector2(posX, posY));
}
void UI2DPercentGauge::Uninit(void)
{
	Frame.Release();
	Gage.Release();
}
void UI2DPercentGauge::Update(float per)
{
	Gage.SetVertex(0, Vector3(Position.x - Size.x, Position.y - Size.y, 0.0f));
	Gage.SetVertex(1, Vector3(Position.x - Size.x + Size.x * 2 * per, Position.y - Size.y, 0.0f));
	Gage.SetVertex(2, Vector3(Position.x - Size.x, Position.y + Size.y, 0.0f));
	Gage.SetVertex(3, Vector3(Position.x - Size.x + Size.x * 2 * per, Position.y + Size.y, 0.0f));
}
void UI2DPercentGauge::Draw(void)
{
	Frame.Draw();
	Gage.Draw();
}

