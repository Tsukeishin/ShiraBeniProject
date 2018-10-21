#ifndef __DX9_POLYGON_H_INCLUDE__
#define __DX9_POLYGON_H_INCLUDE__


#include "Vector.h"
#include "Color.h"
#include <d3dx9.h>


// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)


/* ��`�|���S�� */
#define RECT_NUM_VERTEX		(4)		// ���_��
#define RECT_NUM_POLYGON	(2)		// �|���S����


// ��L�Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct VERTEX_2D
{
	Vector3 coord;		// ���_���W
	float   rhw;		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	DxColor diffuse;	// ���ˌ�
	Vector2 uv;			// �e�N�X�`�����W
} Vertex2D;

// ��L�R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct VERTEX_3D
{
	Vector3 coord;		// ���_���W
	Vector3 normal;		// �@���x�N�g��
	DxColor diffuse;	// ���ˌ�
	Vector2 uv;			// �e�N�X�`�����W
} Vertex3D;



#endif // !__DX9_POLYGON_H_INCLUDE__
