//=============================================================================
//
// �J�������� [Camera.cpp]
//
//=============================================================================
#include "Camera.h"
#include "Direct3D.h"
#include "Input.h"
#include "DebugProcess.h"


// �}�N����`
#define CtoA_INTERVAL_MAX	(640.0f)	// �J�����ƒ����_�Ԃ̍ő勗��
#define CtoA_INTERVAL_MIN	(320.0f)	// �J�����ƒ����_�Ԃ̍ŏ�����
#define CAMERA_ANGLE		(10)


//----�R���X�g���N�^--------
CCamera::CCamera()
{
	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Gaze = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	UpVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Angle = D3DXVECTOR3(0.0f, D3DXToRadian(90), 0.0f);
	Interval = CtoA_INTERVAL_MIN;
	Sensitivity = GAZE_MOVE_VALUE;
}

//----�f�X�g���N�^--------
CCamera::~CCamera()
{

}

//----������--------
void CCamera::Init(void)
{
	// �J�����̏�����
	Gaze = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Interval = CtoA_INTERVAL_MAX;
	Sensitivity = GAZE_MOVE_VALUE;

	UpVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Angle = D3DXVECTOR3(PI / 2, PI / 2, -PI / 2);

	Position.x = Interval * sinf(Angle.x) * cosf(Angle.z);
	Position.y = Interval * cosf(Angle.x);
	Position.z = Interval * sinf(Angle.x) * sinf(Angle.z);
	Position += Gaze;

}

//----���s�ړ�--------
void CCamera::Translation(D3DXVECTOR2 moveRate)
{
	/* �\���x�N�g�� */
	D3DXVECTOR3 LeftVec, FrontVec;
	D3DXVECTOR3 gazeVec = Gaze - Position;
	D3DXVECTOR3 subVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXVec3Cross(&LeftVec, &gazeVec, &subVec);
	D3DXVec3Normalize(&LeftVec, &LeftVec);
	D3DXVec3Cross(&FrontVec, &LeftVec, &gazeVec);
	D3DXVec3Normalize(&FrontVec, &FrontVec);
	D3DXVec3Normalize(&gazeVec, &gazeVec);

	/* ���_���s�ړ� */
	if (IsMouseCenterPressed())
	{
		Gaze += LeftVec *  moveRate.x * CAMERA_MOVE_VALUE;
		Gaze += FrontVec * moveRate.y * CAMERA_MOVE_VALUE;
	}

#ifdef _DEBUG
	PrintDebugProcess("�f�o�b�O�J�����ʒu : (%v)\n", Position);
	PrintDebugProcess("�f�o�b�O�J�������� : (%v)\n", Gaze);
	PrintDebugProcess("�f�o�b�O�J����Angl : (%v)\n", Angle);
#endif // _DEBUG

}

//----�O��ړ�--------
void CCamera::Scaling(float moveRate)
{
	D3DXVECTOR3 gazeVec = Gaze - Position;

	/* �g��E�k�� */
	//gazeVec *= moveRate * 0.001f;
	//Gaze += gazeVec;

	Interval -= moveRate;
}

//----����ړ�--------
void CCamera::Rotation(D3DXVECTOR2 moveRate)
{
	/* �J�����ʒu */
	// �ړ�����
	if (IsMouseLeftPressed())
	{
		Angle.x -= moveRate.y * Sensitivity;
		Angle.z -= moveRate.x * Sensitivity;
		Angle.y += moveRate.x * Sensitivity;
	}
	if (GetKeyboardPress(DIK_LSHIFT))
	{
		Angle.z -= 0.05f;
	}
	/* �ړ��͈͐��� */
	if (Angle.x > D3DXToRadian(179))
	{
		Angle.x = D3DXToRadian(179);
	}
	if (Angle.x < D3DXToRadian(1))
	{
		Angle.x = D3DXToRadian(1);
	}
	if (Angle.z > D3DX_PI)
	{
		Angle.z -= D3DX_PI * 2.0f;
		Angle.y += D3DX_PI * 2.0f;
	}
	if (Angle.z < -D3DX_PI)
	{
		Angle.z += D3DX_PI * 2.0f;
		Angle.y -= D3DX_PI * 2.0f;
	}

	/* ���̍��W�ֈړ� */
	float sinTheta = sinf(Angle.x);
	Position.x = Interval * sinTheta * cosf(Angle.z);
	Position.y = Interval * cosf(Angle.x);
	Position.z = Interval * sinTheta * sinf(Angle.z);
	// ���̍��W�̔��f
	Position += Gaze;
}

//----�ǔ�--------
void CCamera::Tracking(D3DXVECTOR3 target)
{
	Gaze = target + D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	Position.x = 0.0f;
	Position.y = Interval * sinf(D3DXToRadian(CAMERA_ANGLE));
	Position.z = Interval * -cosf(D3DXToRadian(CAMERA_ANGLE));
	Position += Gaze;
}

//----������Ǐ]--------
void CCamera::FollowingFocus(D3DXVECTOR3 correction)
{
	Position = Gaze + correction;
}

//----�}�g���b�N�X����--------
void CCamera::CreateMatrix(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();

	/* �r���[�}�g���b�N�X */
	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&ViewMatrix);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&ViewMatrix,
		&Position,		// �J�����̎��_
		&Gaze,			// ������
		&UpVector);		// �����

						// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &ViewMatrix);


	/* �v���W�F�N�V�����}�g���b�N�X */
	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&ProjectionMatrix);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&ProjectionMatrix,
		VIEW_ANGLE,		// �r���[���ʂ̎���p
		VIEW_ASPECT,	// �r���[���ʂ̃A�X�y�N�g��
		VIEW_NEAR_Z,	// �r���[���ʂ�NearZ�l
		VIEW_FAR_Z);	// �r���[���ʂ�FarZ�l

						// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &ProjectionMatrix);
}

/*----�擾�֐�----*/
D3DXMATRIX CCamera::GetViewMatrix(void)			{ return ViewMatrix; }			//--�r���[�}�g���b�N�X
D3DXMATRIX CCamera::GetProjectionMatrix(void)	{ return ProjectionMatrix; }	//--�v���W�F�N�g�}�g���b�N�X


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CCamera GameCamera;

#if _DEBUG
CCamera DebugCamera;
bool DebugCameraFlag = false;
#endif // _DEBUG


//=============================================================================
// ����������
//=============================================================================
HRESULT InitCamera(void)
{
	// �Q�[���J����
	GameCamera.Init();

#if _DEBUG
	// �f�o�b�N�J����
	DebugCamera.Init();
#endif // _DEBUG


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCamera(D3DXVECTOR3 target)
{
	// �Q�[���J����
	GameCamera.Rotation(D3DXVECTOR2((float)GetMouseX(), (float)GetMouseY()));
	GameCamera.Translation(D3DXVECTOR2((float)GetMouseX(), (float)GetMouseY()));
	GameCamera.Scaling((float)GetMouseZ());
}

//=============================================================================
// �`�揈��
//=============================================================================
void SetCamera(void)
{
#if _DEBUG
	if (DebugCameraFlag)
	{
		// �f�o�b�N�J����
		DebugCamera.CreateMatrix();
	}
	else
	{
		// �Q�[���J����
		GameCamera.CreateMatrix();
	}
#else
	// �Q�[���J����
	GameCamera.CreateMatrix();
#endif // _DEBUG

}

//=============================================================================
// �}�g���b�N�X�擾�֐�
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return GameCamera.GetViewMatrix();
}
D3DXMATRIX GetProjectionMatrix(void)
{
	return GameCamera.GetProjectionMatrix();
}

