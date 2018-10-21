//=============================================================================
//
// ���͏��� [input.h]
//
//=============================================================================
#ifndef __INPUT_INCLUDE_H__
#define __INPUT_INCLUDE_H__


#define DIRECTINPUT_VERSION (0x0800)	// �x���΍�
#include "Vector.h"
#include <dinput.h>
#include <Windows.h>
#include <tchar.h>
#pragma comment (lib, "dinput8.lib")


//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �v���O������������Ƃ��Ɏg��
#define USE_KEYBOARD	// �錾����ƃL�[�{�[�h�ő���\�ɂȂ�
#define USE_MOUSE		// �錾����ƃ}�E�X�ő���\�ɂȂ�
#define USE_PAD			// �錾����ƃp�b�h�ő���\�ɂȂ�

/* �}�E�X�\����� */
// ����
#define MOUSE_SET_CENTER	SetCursorPos((int)LAST_GAME_SCREEN_CENTER_X, (int)LAST_GAME_SCREEN_CENTER_Y)

/* GamePad */
#define RANGE_VALUE (1000)	// �L���͈́i��Βl�j

/* game pad��� */
#define LSTICK_UP       0x00000001L	// ���X�e�B�b�N��(.IY<0)
#define LSTICK_DOWN     0x00000002L	// ���X�e�B�b�N��(.IY>0)
#define LSTICK_LEFT     0x00000004L	// ���X�e�B�b�N��(.IX<0)
#define LSTICK_RIGHT    0x00000008L	// ���X�e�B�b�N�E(.IX>0)
#define TRIGGER_LEFT    0x00000010L	// ���g���K�[(.IZ<0)
#define TRIGGER_RIGHT   0x00000020L	// �E�g���K�[(.IZ>0)
#define RSTICK_UP       0x00000100L	// �E�X�e�B�b�N��(.IRy<0)
#define RSTICK_DOWN     0x00000200L	// �E�X�e�B�b�N��(.IRy>0)
#define RSTICK_LEFT     0x00000400L	// �E�X�e�B�b�N��(.IRx<0)
#define RSTICK_RIGHT    0x00000800L	// �E�X�e�B�b�N�E(.IRx>0)
#define POV_UP          0x00001000L	// �\���L�[��(.rgdwPOV[0]==0)
#define POV_RIGHT       0x00002000L	// �\���L�[�E(.rgdwPOV[0]==9000)
#define POV_DOWN        0x00004000L	// �\���L�[��(.rgdwPOV[0]==18000)
#define POV_LEFT        0x00008000L	// �\���L�[��(.rgdwPOV[0]==27000)
#define BUTTON_A        0x00100000L	// �`�{�^��(.rgbButtons[0]&0x80)
#define BUTTON_B        0x00200000L	// �a�{�^��(.rgbButtons[1]&0x80)
#define BUTTON_X        0x00400000L	// �w�{�^��(.rgbButtons[2]&0x80)
#define BUTTON_Y        0x00800000L	// �x�{�^��(.rgbButtons[3]&0x80)
#define BUTTON_L        0x01000000L	// LB�{�^��(.rgbButtons[4]&0x80)
#define BUTTON_R        0x02000000L	// RB�{�^��(.rgbButtons[5]&0x80)
#define BUTTON_BACK     0x04000000L	// BACK�{�^��(.rgbButtons[6]&0x80)
#define BUTTON_START    0x08000000L	// START�{�^��(.rgbButtons[7]&0x80)
#define BUTTON_LS       0x10000000L	// ���X�e�B�b�N�{�^��(.rgbButtons[8]&0x80)
#define BUTTON_RS       0x20000000L	// �E�X�e�B�b�N�{�^��(.rgbButtons[9]&0x80)
#define GAMEPADMAX      4			// �����ɐڑ�����W���C�p�b�h�̍ő吔���Z�b�g


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

//---------------------------- keyboard
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);

//---------------------------- mouse
BOOL IsMouseLeftPressed(void);      // ���N���b�N�������
BOOL IsMouseLeftTriggered(void);    // ���N���b�N�����u��
BOOL IsMouseLeftRepeat(void);       // ���N���b�N��������
BOOL IsMouseLeftRelease(void);      // ���𗣂����u��
BOOL IsMouseRightPressed(void);     // �E�N���b�N�������
BOOL IsMouseRightTriggered(void);   // �E�N���b�N�����u��
BOOL IsMouseRightRepeat(void);      // �E�N���b�N��������
BOOL IsMouseRightRelease(void);     // �E�𗣂����u��
BOOL IsMouseCenterPressed(void);    // ���N���b�N�������
BOOL IsMouseCenterTriggered(void);  // ���N���b�N�����u��
BOOL IsMouseCenterRepeat(void);     // ���N���b�N��������
BOOL IsMouseCenterRelease(void);    // ���𗣂����u��
long GetMouseX(void);               // �}�E�X��X�����ɓ��������Βl
long GetMouseY(void);               // �}�E�X��Y�����ɓ��������Βl
long GetMouseZ(void);               // �}�E�X�z�C�[�������������Βl
POINT GetScreenMouse(void);         // �}�E�X�̃X�N���[�����W
Vector2 GetLocalMouse(void);        // �}�E�X�̃��[�J�����W

//---------------------------- game pad
BOOL IsButtonPressed(int padNo, DWORD button);
BOOL IsButtonTriggered(int padNo, DWORD button);
D3DXVECTOR2 GetLStickVolume(int padNo);
D3DXVECTOR2 GetRStickVolume(int padNo);

HRESULT InitializePad(void);			// �p�b�h������

#endif