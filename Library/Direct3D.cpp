#include "Direct3D.h"
#include "Common.h"


LPDIRECT3D9             Direct3D::dx_pD3D       = NULL;	// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9       Direct3D::dx_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)
D3DPRESENT_PARAMETERS   Direct3D::dxD3Dpp       = {};	// �v���[���e�[�V�����p�����[�^


//----����������--------
HRESULT Direct3D::Init(HWND hWnd, bool bWindowMode)
{
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	dx_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (dx_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(dx_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&dxD3Dpp, sizeof(dxD3Dpp));			// ���[�N���[���N���A
	dxD3Dpp.BackBufferCount  = 1;					// �o�b�N�o�b�t�@�̐�
	dxD3Dpp.BackBufferWidth  = SCREEN_WIDTH;		// �Q�[����ʃT�C�Y(��)
	dxD3Dpp.BackBufferHeight = SCREEN_HEIGHT;		// �Q�[����ʃT�C�Y(����)
	dxD3Dpp.BackBufferFormat = d3ddm.Format;		// �J���[���[�h�̎w��
	dxD3Dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	dxD3Dpp.Windowed = bWindowMode;				// �E�B���h�E���[�h
	dxD3Dpp.EnableAutoDepthStencil = TRUE;		// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	dxD3Dpp.AutoDepthStencilFormat = D3DFMT_D16;	// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	if (bWindowMode)
	{// �E�B���h�E���[�h
		dxD3Dpp.FullScreen_RefreshRateInHz = 0;						// ���t���b�V�����[�g
		dxD3Dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		dxD3Dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
		dxD3Dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��
	}

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(dx_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&dxD3Dpp, &dx_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(dx_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&dxD3Dpp, &dx_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(dx_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&dxD3Dpp, &dx_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}


	/* �����_�����O�X�e�[�g�p�����[�^�̐ݒ� */
	dx_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
//	dx_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);			// ���ʂ��\��
	dx_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	dx_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// ���u�����h���s��(off�ɂ���ƌy���Ȃ�)
	dx_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	dx_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��
//	dx_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);		// ���f�B�X�g�l�[�V�����J���[�̎w��

	/* �T���v���[�X�e�[�g�p�����[�^�̐ݒ� */
	dx_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	dx_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	dx_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	dx_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	/* �e�N�X�`���X�e�[�W���Z�������� */
	dx_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	dx_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	dx_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

	/* ���C�e�B���O���[�h��L�� */
	dx_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


	return S_OK;
}

//----�I������--------
void Direct3D::Uninit()
{
	if (dx_pD3DDevice != NULL)
	{// �f�o�C�X�̊J��
		dx_pD3DDevice->Release();
		dx_pD3DDevice = NULL;
	}

	if (dx_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		dx_pD3D->Release();
		dx_pD3D = NULL;
	}
}

//----�f�o�C�X�̃��Z�b�g
void Direct3D::ResetDevice()
{
	dx_pD3DDevice->Reset(&dxD3Dpp);

	/* �����_�����O�X�e�[�g�p�����[�^�̐ݒ� */
	dx_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
//	dx_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);			// ���ʂ��\��
	dx_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	dx_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// ���u�����h���s��(off�ɂ���ƌy���Ȃ�)
	dx_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	dx_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��
//	dx_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);		// ���f�B�X�g�l�[�V�����J���[�̎w��

	/* �T���v���[�X�e�[�g�p�����[�^�̐ݒ� */
	dx_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	dx_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	dx_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	dx_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	/* �e�N�X�`���X�e�[�W���Z�������� */
	dx_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	dx_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	dx_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

	/* ���C�e�B���O���[�h��L�� */
	dx_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}


//----�擾�֐�--------
LPDIRECT3DDEVICE9 Direct3D::GetD3DDevice()
{
	return Direct3D::dx_pD3DDevice;
}

