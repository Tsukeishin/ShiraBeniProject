#include "Matrix.h"



D3DXMATRIX CreateMatrix(D3DXMATRIX *mtx, float scale, Vector3 rota, Vector3 trans, const char *order = "SRT")
{
	D3DXMATRIX mtxWorld, mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	while (*order != '\0')
	{
		switch (*order)
		{
		case 'S':
		case 's':
			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, scale, scale, scale);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);
			break;

		case 'R':
		case 'r':
			// ��]�𔽉f (���� : y, x, z�̏�)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, rota.y, rota.x, rota.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
			break;

		case 'T':
		case 't':
			// ���s�ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, trans.x, trans.y, trans.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);
			break;
		}
		order++;
	}

	*mtx = mtxWorld;
	return mtxWorld;
}




