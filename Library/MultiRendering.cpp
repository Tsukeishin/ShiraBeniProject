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

	//�f�v�X�o�b�t�@�쐬
	Direct3D::GetD3DDevice()->CreateDepthStencilSurface(
		dep_w, dep_h,		//�T�C�Y�i2�̊K��ɂ��悤�Œ�ł�1024�͂ق����j
		D3DFMT_D24S8,	//�s�N�Z���t�H�[�}�b�g
		D3DMULTISAMPLE_NONE,//�}���`�T���v�����OOFF
		0,					// ���̉�����̓}���`�T���v�����O
		FALSE,
		&this->DepthBuffer,
		NULL);

	//�����_�[�^�[�Q�b�g�p�e�N�X�`���쐬
	D3DXCreateTexture(Direct3D::GetD3DDevice(),
		tex_w, tex_h,		//�T�C�Y 
		1,				//�~�b�v�}�b�v��
		D3DUSAGE_RENDERTARGET,	//�g�p�ړI
		tex_format,		//�s�N�Z���t�H�[�}�b�g D3DFMT_X8R8G8B8
		D3DPOOL_DEFAULT,
		&this->Texture);

	return S_OK;
}

HRESULT RenderBuffer::BeginDraw()
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();

	//�f�t�H���g�̃T�[�t�F�[�X��ۑ�
	pDevice->GetRenderTarget(0, &this->DefaultRenderTargetSurface);
	pDevice->GetDepthStencilSurface(&this->DefaultDepthBufferSurface);
	//�����_�����O�p�e�N�X�`���̃T�[�t�F�[�X�擾
	this->Texture->GetSurfaceLevel(0, &this->RenderTextureSurface);

	//�V���������_�����O�^�[�Q�b�g���Z�b�g
	pDevice->SetRenderTarget(0, this->RenderTextureSurface);
	//�V�����f�v�X�o�b�t�@���Z�b�g
	pDevice->SetDepthStencilSurface(this->DepthBuffer);

	//�r���[�|�[�g�̐؂�ւ�
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

	//�T�[�t�F�[�X�̉��
	this->DefaultRenderTargetSurface->Release();
	this->DefaultDepthBufferSurface->Release();
	this->RenderTextureSurface->Release();

	//�r���[�|�[�g�̕��A
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
