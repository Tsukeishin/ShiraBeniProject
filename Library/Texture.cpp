#include "Texture.h"


LPDx3DTex9 Dx9Texture::LoadTexture(LPDx3DTex9 *lpDxTex, LPCSTR fileName)
{
	if (*lpDxTex != NULL)
	{
		(*lpDxTex)->Release();
		*lpDxTex = NULL;
	}
	D3DXCreateTextureFromFile(Direct3D::GetD3DDevice(), fileName, lpDxTex);
	return *lpDxTex;
}
LPDx3DTex9 Dx9Texture::LoadTexture(Dx9Texture *Dx9pTex, LPCSTR fileName)
{
	if (Dx9pTex->pDx9Texture != NULL)
	{
		Dx9pTex->pDx9Texture->Release();
		Dx9pTex->pDx9Texture = NULL;
	}
	D3DXCreateTextureFromFile(Direct3D::GetD3DDevice(), fileName, &Dx9pTex->pDx9Texture);
	return Dx9pTex->pDx9Texture;
}


Dx9Texture::Dx9Texture()
{
	this->pDx9Texture = NULL;
}

Dx9Texture & Dx9Texture::operator = (const LPDx3DTex9 pTex)
{
	if (this->pDx9Texture != NULL)
	{
		this->pDx9Texture->Release();
		this->pDx9Texture = NULL;
	}
	this->pDx9Texture = pTex;
	return *this;
}

Dx9Texture::operator LPDx3DTex9() const
{
	return this->pDx9Texture;
}

bool Dx9Texture::operator == (const LPDx3DTex9 pTex) const
{
	return (this->pDx9Texture == pTex);
}
bool Dx9Texture::operator != (const LPDx3DTex9 pTex) const
{
	return (this->pDx9Texture != pTex);
}

LPDx3DTex9 Dx9Texture::LoadTexture(LPCSTR fileName)
{
	if (this->pDx9Texture != NULL)
	{
		this->pDx9Texture->Release();
		this->pDx9Texture = NULL;
	}
	D3DXCreateTextureFromFile(Direct3D::GetD3DDevice(), fileName, &this->pDx9Texture);
	return this->pDx9Texture;
}
LPDx3DTex9 Dx9Texture::LoadTexture(LPDx3DTex9 pTex)
{
	if (this->pDx9Texture != NULL)
	{
		this->pDx9Texture->Release();
		this->pDx9Texture = NULL;
	}
	this->pDx9Texture = pTex;
	return this->pDx9Texture;
}

void Dx9Texture::Release()
{
	if (this->pDx9Texture != NULL)
	{
		this->pDx9Texture->Release();
		this->pDx9Texture = NULL;
	}
}


Dx9TextureM::Dx9TextureM()
{
	this->pDx9Texture = NULL;
	this->Divide = X2<INT>(1, 1);
}

LPDx3DTex9 Dx9TextureM::LoadTexture(LPCSTR fileName, int ix, int iy)
{
	if (this->pDx9Texture != NULL)
	{
		this->pDx9Texture->Release();
		this->pDx9Texture = NULL;
	}
	D3DXCreateTextureFromFile(Direct3D::GetD3DDevice(), fileName, &this->pDx9Texture);
	this->Divide = X2<INT>(ix, iy);
	return this->pDx9Texture;
}
LPDx3DTex9 Dx9TextureM::LoadTexture(LPDx3DTex9 pTex, int ix, int iy)
{
	if (this->pDx9Texture != NULL)
	{
		this->pDx9Texture->Release();
		this->pDx9Texture = NULL;
	}
	this->pDx9Texture = pTex;
	this->Divide = X2<INT>(ix, iy);
	return this->pDx9Texture;
}


