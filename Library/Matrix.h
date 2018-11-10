#ifndef __MATRIX_H_INCLUDE__
#define __MATRIX_H_INCLUDE__


#include "Vector.h" // DirectX9 <d3dx9math.h>“ü‚è


typedef D3DXMATRIX DxMatrix;


//class Matrix
//{
//public:
//	union
//	{
//		struct
//		{
//			float _11, _12, _13, _14;
//			float _21, _22, _23, _24;
//			float _31, _32, _33, _34;
//			float _41, _42, _43, _44;
//		};
//		float m[4][4];
//	};
//
//public:
//	Matrix();
//	Matrix(const Matrix &mtx);
//	Matrix(float _11, float _12, float _13, float _14,
//	       float _21, float _22, float _23, float _24,
//	       float _31, float _32, float _33, float _34,
//	       float _41, float _42, float _43, float _44);
//
//
//	// access grants
//	float & operator () (unsigned int Row, unsigned int Column);
//	float   operator () (unsigned int Row, unsigned int Column) const;
//
//	// casting operators
//	operator float* ();
//	operator const float* () const;
//
//	// assignment operators
//	Matrix & operator *= (const Matrix&);
//	Matrix & operator += (const Matrix&);
//	Matrix & operator -= (const Matrix&);
//	Matrix & operator *= (float);
//	Matrix & operator /= (float);
//
//	// unary operators
//	Matrix operator + () const;
//	Matrix operator - () const;
//
//	// binary operators
//	Matrix operator * (const Matrix&) const;
//	Matrix operator + (const Matrix&) const;
//	Matrix operator - (const Matrix&) const;
//	Matrix operator * (float) const;
//	Matrix operator / (float) const;
//
//	friend Matrix operator * (float, const Matrix&);
//
//	bool operator == (const Matrix&) const;
//	bool operator != (const Matrix&) const;
//
//};


DxMatrix CreateMatrix(DxMatrix *mtx, float scale, Vector3 rota, Vector3 trans, const char *order = "SRT");
DxMatrix CreateMatrix(DxMatrix *mtx, Vector3 scale, Vector3 rota, Vector3 trans, const char *order = "SRT");





#endif // !__COMMON_H_INCLUDE__
