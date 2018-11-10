#ifndef __MULTI_PASS_RENDERING_H_INCLUDE__
#define __MULTI_PASS_RENDERING_H_INCLUDE__


#include "Direct3D.h"


class RenderBuffer
{
protected:
	LPDIRECT3DSURFACE9  DepthBuffer;	// レンダーテクスチャ用のZバッファ
	LPDIRECT3DTEXTURE9  Texture;		// レンダーテクスチャ
	D3DVIEWPORT9        Viewport;		// レンダーテクスチャ用のビューポート

	LPDIRECT3DSURFACE9  DefaultRenderTargetSurface;	// 保存用
	LPDIRECT3DSURFACE9  DefaultDepthBufferSurface;	// 保存用
	LPDIRECT3DSURFACE9  RenderTextureSurface;		// 保存用
	D3DVIEWPORT9        DefaultViewport;			// 保存用

public:
	~RenderBuffer();

	HRESULT Init(DWORD vp_w, DWORD vp_h, UINT dep_w, UINT dep_h, UINT tex_w, UINT tex_h, D3DFORMAT tex_format);
	HRESULT BeginDraw();
	HRESULT EndDraw();
	void    Release();
	LPDIRECT3DTEXTURE9 GetTexture();
	
};


#endif // !__MULTI_PASS_RENDERING_H_INCLUDE__
