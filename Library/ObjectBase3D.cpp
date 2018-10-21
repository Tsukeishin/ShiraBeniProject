#include "ObjectBase3D.h"
#include "Direct3D.h"
#include <math.h>


/* �Ŋ��N���X */
_ObjectBase3D::_ObjectBase3D()
{
	this->Texture = NULL;
	this->VtxBuff = NULL;
}

void _ObjectBase3D::LoadTexture(const char *texture)
{
	this->Texture.LoadTexture(texture);
}
void _ObjectBase3D::LoadTexture(LPDx3DTex9 texture)
{
	Texture = texture;
}
void _ObjectBase3D::Release()
{
	this->Texture.Release();
	if (VtxBuff != NULL)
	{	// ���_�̊J��
		VtxBuff->Release();
		VtxBuff = NULL;
	}
}
void _ObjectBase3D::ReleaseVertex()
{
	if (VtxBuff != NULL)
	{	// ���_�̊J��
		VtxBuff->Release();
		VtxBuff = NULL;
	}
}


/* 3D�|�� */
//----�R���X�g���N�^--------
C3DPolygonObject::C3DPolygonObject()
{
	Texture = NULL;		// �e�N�X�`���ւ̃|�C���^
	VtxBuff = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

	Position = Vector3(0.0f, 0.0f, 0.0f);	// �ʒu���W
	Rotation = Vector3(0.0f, 0.0f, 0.0f);	// ��]�p�x
	Size = Vector2(0.0f, 0.0f);				// �|���S���T�C�Y
	Scale = 1.0f;								// �T�C�Y�{��

	TexPattern_X = 1;		// �e�N�X�`���p�^�[���i���j
	TexPattern_Y = 1;		// �e�N�X�`���p�^�[���i�c�j
	AnimeCount = 0;			// �A�j���[�V�����J�E���g
	AnimePattern = 0;		// ���݂̃A�j���[�V�����p�^�[���ԍ�
	ChangeAnimeTime = 0;	// �A�j���[�V�����؂�ւ��Ҏ���
}

//----������--------
void C3DPolygonObject::Init(float posX, float posY, float posZ, float sizX, float sizY)
{
	this->Position = Vector3(posX, posY, posZ);
	this->Size = Vector2(sizX, sizY);
	this->MakeVertex();
}
void C3DPolygonObject::Init(Vector3 pos, Vector2 size)
{
	this->Position = pos;
	this->Size = size;
	this->MakeVertex();
}
void C3DPolygonObject::Init(Vector3 pos, Vector3 rot, Vector2 size)
{
	this->Position = pos;
	this->Rotation = rot;
	this->Size = size;
	this->MakeVertex();
}

//----�`�揈��--------
void C3DPolygonObject::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxWorld;

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ON
	pDevice->SetRenderState(D3DRS_ALPHAREF, 125);				// ��r���郿�̒l
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// ����(GREATER : �ȏ�)

	// ���C���e�B���O�𖳌��ɂ��� (���C�g�𓖂Ă�ƕςɂȂ�)
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, VtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, Texture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, RECT_NUM_POLYGON);

	// ���C���e�B���O��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//----���_�쐬--------
int C3DPolygonObject::MakeVertex(void)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(Direct3D::GetD3DDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * RECT_NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,		// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,			// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,		// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&VtxBuff,				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))					// NULL�ɐݒ�
	{
		return 1;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].coord = Vector3(-Size.x,  Size.y, 0.0f);
		pVtx[1].coord = Vector3( Size.x,  Size.y, 0.0f);
		pVtx[2].coord = Vector3(-Size.x, -Size.y, 0.0f);
		pVtx[3].coord = Vector3( Size.x, -Size.y, 0.0f);

		// �@���̐ݒ�
		pVtx[0].normal = Vector3(0.0f, 0.0f, -1.0f);
		pVtx[1].normal = Vector3(0.0f, 0.0f, -1.0f);
		pVtx[2].normal = Vector3(0.0f, 0.0f, -1.0f);
		pVtx[3].normal = Vector3(0.0f, 0.0f, -1.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].uv = Vector2(0.0f, 0.0f);
		pVtx[1].uv = Vector2(1.0f, 0.0f);
		pVtx[2].uv = Vector2(0.0f, 1.0f);
		pVtx[3].uv = Vector2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		VtxBuff->Unlock();
	}

	return 0;
}

