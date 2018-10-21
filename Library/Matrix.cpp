#include "Matrix.h"



D3DXMATRIX CreateMatrix(D3DXMATRIX *mtx, float scale, Vector3 rota, Vector3 trans, const char *order = "SRT")
{
	D3DXMATRIX mtxWorld, mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	while (*order != '\0')
	{
		switch (*order)
		{
		case 'S':
		case 's':
			// スケールを反映
			D3DXMatrixScaling(&mtxScl, scale, scale, scale);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);
			break;

		case 'R':
		case 'r':
			// 回転を反映 (注意 : y, x, zの順)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, rota.y, rota.x, rota.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
			break;

		case 'T':
		case 't':
			// 平行移動を反映
			D3DXMatrixTranslation(&mtxTranslate, trans.x, trans.y, trans.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);
			break;
		}
		order++;
	}

	*mtx = mtxWorld;
	return mtxWorld;
}




