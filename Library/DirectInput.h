/*===========================================================================*/
/*                                                                           */
/* DirectInput.h                                                             */
/*                                                                           */
/*===========================================================================*/
#ifndef __DIRECT_INPUT_H_INCLUDE__
#define __DIRECT_INPUT_H_INCLUDE__


#define DIRECTINPUT_VERSION (0x0800)	// �x���΍�
#include "Vector.h"
#include <Windows.h>
#include <dinput.h>
#include <tchar.h>
#pragma comment (lib, "dinput8.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �v���O������������Ƃ��Ɏg��
#define USE_KEYBOARD	// �錾����ƃL�[�{�[�h�ő���\�ɂȂ�
#define USE_MOUSE		// �錾����ƃ}�E�X�ő���\�ɂȂ�
#define USE_PAD			// �錾����ƃp�b�h�ő���\�ɂȂ�

/* �L�[�{�[�h */
#define	NUM_KEY_MAX (256)

/* �}�E�X�\����� */
// ����
#define MOUSE_SET_CENTER	SetCursorPos((int)LAST_GAME_SCREEN_CENTER_X, (int)LAST_GAME_SCREEN_CENTER_Y)

/* GamePad */
#define RANGE_VALUE (1000)	// �L���͈́i��Βl�j

/* game pad��� */
#define LSTICK_UP		0x00000001l	// ���X�e�B�b�N��(.IY<0)
#define LSTICK_DOWN		0x00000002l	// ���X�e�B�b�N��(.IY>0)
#define LSTICK_LEFT		0x00000004l	// ���X�e�B�b�N��(.IX<0)
#define LSTICK_RIGHT	0x00000008l	// ���X�e�B�b�N�E(.IX>0)
#define TRIGGER_LEFT	0x00000010l	// ���g���K�[(.IZ<0)
#define TRIGGER_RIGHT	0x00000020l	// �E�g���K�[(.IZ>0)
#define RSTICK_UP		0x00000100l	// �E�X�e�B�b�N��(.IRy<0)
#define RSTICK_DOWN		0x00000200l	// �E�X�e�B�b�N��(.IRy>0)
#define RSTICK_LEFT		0x00000400l	// �E�X�e�B�b�N��(.IRx<0)
#define RSTICK_RIGHT	0x00000800l	// �E�X�e�B�b�N�E(.IRx>0)
#define POV_UP			0x00001000l	// �\���L�[��(.rgdwPOV[0]==0)
#define POV_RIGHT		0x00002000l	// �\���L�[�E(.rgdwPOV[0]==9000)
#define POV_DOWN		0x00004000l	// �\���L�[��(.rgdwPOV[0]==18000)
#define POV_LEFT		0x00008000l	// �\���L�[��(.rgdwPOV[0]==27000)
#define BUTTON_A		0x00100000l	// �`�{�^��(.rgbButtons[0]&0x80)
#define BUTTON_B		0x00200000l	// �a�{�^��(.rgbButtons[1]&0x80)
#define BUTTON_X		0x00400000l	// �w�{�^��(.rgbButtons[2]&0x80)
#define BUTTON_Y		0x00800000l	// �x�{�^��(.rgbButtons[3]&0x80)
#define BUTTON_L		0x01000000l	// LB�{�^��(.rgbButtons[4]&0x80)
#define BUTTON_R		0x02000000l	// RB�{�^��(.rgbButtons[5]&0x80)
#define BUTTON_BACK		0x04000000l	// BACK�{�^��(.rgbButtons[6]&0x80)
#define BUTTON_START	0x08000000l	// START�{�^��(.rgbButtons[7]&0x80)
#define BUTTON_LS		0x10000000l	// ���X�e�B�b�N�{�^��(.rgbButtons[8]&0x80)
#define BUTTON_RS		0x20000000l	// �E�X�e�B�b�N�{�^��(.rgbButtons[9]&0x80)
#define GAMEPADMAX		4			// �����ɐڑ�����W���C�p�b�h�̍ő吔���Z�b�g


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
typedef class DirectInput
{
	static LPDIRECTINPUT8 DirectInput8;		// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^

public:
	static HRESULT Init(HINSTANCE hInst, HWND hWnd);
	static HRESULT Update();
	static void    Uninit();

	class Keyboard
	{
		static LPDIRECTINPUTDEVICE8 DirectInputDevice;		// �L�[�{�[�h�̃C���^�[�t�F�[�X�ւ̃|�C���^(IP)
		static BYTE                 State[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
		static BYTE                 StateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
		static BYTE                 StateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
		static BYTE                 StateRepeat[NUM_KEY_MAX];	// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
		static int                  StateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^

	public:
		static HRESULT Init(HINSTANCE hInst, HWND hWnd);
		static HRESULT Update();
		static void    Uninit();

		static bool Pressed(int nKey);
		static bool Trigger(int nKey);
		static bool Repeat(int nKey);
		static bool Release(int nKey);

	};
	class Mouse
	{
		static LPDIRECTINPUTDEVICE8 DirectInputDevice;	// �L�[�{�[�h��IP
		static DIMOUSESTATE2        State;				// �}�E�X�̃_�C���N�g�ȏ��
		static DIMOUSESTATE2        Trigger;			// �����ꂽ�u�Ԃ���ON
		static POINT                Coordinate;			// �}�E�X�J�[�\���̐�Έʒu(�X�N���[��)

	public:
		static HRESULT Init(HINSTANCE hInst, HWND hWnd);
		static HRESULT Update();
		static void    Uninit();

		static BOOL     LPressed(void);		// ���N���b�N�������
		static BOOL     LTrigger(void);		// ���N���b�N�����u��
		static BOOL     RPressed(void);		// �E�N���b�N�������
		static BOOL     RTrigger(void);		// �E�N���b�N�����u��
		static BOOL     CPressed(void);		// ���N���b�N�������
		static BOOL     CTrigger(void);		// ���N���b�N�����u��
		static long     MovementX(void);	// �}�E�X��X�����ɓ��������Βl
		static long     MovementY(void);	// �}�E�X��Y�����ɓ��������Βl
		static long     MovementZ(void);	// �}�E�X�z�C�[�������������Βl
		static POINT    GlobalCoord(void);	// �}�E�X�̃O���[�o�����W
		static Vector2  LocalCoord(void);	// �}�E�X�̃��[�J�����W

	};
	class GamePad
	{
		static LPDIRECTINPUTDEVICE8 DirectInputDevice[GAMEPADMAX];	// �Q�[���p�b�h��IP
		static DWORD                State[GAMEPADMAX];				// �p�b�h���i�����Ή��j
		static DWORD                StateTrigger[GAMEPADMAX];		// �p�b�h���i�����Ή��j
		static Vector2              LsRoll[GAMEPADMAX];				// ���X�e�B�b�N�̓|���
		static Vector2              RsRoll[GAMEPADMAX];				// �E�X�e�B�b�N�̓|���
		static int                  Count;							// ���o�����p�b�h�̐�

	public:
		static HRESULT Init();
		static BOOL CALLBACK Callback(LPDIDEVICEINSTANCE lpddi, LPVOID);	// �p�b�h�����R�[���o�b�N
		static HRESULT Update();
		static void    Uninit();

		static BOOL     Pressed(int padNo, DWORD button);
		static BOOL     Trigger(int padNo, DWORD button);
		static Vector2  LStickVolume(int padNo);
		static Vector2  RStickVolume(int padNo);

	};

}DInput;

typedef DirectInput::Keyboard Keyboard;
typedef DirectInput::Mouse    Mouse;
typedef DirectInput::GamePad  GamePad;


#endif