#ifndef __Dx9_TEXTURE_H_INCLUDE__
#define __Dx9_TEXTURE_H_INCLUDE__


#include "Direct3D.h"
#include "Math.h"
#include <string>


typedef LPDIRECT3DTEXTURE9 LPDx3DTex9;

class Dx9Texture
{
public:
	static LPDx3DTex9 LoadTexture(LPDx3DTex9 *lpDxTex, LPCSTR fileName);
	static LPDx3DTex9 LoadTexture(Dx9Texture *Dx9pTex, LPCSTR fileName);

protected:
	LPDx3DTex9 pDx9Texture;

public:
	Dx9Texture();

	Dx9Texture & operator = (const LPDx3DTex9 pTex);
	operator LPDx3DTex9() const;

	bool operator == (const LPDx3DTex9 pTex) const;
	bool operator != (const LPDx3DTex9 pTex) const;

	LPDx3DTex9 LoadTexture(LPCSTR fileName);
	LPDx3DTex9 LoadTexture(LPDx3DTex9 pTex);

	void Release();
	
private:

};

class Dx9TextureM : public Dx9Texture
{
protected:
	X2<INT>     Divide;		// テクスチャ内分割数

public:
	Dx9TextureM();

	LPDx3DTex9 LoadTexture(LPCSTR fileName, int ix, int iy);
	LPDx3DTex9 LoadTexture(LPDx3DTex9 pTex, int ix, int iy);


};





#endif // !__Dx9_TEXTURE_H_INCLUDE__
