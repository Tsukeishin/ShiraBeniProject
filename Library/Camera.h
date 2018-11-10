//=============================================================================
//
// �J�������� [Camera.h]
//
//=============================================================================
#ifndef _CAMERA_INCLUDE_H_
#define _CAMERA_INCLUDE_H_

#include "Common.h"
#include "Vector.h"
#include <Windows.h>


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VIEW_ANGLE  (D3DXToRadian(45))								// �r���[���ʂ̎���p(45�x)
#define	VIEW_ASPECT ((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z (10.0f)											// �r���[����_DEBUG_MODE_CAMERA_��NearZ�l
#define	VIEW_FAR_Z  (32768.0f)										// �r���[���ʂ�FarZ�l

#if _DEBUG
#define CAMERA_MOVE_VALUE	(2.0f)		// �ړ���
#define GAZE_MOVE_VALUE		(0.005f)	// �ړ���
#endif // _DEBUG


enum CAMERA_STATUS
{
	CAMERA_POSITION,	// �J�����̈ʒu
	CAMERA_FOCUS,		// �����_
	CAMERA_GAZE,		// �����x�N�g��
	CAMERA_ROTATION,	// �J�����̉�]
	CAMERA_UPSIDE,		// ������x�N�g��
};

//*****************************************************************************
// �\����
//*****************************************************************************


//*****************************************************************************
// �N���X�݌v
//*****************************************************************************
class CCamera
{
public:
	D3DXVECTOR3 Position;			// �J�����̍��W
	D3DXVECTOR3 Gaze;				// �J�����̎�����
	D3DXVECTOR3 UpVector;			// �J�����̏�����x�N�g��
	D3DXVECTOR3 Angle;				// �J�����̃A���O��
	float       Interval;			// �J�����̎��_�Ǝ�����̋���
	float       Sensitivity;		// �}�E�X���x

	D3DXMATRIX  ViewMatrix;			// �r���[�}�g���b�N�X
	D3DXMATRIX  ProjectionMatrix;	// �v���W�F�N�V�����}�g���b�N�X

public:
	CCamera();
	~CCamera();

	void Init(void);

	void Translation(Vector2 moveRate);
	void Rotation(Vector2 moveRate);
	void Scaling(float moveRate);
	void FollowingFocus(Vector3 correction);
	void Tracking(Vector3 target);

	void CreateMatrix(void);

	D3DXMATRIX GetViewMatrix(void);
	D3DXMATRIX GetProjectionMatrix(void);

private:

};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera();
void SetCamera(void);

D3DXMATRIX GetViewMatrix(void);
D3DXMATRIX GetProjectionMatrix(void);

#endif
