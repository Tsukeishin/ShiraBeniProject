#include "TsuLibSystem.h"
#include "WindowClass.h"
#include "Direct3D.h"
#include "Dx9Line.h"
#include "DirectInput.h"
#include "Sound.h"
#include "DebugProcess.h"

HRESULT TSULibrarySystem::Initialize(HINSTANCE hInstance)
{
	// �E�B���h�E������
	if (FAILED(WindowClass::Init(hInstance, "ShirabeniProject", "���g�v���W�F�N�g")))
		return -1;

	// �O���t�B�b�N�X������(Direct3D)
	if (FAILED(Direct3D::Init(WindowClass::GetHWnd(), TRUE)))
		return -1;

	// �C���v�b�g������
	if (FAILED(DirectInput::Init(WindowClass::GetHInstance(), WindowClass::GetHWnd())))
		return -1;

	// �T�E���h������
	if (FAILED(DirectSound::Init(WindowClass::GetHWnd())))
		return -1;

	// Dx9Line������
	if (FAILED(Dx9Line::Init()))
		return -1;

	// �f�o�b�O�\���̏�����
	InitDebugProcess();

	return S_OK;
}

void TSULibrarySystem::Uninitialize()
{
	WindowClass::Uninit();	// �E�B���h�E�I��
	Direct3D::Uninit();		// �O���t�B�b�N�X�I��(Direct3D)
	DirectInput::Uninit();	// ���͂̏I������
	DirectSound::Uninit();	// �T�E���h�I������
	Dx9Line::Uninit();		// Dx9Line�I������
	UninitDebugProcess();	// �f�o�b�O�\�������̏I������
}

void TSULibrarySystem::CoordinateAxis()
{
	struct caLine
	{
		Vector3 coord;
		DxColor color;
	};

	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();

#define CAFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
	LPDIRECT3DVERTEXBUFFER9 lineVtxBuff;
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	Direct3D::GetD3DDevice()->CreateVertexBuffer(sizeof(caLine) * 6,
		D3DUSAGE_WRITEONLY,		// ���_�o�b�t�@�̎g�p�@�@
		CAFVF,					// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,		// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&lineVtxBuff,			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL);					// NULL�ɐݒ�
	{//���_�o�b�t�@�̒��g�𖄂߂�
		caLine *pVtx;

		// ���_�f�[�^�͈̔͂����b�N
		lineVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���W
		pVtx[0].coord = Vector3(  0, 0, 0);
		pVtx[1].coord = Vector3(100, 0, 0);
		pVtx[2].coord = Vector3(0,   0, 0);
		pVtx[3].coord = Vector3(0, 100, 0);
		pVtx[4].coord = Vector3(0, 0,   0);
		pVtx[5].coord = Vector3(0, 0, 100);

		// �F
		pVtx[0].color = DX9COLOR_RED;
		pVtx[1].color = DX9COLOR_RED;
		pVtx[2].color = DX9COLOR_GREEN;
		pVtx[3].color = DX9COLOR_GREEN;
		pVtx[4].color = DX9COLOR_BLUE;
		pVtx[5].color = DX9COLOR_BLUE;

		// ���_�f�[�^���A�����b�N����
		lineVtxBuff->Unlock();
	}

	// ���C���e�B���O
	DWORD lightState;
	pDevice->GetRenderState(D3DRS_LIGHTING, &lightState);
	if (lightState)
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetStreamSource(0, lineVtxBuff, 0, sizeof(caLine));
	pDevice->SetFVF(CAFVF);
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 3);

	Dx9SafeRelease(lineVtxBuff);

	// ���C���e�B���O��L���ɖ߂�
	if (lightState)
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}



