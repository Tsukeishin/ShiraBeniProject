#ifndef __MULTI_PASS_RENDERING_H_INCLUDE__
#define __MULTI_PASS_RENDERING_H_INCLUDE__


#include "Direct3D.h"


class RenderBuffer
{
protected:
	LPDIRECT3DSURFACE9  DepthBuffer;	// �����_�[�e�N�X�`���p��Z�o�b�t�@
	LPDIRECT3DTEXTURE9  Texture;		// �����_�[�e�N�X�`��
	D3DVIEWPORT9        Viewport;		// �����_�[�e�N�X�`���p�̃r���[�|�[�g

	LPDIRECT3DSURFACE9  DefaultRenderTargetSurface;	// �ۑ��p
	LPDIRECT3DSURFACE9  DefaultDepthBufferSurface;	// �ۑ��p
	LPDIRECT3DSURFACE9  RenderTextureSurface;		// �ۑ��p
	D3DVIEWPORT9        DefaultViewport;			// �ۑ��p

public:
	~RenderBuffer();

	HRESULT Init(DWORD vp_w, DWORD vp_h, UINT dep_w, UINT dep_h, UINT tex_w, UINT tex_h, D3DFORMAT tex_format);
	HRESULT BeginDraw();
	HRESULT EndDraw();
	void    Release();
	LPDIRECT3DTEXTURE9 GetTexture();
	
};


#endif // !__MULTI_PASS_RENDERING_H_INCLUDE__
