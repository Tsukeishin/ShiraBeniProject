#ifndef __DIRECTX9_3D_DEVICE_H_INCLUDE__
#define __DIRECTX9_3D_DEVICE_H_INCLUDE__


#include <d3dx9.h>


class Direct3D
{
	static LPDIRECT3D9              dx_pD3D;		// Direct3D�I�u�W�F�N�g
	static LPDIRECT3DDEVICE9        dx_pD3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	static D3DPRESENT_PARAMETERS    dxD3Dpp;		// �v���[���e�[�V�����p�����[�^

public:
	static HRESULT  Init(HWND hWnd, bool bWindowMode);
	static void     Uninit();
	
	static LPDIRECT3DDEVICE9 GetD3DDevice();
};



#endif // !__DIRECTX9_3D_DEVICE_H_INCLUDE__