//----���_���W�ݒ�--------
void C3DPolygonObject::SetVertex(void)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].coord = Vector3(-Size.x, Size.y, 0.0f);
		pVtx[1].coord = Vector3(Size.x, Size.y, 0.0f);
		pVtx[2].coord = Vector3(-Size.x, -Size.y, 0.0f);
		pVtx[3].coord = Vector3(Size.x, -Size.y, 0.0f);

		// ���_�f�[�^���A�����b�N����
		VtxBuff->Unlock();
	}
}
void C3DPolygonObject::SetVertex(D3DXCOLOR color)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].coord = Vector3(-Size.x, Size.y, 0.0f);
		pVtx[1].coord = Vector3(Size.x, Size.y, 0.0f);
		pVtx[2].coord = Vector3(-Size.x, -Size.y, 0.0f);
		pVtx[3].coord = Vector3(Size.x, -Size.y, 0.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = color;
		pVtx[1].diffuse = color;
		pVtx[2].diffuse = color;
		pVtx[3].diffuse = color;

		// ���_�f�[�^���A�����b�N����
		VtxBuff->Unlock();
	}
}

//----�e�N�X�`����񏑂�����--------
void C3DPolygonObject::LoadTextureStatus(float sizX, float sizY, float scale, int ptnX, int ptnY, int time)
{
	Size = { sizX, sizY };
	Scale = scale;
	TexPattern_X = ptnX;
	TexPattern_Y = ptnY;
	ChangeAnimeTime = time;
}
void C3DPolygonObject::LoadTextureStatus(float sizX, float sizY, float scale)
{
	Size = { sizX, sizY };
	Scale = scale;
	TexPattern_X = 1;
	TexPattern_Y = 1;
	ChangeAnimeTime = 1;
}

//----�I�u�W�F�N�g���--------
void C3DPolygonObject::LoadObjectStatus(Vector3 pos)
{
	this->Position = pos;
}
void C3DPolygonObject::LoadObjectStatus(Vector3 pos, Vector3 rot)
{
	this->Position = pos;
	this->Rotation = rot;
}



/* 3D������ */
//----�R���X�g���N�^--------
C3DCubeObject::C3DCubeObject()
{
	this->Texture = NULL;
	this->Position = Vector3(0.0f, 0.0f, 0.0f);
	this->Rotation = Vector3(0.0f, 0.0f, 0.0f);
	this->Size = Vector3(0.0f, 0.0f, 0.0f);
}
void C3DCubeObject::LoadTexture(const char *texture)
{
	this->Texture.LoadTexture(texture);
}
void C3DCubeObject::Release()
{
	this->Texture.Release();
}

//----������------
int  C3DCubeObject::Init(Vector3 pos, Vector3 rot, Vector3 size)
{
	this->Position = Vector3( pos.x,  pos.y,  pos.z);
	this->Rotation = Vector3( rot.x,  rot.y,  rot.z);
	this->Size     = Vector3(size.x, size.y, size.z);
	return this->MakeVertex();
}
int  C3DCubeObject::Init(Vector3 pos, Vector3 size)
{
	this->Position = Vector3( pos.x,  pos.y,  pos.z);
	this->Size     = Vector3(size.x, size.y, size.z);
	return this->MakeVertex();
}
int  C3DCubeObject::Init(Vector3 pos, Vector3 rot, float size)
{
	this->Position = Vector3(pos.x, pos.y, pos.z);
	this->Rotation = Vector3(rot.x, rot.y, rot.z);
	this->Size     = Vector3( size,  size,  size);
	return this->MakeVertex();
}
int  C3DCubeObject::Init(Vector3 pos, float size)
{
	this->Position = Vector3(pos.x, pos.y, pos.z);
	this->Size     = Vector3( size,  size,  size);
	return this->MakeVertex();
}

