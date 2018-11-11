//=============================================================================
//
// ���C������ [main.cpp]
//
//=============================================================================
#include "Library/Common.h"
#include "Library/TsuLibSystem.h"
#include "Library/WindowClass.h"
#include "Library/Direct3D.h"
#include "Library/FPSManager.h"
#include "Library/DirectInput.h"
#include "Library/Sound.h"
#include "Library/Fade.h"
#include "Library/Camera.h"
#include "Library/Light.h"
#include "Library/Dx9Line.h"
#include "Library/DebugProcess.h"
#include "SceneManager.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT Init();
void Uninit(void);
void Update(void);
void Draw(void);


//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
bool g_bDispDebug = true;	// �f�o�b�O�\��ON/OFF


//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	// TSU�V�X�e����������
	if (FAILED(TsuSystem::Initialize(hInstance, "ShirabeniProject", "���g�v���W�F�N�g")))
		return -1;

	// ���̑�������
	if (FAILED(Init()))
		return -1;

	//�t���[���J�E���g������
	timeBeginPeriod(1);	// ����\�ݒ�
	FPSManager::Init();	// FPS����

	/* ���b�Z�[�W���[�v */
	while (1)
	{
		if (WindowClass::CheckMessage())
			break;

		if (FPSManager::FramerateControl())
		{
			PrintDebugProcess("FPS : %f\n", FPSManager::DisplayFPS(FPS_NORMAL));
			PrintDebugProcess("SCENE : ");
			switch (Scene::SetScene(SCENE_MAX))
			{
			case SCENE_TITLE:   PrintDebugProcess("Title\n");   break;
			case SCENE_GAME:    PrintDebugProcess("Game\n");   break;
			case SCENE_RESULT:  PrintDebugProcess("Result\n");   break;
			case SCENE_MAX:     PrintDebugProcess("������...\n");   break;
			case SCENE_END:     PrintDebugProcess("�I�������ł�(�\������Ȃ��͂�����)\n");   break;
			}

			Update();	// �X�V����
			Draw();		// �`�揈��
		}
	}

	TsuSystem::Uninitialize();	// TSU�V�X�e����������
	Uninit();					// ���̑��I������

	timeEndPeriod(1);	// ����\��߂�

	return 0;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init()
{
	// �t�F�[�h
	CSFade::MakeVertex();

	// �^�C�g���V�[���ɃZ�b�g
	Scene::SetScene(SCENE_GAME);

	// �J����
	InitCamera();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	Scene::SetScene(SCENE_END);

}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	// ���͂̍X�V����
	DirectInput::Update();

	if (Keyboard::Trigger(DIK_F3))
	{// �f�o�b�O�\��ON/OFF
		g_bDispDebug = g_bDispDebug ? false : true;
	}

	// �V�[���̍X�V
	Scene::Update();

	// �t�F�[�h�����̍X�V
	CSFade::Update();

}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();

	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0x66, 0x88, 0xFF, 0xFF), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(pDevice->BeginScene()))
	{
		// 3���K�C�h���C��
		TsuSystem::CoordinateAxis();

		// �V�[���̕`��
		Scene::Draw();

		// �t�F�[�h�`��
		CSFade::Draw();

		// �f�o�b�O�\���̕`�揈��
		if (g_bDispDebug)
		{
			DrawDebugProcess();
		}
		Dx9Line::Draw();

		// Direct3D�ɂ��`��̏I��
		pDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	if (pDevice->Present(NULL, NULL, NULL, NULL) == D3DERR_DEVICELOST)
	{// �f�o�C�X���X�g�̌��m
		if (pDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		{// ���A�\�̏ꍇ
			Direct3D::ResetDevice();
		}
	}
}


