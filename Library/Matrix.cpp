#include "Matrix.h"


//Matrix::Matrix()
//{
//	_11 = 1.0f; _12 = 0.0f; _13 = 0.0f; _14 = 0.0f;
//	_21 = 0.0f; _22 = 1.0f; _23 = 0.0f; _24 = 0.0f;
//	_31 = 0.0f; _32 = 0.0f; _33 = 1.0f; _34 = 0.0f;
//	_41 = 0.0f; _42 = 0.0f; _43 = 0.0f; _44 = 1.0f;
//}
//Matrix::Matrix(const Matrix &mtx)
//{
//	*this = mtx;
//}
//Matrix::Matrix(float _11_, float _12_, float _13_, float _14_,
//	           float _21_, float _22_, float _23_, float _24_,
//	           float _31_, float _32_, float _33_, float _34_,
//	           float _41_, float _42_, float _43_, float _44_)
//{
//	this->_11 = _11_; this->_12 = _12_; this->_13 = _13_; this->_14 = _14_;
//	this->_21 = _21_; this->_22 = _22_; this->_23 = _23_; this->_24 = _24_;
//	this->_31 = _31_; this->_32 = _32_; this->_33 = _33_; this->_34 = _34_;
//	this->_41 = _41_; this->_42 = _42_; this->_43 = _43_; this->_44 = _44_;
//}
//
//
//// access grants
//float & Matrix::operator () (unsigned int Row, unsigned int Column)
//{
//	return m[Column][Row];
//}
//float   Matrix::operator () (unsigned int Row, unsigned int Column) const
//{
//	return m[Column][Row];
//}
//
//// casting operators
//Matrix::operator float* ();
//Matrix::operator const float* () const;
//
//// assignment operators
//Matrix & Matrix::operator *= (const Matrix&);
//Matrix & Matrix::operator += (const Matrix&);
//Matrix & Matrix::operator -= (const Matrix&);
//Matrix & Matrix::operator *= (float);
//Matrix & Matrix::operator /= (float);
//
//// unary operators
//Matrix Matrix::operator + () const;
//Matrix Matrix::operator - () const;
//
//// binary operators
//Matrix Matrix::operator * (const Matrix&) const;
//Matrix Matrix::operator + (const Matrix&) const;
//Matrix Matrix::operator - (const Matrix&) const;
//Matrix Matrix::operator * (float) const;
//Matrix Matrix::operator / (float) const;
//
//Matrix operator * (float, const Matrix&);
//
//bool Matrix::operator == (const Matrix&) const;
//bool Matrix::operator != (const Matrix&) const;


DxMatrix CreateMatrix(DxMatrix *mtx, float scale, Vector3 rota, Vector3 trans, const char *order)
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
DxMatrix CreateMatrix(DxMatrix *mtx, Vector3 scale, Vector3 rota, Vector3 trans, const char *order)
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
			D3DXMatrixScaling(&mtxScl, scale.x, scale.y, scale.z);
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




