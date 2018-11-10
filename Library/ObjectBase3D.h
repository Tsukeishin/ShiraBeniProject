#ifndef __CLASS_3D_OBJECT_BASE_H_INCLUDE__
#define __CLASS_3D_OBJECT_BASE_H_INCLUDE__


#include "Texture.h"
#include "Polygon.h"


/* 3D�I�u�W�F�N�g��b�N���X */
class _ObjectBase3D
{
protected:
	Dx9Texture              Texture;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;

public:
	_ObjectBase3D();

	virtual int  Init() { return 1; };
	virtual int  Update() { return 1; };
	virtual void Draw() {};
	virtual void Uninit() { this->Release(); };

	virtual void LoadTexture(const char *texture);			// �O�e�N�X�`���̓N���A(�J������)
	virtual void LoadTexture(LPDx3DTex9 texture);	// �O�e�N�X�`���̓����[�X(�J���Ȃ�)
	virtual void Release();
	virtual void ReleaseVertex();
};


/* 3D�|���S���I�u�W�F�N�g */
class C3DPolygonObject : public _ObjectBase3D
{
protected:
	Vector3 Position;	// �ʒu���W
	Vector3 Rotation;	// ��]�p�x
	Vector2 Size;		// �|���S���T�C�Y
	float   Scale;		// �T�C�Y�{��

	int TexPattern_X;		// �e�N�X�`���p�^�[���i���j
	int TexPattern_Y;		// �e�N�X�`���p�^�[���i�c�j
	int AnimeCount;			// �A�j���[�V�����J�E���g
	int AnimePattern;		// ���݂̃A�j���[�V�����p�^�[���ԍ�
	int ChangeAnimeTime;	// �A�j���[�V�����؂�ւ��Ҏ���

	virtual int  MakeVertex(void);
	virtual void SetVertex(void);				// ���_���W�ݒ�@���_�ʒu�̂�
	virtual void SetVertex(D3DXCOLOR color);	// ���_���W�ݒ�@���_�F����

public:
	C3DPolygonObject();

	virtual void Init(float posX, float posY, float posZ, float sizX, float sizY);
	virtual void Init(Vector3 pos, Vector2 size);
	virtual void Init(Vector3 pos, Vector3 rot, Vector2 size);
	virtual void Draw(void);

	virtual void LoadTextureStatus(float sizX, float sizY, float scale, int ptnX, int ptnY, int time);
	virtual void LoadTextureStatus(float sizX, float sizY, float scale);
	virtual void LoadObjectStatus(Vector3 pos);
	virtual void LoadObjectStatus(Vector3 pos, Vector3 rot);
};


/* 3D�Z�ʑ̃I�u�W�F�N�g *///*
class C3DCubeObject
{
protected:
	Dx9Texture Texture;
	Vertex3D   Face[6][4];
	Vector3 Position;	// �ʒu���W
	Vector3 Rotation;	// ��]�p�x
	Vector3 Size;		// �|���S���T�C�Y

public:
	C3DCubeObject();

	void LoadTexture(const char *texture);
	void LoadTexture(LPDx3DTex9 texture);
	void Release();

	int  Init(Vector3 pos, Vector3 rot, Vector3 size);
	int  Init(Vector3 pos, Vector3 size);
	int  Init(Vector3 pos, Vector3 rot, float size);
	int  Init(Vector3 pos, float size);
	int  MakeVertex(void);

	void Draw();

};


/* ���f���ǂݍ��݃e�X�g *///*
class C3DXModel
{
protected:
	LPDIRECT3DTEXTURE9	Texture;	// �e�N�X�`���ւ̃|�C���^
	LPD3DXMESH			Mesh;		// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER		BuffMat;	// �}�e���A�����ւ̃|�C���^
	DWORD				NumMat;		// �}�e���A�����̐�

public:
	Vector3 Position;
	Vector3 Rotation;
	float   Scale;

public:
	C3DXModel();

	int  Init(const char *filePath);
	void Draw();
	void Uninit();
};






#endif // !__CLASS_OBJECT_INCLUDE__

