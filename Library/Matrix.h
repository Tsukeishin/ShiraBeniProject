#ifndef __MATRIX_H_INCLUDE__
#define __MATRIX_H_INCLUDE__


#include "Vector.h" // DirectX9 <d3dx9math.h>“ü‚è


typedef D3DXMATRIX DxMatrix;

D3DXMATRIX CreateMatrix(D3DXMATRIX *mtx, float scale, Vector3 rota, Vector3 trans, const char *order);





#endif // !__COMMON_H_INCLUDE__
