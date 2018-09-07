//=============================================================================
//
// ���C������ [main.cpp]
//
//=============================================================================
#include "main.h"
#include "Library/Common.h"
#include "Library/WindowClass.h"
#include "Library/Direct3D.h"
#include "Library/FPSManager.h"
#include "Library/Input.h"
#include "Library/Sound.h"
#include "Library/Fade.h"
#include "Library/Camera.h"
#include "Result.h"
#include "Title.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"ShirabeniProject"	// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"���g�v���W�F�N�g"	// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �\���̒�`
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
bool		g_bDispDebug = true;	// �f�o�b�O�\��ON/OFF
GAMESCENE	g_GameScene = SCENE_MAX;


//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	// �E�B���h�E������
	if (FAILED(WindowClass::Init(hInstance)))
	{
		return -1;
	}
	// �O���t�B�b�N�X������(Direct3D)
	if (FAILED(Direct3D::Init(WindowClass::GetHWnd(), TRUE)))
	{
		return -1;
	}
	// �C���v�b�g������
	if (FAILED(InitInput(WindowClass::GetHInstance(), WindowClass::GetHWnd())))
	{
		return -1;
	}
	// �T�E���h������
	if (FAILED(DirectSound::Init(WindowClass::GetHWnd())))
	{
		return -1;
	}
	// ���̑�������
	if (FAILED(Init()))
	{
		return -1;
	}

	int updateCounter = 0;

	//�t���[���J�E���g������
	timeBeginPeriod(1);	// ����\�ݒ�
	FPSManager::Init();	// FPS����

	/* ���b�Z�[�W���[�v */
	while (1)
	{
		if (WindowClass::CheckMessage())
			break;

		// �X�V����
		updateCounter = FPSManager::ExactFPS(60);
		for (int i = 0; i < updateCounter && i < 4; i++)
		{
			Update();
		}

		// �`�揈��
		if (FPSManager::FramerateControl())
		{
			PrintDebugProcess("FPS : %f(%f)\n", FPSManager::DisplayFPS(FPS_NORMAL), FPSManager::DisplayFPS(FPS_EXACT));

			Draw();
		}
	}

	WindowClass::Uninit();	// �E�B���h�E�I��
	Direct3D::Uninit();		// �O���t�B�b�N�X�I��(Direct3D)
	UninitInput();	// ���͂̏I������
	DirectSound::Uninit();	// �T�E���h�I������
	Uninit();				// ���̑��I������


	timeEndPeriod(1);	// ����\��߂�

	return 0;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init()
{
	// �f�o�b�O�\���̏�����
	InitDebugProcess();

	// �t�F�[�h
	CSFade::MakeVertex();

	// �^�C�g���V�[���ɃZ�b�g
	SetGameScene(SCENE_TITLE);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	SetGameScene(SCENE_END);

	// �f�o�b�O�\�������̏I������
	UninitDebugProcess();
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	if (GetKeyboardTrigger(DIK_F3))
	{// �f�o�b�O�\��ON/OFF
		g_bDispDebug = g_bDispDebug ? false : true;
	}

	// ���͂̍X�V����
	UpdateInput();

	switch (g_GameScene)
	{
	case SCENE_TITLE:

		// �^�C�g���V�[���̍X�V����
		UpdateTitle();

		break;

	case SCENE_GAME:

		// �Q�[���V�[���̍X�V
		g_GameScene = SCENE_RESULT;

		break;

	case SCENE_RESULT:

		// ���U���g�V�[���̍X�V����
		UpdateResult();

		break;

	default:
		break;
	}

	// �t�F�[�h�����̍X�V
	CSFade::Update();

}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	Direct3D::GetD3DDevice()->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0x66, 0x88, 0xFF, 0xFF), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(Direct3D::GetD3DDevice()->BeginScene()))
	{
		switch (g_GameScene)
		{
		case SCENE_TITLE:

			// �^�C�g���V�[���̕`�揈��
			DrawTitle();

			break;

		case SCENE_GAME:

			// �Q�[���V�[���̕`�揈��

			break;

		case SCENE_RESULT:

			// ���U���g�̕`�揈��
			DrawResult();

			break;

		default:
			break;
		}

		// �t�F�[�h�`��
		CSFade::Draw();

		// �f�o�b�O�\���̕`�揈��
		if (g_bDispDebug)
		{
			DrawDebugProcess();
		}

		// Direct3D�ɂ��`��̏I��
		Direct3D::GetD3DDevice()->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	Direct3D::GetD3DDevice()->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �Q�[���V�[���̍X�V�E�擾
//=============================================================================
GAMESCENE SetGameScene(GAMESCENE scene)
{
	/* �w��V�[���������ꍇ�͖߂� */
	if (scene == SCENE_MAX)
	{
		return g_GameScene;
	}

	/* ���݂̃V�[���̂��Еt�� */
	switch (g_GameScene)
	{
	case SCENE_TITLE:

		// �^�C�g���V�[���̏I������
		UninitTitle();

		break;

	case SCENE_GAME:

		// �Q�[���V�[���̏I������ ���U���g�ɓ���
		//UninitGame();

		// �|�[�Y�V�[���̏I������

		// �J�b�g�C���V�[���̏I������

		break;

	case SCENE_RESULT:

		// ���U���g�V�[���̏I������
		UninitResult();

		// �Q�[���V�[���̏I������


		break;

	default:
		break;
	}

	/* ���̃V�[���̏��� */
	switch (scene)
	{
	case SCENE_TITLE:

		// �^�C�g���V�[���̏�����
		InitTitle();

		g_GameScene = SCENE_TITLE;

		break;

	case SCENE_GAME:

		// �Q�[���V�[���̏�����


		g_GameScene = SCENE_GAME;

		break;

	case SCENE_RESULT:

		// ���U���g�V�[���̏�����
		InitResult();

		g_GameScene = SCENE_RESULT;

		break;

	default:
		return g_GameScene;
		break;
	}

	g_GameScene = scene;

	return g_GameScene;
}