//----���_�쐬--------
int  C3DCubeObject::MakeVertex()
{
	Face[0][0].coord  = Vector3(-1.0f,  1.0f, -1.0f);//-Z
	Face[0][1].coord  = Vector3( 1.0f,  1.0f, -1.0f);
	Face[0][2].coord  = Vector3(-1.0f, -1.0f, -1.0f);
	Face[0][3].coord  = Vector3( 1.0f, -1.0f, -1.0f);
	Face[0][0].normal = Vector3( 0.0f,  0.0f, -1.0f);
	Face[0][1].normal = Vector3( 0.0f,  0.0f, -1.0f);
	Face[0][2].normal = Vector3( 0.0f,  0.0f, -1.0f);
	Face[0][3].normal = Vector3( 0.0f,  0.0f, -1.0f);

	Face[1][0].coord  = Vector3( 1.0f,  1.0f, -1.0f);//X
	Face[1][1].coord  = Vector3( 1.0f,  1.0f,  1.0f);
	Face[1][2].coord  = Vector3( 1.0f, -1.0f, -1.0f);
	Face[1][3].coord  = Vector3( 1.0f, -1.0f,  1.0f);
	Face[1][0].normal = Vector3( 1.0f,  0.0f,  0.0f);
	Face[1][1].normal = Vector3( 1.0f,  0.0f,  0.0f);
	Face[1][2].normal = Vector3( 1.0f,  0.0f,  0.0f);
	Face[1][3].normal = Vector3( 1.0f,  0.0f,  0.0f);

	Face[2][0].coord  = Vector3( 1.0f,  1.0f,  1.0f);//Z
	Face[2][1].coord  = Vector3(-1.0f,  1.0f,  1.0f);
	Face[2][2].coord  = Vector3( 1.0f, -1.0f,  1.0f);
	Face[2][3].coord  = Vector3(-1.0f, -1.0f,  1.0f);
	Face[2][0].normal = Vector3( 0.0f,  0.0f,  1.0f);
	Face[2][1].normal = Vector3( 0.0f,  0.0f,  1.0f);
	Face[2][2].normal = Vector3( 0.0f,  0.0f,  1.0f);
	Face[2][3].normal = Vector3( 0.0f,  0.0f,  1.0f);

	Face[3][0].coord  = Vector3(-1.0f,  1.0f,  1.0f);//-X
	Face[3][1].coord  = Vector3(-1.0f,  1.0f, -1.0f);
	Face[3][2].coord  = Vector3(-1.0f, -1.0f,  1.0f);
	Face[3][3].coord  = Vector3(-1.0f, -1.0f, -1.0f);
	Face[3][0].normal = Vector3(-1.0f,  0.0f,  0.0f);
	Face[3][1].normal = Vector3(-1.0f,  0.0f,  0.0f);
	Face[3][2].normal = Vector3(-1.0f,  0.0f,  0.0f);
	Face[3][3].normal = Vector3(-1.0f,  0.0f,  0.0f);

	Face[4][0].coord  = Vector3(-1.0f,  1.0f,  1.0f);//Y
	Face[4][1].coord  = Vector3( 1.0f,  1.0f,  1.0f);
	Face[4][2].coord  = Vector3(-1.0f,  1.0f, -1.0f);
	Face[4][3].coord  = Vector3( 1.0f,  1.0f, -1.0f);
	Face[4][0].normal = Vector3( 0.0f,  1.0f,  0.0f);
	Face[4][1].normal = Vector3( 0.0f,  1.0f,  0.0f);
	Face[4][2].normal = Vector3( 0.0f,  1.0f,  0.0f);
	Face[4][3].normal = Vector3( 0.0f,  1.0f,  0.0f);

	Face[5][0].coord  = Vector3(-1.0f, -1.0f, -1.0f);//-Y
	Face[5][1].coord  = Vector3( 1.0f, -1.0f, -1.0f);
	Face[5][2].coord  = Vector3(-1.0f, -1.0f,  1.0f);
	Face[5][3].coord  = Vector3( 1.0f, -1.0f,  1.0f);
	Face[5][0].normal = Vector3( 0.0f, -1.0f,  0.0f);
	Face[5][1].normal = Vector3( 0.0f, -1.0f,  0.0f);
	Face[5][2].normal = Vector3( 0.0f, -1.0f,  0.0f);
	Face[5][3].normal = Vector3( 0.0f, -1.0f,  0.0f);

	for (int iCnt = 0; iCnt < 6; iCnt++)
	{
		Face[iCnt][0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Face[iCnt][1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Face[iCnt][2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Face[iCnt][3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		Face[iCnt][0].uv = Vector2(0.1f, 0.1f);
		Face[iCnt][1].uv = Vector2(0.9f, 0.1f);
		Face[iCnt][2].uv = Vector2(0.1f, 0.9f);
		Face[iCnt][3].uv = Vector2(0.9f, 0.9f);
	}

	return 0;
}

//----�`�揈��--------
void C3DCubeObject::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ON
	pDevice->SetRenderState(D3DRS_ALPHAREF, 125);				// ��r���郿�̒l
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// ���� (D3DCMP_GREATER)

	// ���C���e�B���O�𖳌��ɂ��� (���C�g�𓖂Ă�ƕςɂȂ�)
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �T�C�Y�𔽉f
	D3DXMatrixScaling(&mtxScl, Size.x, Size.y, Size.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, Texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, RECT_NUM_POLYGON, Face[0], sizeof(VERTEX_3D));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, RECT_NUM_POLYGON, Face[1], sizeof(VERTEX_3D));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, RECT_NUM_POLYGON, Face[2], sizeof(VERTEX_3D));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, RECT_NUM_POLYGON, Face[3], sizeof(VERTEX_3D));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, RECT_NUM_POLYGON, Face[4], sizeof(VERTEX_3D));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, RECT_NUM_POLYGON, Face[5], sizeof(VERTEX_3D));

	// ���C���e�B���O��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}


