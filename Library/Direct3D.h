#ifndef __DIRECTX9_3D_DEVICE_H_INCLUDE__
#define __DIRECTX9_3D_DEVICE_H_INCLUDE__


#include <d3dx9.h>
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")


class Direct3D
{
	static LPDIRECT3D9              dx_pD3D;		// Direct3Dオブジェクト
	static LPDIRECT3DDEVICE9        dx_pD3DDevice;	// Deviceオブジェクト(描画に必要)
	static D3DPRESENT_PARAMETERS    dxD3Dpp;		// プレゼンテーションパラメータ

public:
	static HRESULT Init(HWND hWnd, bool bWindowMode);
	static void    Uninit();
	
	static void ResetDevice();

	static LPDIRECT3DDEVICE9 GetD3DDevice();
};


#define Dx9SafeRelease( pointer ) if ( pointer != NULL ) { pointer->Release(); pointer = NULL; }


#endif // !__DIRECTX9_3D_DEVICE_H_INCLUDE__
