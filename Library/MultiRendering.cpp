#include "MultiRendering.h"


RenderBuffer::~RenderBuffer()
{
	if (this->DepthBuffer != NULL)
	{
		this->DepthBuffer->Release();
		this->DepthBuffer = NULL;
	}

	if (this->Texture != NULL)
	{
		this->Texture->Release();
		this->Texture = NULL;
	}
}

HRESULT RenderBuffer::Init(DWORD vp_w, DWORD vp_h, UINT dep_w, UINT dep_h, UINT tex_w, UINT tex_h, D3DFORMAT tex_format)
{
	this->Viewport.X = 0;
	this->Viewport.Y = 0;
	this->Viewport.Width = vp_w;
	this->Viewport.Height = vp_h;
	this->Viewport.MinZ = 0.0f;
	this->Viewport.MaxZ = 1.0f;

	//デプスバッファ作成
	Direct3D::GetD3DDevice()->CreateDepthStencilSurface(
		dep_w, dep_h,		//サイズ（2の階乗にしよう最低でも1024はほしい）
		D3DFMT_D24S8,	//ピクセルフォーマット
		D3DMULTISAMPLE_NONE,//マルチサンプリングOFF
		0,					// この下からはマルチサンプリング
		FALSE,
		&this->DepthBuffer,
		NULL);

	//レンダーターゲット用テクスチャ作成
	D3DXCreateTexture(Direct3D::GetD3DDevice(),
		tex_w, tex_h,		//サイズ 
		1,				//ミップマップ数
		D3DUSAGE_RENDERTARGET,	//使用目的
		tex_format,		//ピクセルフォーマット D3DFMT_X8R8G8B8
		D3DPOOL_DEFAULT,
		&this->Texture);

	return S_OK;
}

HRESULT RenderBuffer::BeginDraw()
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();

	//デフォルトのサーフェースを保存
	pDevice->GetRenderTarget(0, &this->DefaultRenderTargetSurface);
	pDevice->GetDepthStencilSurface(&this->DefaultDepthBufferSurface);
	//レンダリング用テクスチャのサーフェース取得
	this->Texture->GetSurfaceLevel(0, &this->RenderTextureSurface);

	//新しいレンダリングターゲットをセット
	pDevice->SetRenderTarget(0, this->RenderTextureSurface);
	//新しいデプスバッファをセット
	pDevice->SetDepthStencilSurface(this->DepthBuffer);

	//ビューポートの切り替え
	pDevice->GetViewport(&this->DefaultViewport);
	pDevice->SetViewport(&this->Viewport);

	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0x00, 0x00, 0x00, 0xFF), 1.0f, 0);

	return S_OK;
}

HRESULT RenderBuffer::EndDraw()
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();

	pDevice->SetRenderTarget(0, this->DefaultRenderTargetSurface);
	pDevice->SetDepthStencilSurface(this->DefaultDepthBufferSurface);

	//サーフェースの解放
	this->DefaultRenderTargetSurface->Release();
	this->DefaultDepthBufferSurface->Release();
	this->RenderTextureSurface->Release();

	//ビューポートの復帰
	pDevice->SetViewport(&this->DefaultViewport);

	return S_OK;
}

void RenderBuffer::Release()
{
	if (this->DepthBuffer != NULL)
	{
		this->DepthBuffer->Release();
		this->DepthBuffer = NULL;
	}

	if (this->Texture != NULL)
	{
		this->Texture->Release();
		this->Texture = NULL;
	}
}

LPDIRECT3DTEXTURE9 RenderBuffer::GetTexture()
{
	return this->Texture;
}