/* ���f���ǂݍ��݃e�X�g *///*
C3DXModel::C3DXModel()
{
	// ���̏�����
	Position = Vector3();
	Rotation = Vector3();
	Scale = 1.0f;

	// ���f���֌W�̏�����
	Texture = NULL;
	Mesh = NULL;
	BuffMat = NULL;
	NumMat = 0;
}

int C3DXModel::Init(const char *filePath)
{
	// ���̏�����
	Position = Vector3();
	Rotation = Vector3();
	Scale    = 1.0f;

	// ���f���֌W�̏�����
	Texture = NULL;
	Mesh    = NULL;
	BuffMat = NULL;
	NumMat  = 0;

	// x�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(filePath,
		D3DXMESH_SYSTEMMEM,
		Direct3D::GetD3DDevice(),
		NULL,
		&BuffMat,
		NULL,
		&NumMat,
		&Mesh)))
	{
		return 1;
	}
	return 0;
}

void C3DXModel::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	/* ���f���̕`�� */
	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)BuffMat->GetBufferPointer();

	for (int i = 0; i < (int)NumMat; i++)
	{
		// �}�e���A���ݒ�
		pDevice->SetMaterial(&pD3DXMat[i].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, Texture);

		// �`��
		Mesh->DrawSubset(i);
	}

	pDevice->SetMaterial(&matDef);	// �}�e���A�������ɖ߂�
}

void C3DXModel::Uninit()
{
	if (Texture != NULL)
	{// �e�N�X�`���̊J��
		Texture->Release();
		Texture = NULL;
	}

	// 3D�v���C���[�̉��
	if (Mesh != NULL)
	{// ���b�V���̊J��
		Mesh->Release();
		Mesh = NULL;
	}

	if (BuffMat != NULL)
	{// �}�e���A���̊J��
		BuffMat->Release();
		BuffMat = NULL;
	}
}

