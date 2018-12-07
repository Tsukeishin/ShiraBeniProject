/*===========================================================================*/
/*                                                                           */
/* DirectInput.cpp                                                           */
/*                                                                           */
/*===========================================================================*/
#include "DirectInput.h"
#include "Math.h"
#include "WindowClass.h"


// game pad�p�ݒ�l
#define DEADZONE		(1000)		// �e����10%�𖳌��]�[���Ƃ���
#define RANGE_MAX		 RANGE_VALUE	// �L���͈͂̍ő�l
#define RANGE_MIN		-RANGE_VALUE	// �L���͈͂̍ŏ��l (*�����p��)


//----DirectInput8 Interface--------
LPDIRECTINPUT8  DirectInput::DirectInput8 = NULL;	// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^

//----�L�[�{�[�h (keyboard)--------
LPDIRECTINPUTDEVICE8 DirectInput::Keyboard::DirectInputDevice = NULL;		// �L�[�{�[�h��(IP)
BYTE                 DirectInput::Keyboard::State[NUM_KEY_MAX];				// �L�[�{�[�h�̏�ԃ��[�N
BYTE                 DirectInput::Keyboard::StateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̏�ԃ��[�N
BYTE                 DirectInput::Keyboard::StateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̏�ԃ��[�N
BYTE                 DirectInput::Keyboard::StateRelease[NUM_KEY_MAX];		// �L�[�{�[�h�̏�ԃ��[�N
int                  DirectInput::Keyboard::StateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h��RepeatCnt

//----�}�E�X (mouse)--------
LPDIRECTINPUTDEVICE8 DirectInput::Mouse::DirectInputDevice = NULL;	// �}�E�X��IP
DIMOUSESTATE2        DirectInput::Mouse::State;						// �}�E�X�̃_�C���N�g�ȏ��
DIMOUSESTATE2        DirectInput::Mouse::Trigger;					// �����ꂽ�u�Ԃ���ON
POINT                DirectInput::Mouse::Coordinate;				// �}�E�X�J�[�\���̐�΍��W�̎擾

//----�Q�[���p�b�h (game pad)--------

LPDIRECTINPUTDEVICE8 DirectInput::GamePad::DirectInputDevice[GAMEPADMAX] = { NULL };// �Q�[���p�b�h��IP
DWORD                DirectInput::GamePad::State[GAMEPADMAX];			// �p�b�h���
DWORD                DirectInput::GamePad::StateTrigger[GAMEPADMAX];	// �p�b�h���
Vector2              DirectInput::GamePad::LsRoll[GAMEPADMAX];			// ���X�e�B�b�N�̓|���
Vector2              DirectInput::GamePad::RsRoll[GAMEPADMAX];			// �E�X�e�B�b�N�̓|���
int                  DirectInput::GamePad::Count;						// ���o�����p�b�h�̐�


/*================================================================*/
/* ���͏����̏����� */
/*================================================================*/
HRESULT DirectInput::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	if(!DirectInput8)
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
									IID_IDirectInput8, (void**)&DirectInput8, NULL);
	}

	// �L�[�{�[�h�̏�����
	DirectInput::Keyboard::Init(hInst, hWnd);

 	// �}�E�X�̏�����
	DirectInput::Mouse::Init(hInst, hWnd);
	
	// �p�b�h�̏�����
	DirectInput::GamePad::Init();

	return S_OK;
}

/*================================================================*/
/* ���͏����̍X�V���� */
/*================================================================*/
HRESULT DirectInput::Update()
{
	// �L�[�{�[�h�̍X�V
	DirectInput::Keyboard::Update();
	
	// �}�E�X�̍X�V
	DirectInput::Mouse::Update();
	
	// �p�b�h�̍X�V
	DirectInput::GamePad::Update();

	return S_OK;
}

/*================================================================*/
/* ���͏����̏I������ */
/*================================================================*/
void DirectInput::Uninit()
{
	// �L�[�{�[�h�̏I������
	DirectInput::Keyboard::Uninit();

	// �}�E�X�̏I������
	DirectInput::Mouse::Uninit();

	// �p�b�h�̏I������
	DirectInput::GamePad::Uninit();

	if(DirectInput8)
	{
		DirectInput8->Release();
		DirectInput8 = NULL;
	}
}


/*================================================================*/
/* �L�[�{�[�h�֌W�̏��� */
/*================================================================*/
//==== �L�[�{�[�h�̏����� ====//
HRESULT DirectInput::Keyboard::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = DirectInput8->CreateDevice(GUID_SysKeyboard, &DirectInputDevice, NULL);
	if(FAILED(hr) || DirectInputDevice == NULL)
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = DirectInputDevice->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = DirectInputDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	DirectInputDevice->Acquire();

	return S_OK;
}

//==== �L�[�{�[�h�̍X�V ====//
HRESULT DirectInput::Keyboard::Update(void)
{
	HRESULT hr;
	BYTE keyStateOld[256];

	// �O��̃f�[�^��ۑ�
	memcpy(keyStateOld, State, NUM_KEY_MAX);

	// �f�o�C�X����f�[�^���擾
	hr = DirectInputDevice->GetDeviceState(sizeof(State), State);
	if(SUCCEEDED(hr))
	{
		for(int cnt = 0; cnt < NUM_KEY_MAX; cnt++)
		{
			StateTrigger[cnt] = (keyStateOld[cnt] ^ State[cnt]) & State[cnt];
			StateRelease[cnt] = (keyStateOld[cnt] ^ State[cnt]) & ~State[cnt];
			StateRepeat[cnt] = StateTrigger[cnt];

			if(State[cnt])
			{
				StateRepeatCnt[cnt]++;
				if(StateRepeatCnt[cnt] >= 20)
				{
					StateRepeat[cnt] = State[cnt];
				}
			}
			else
			{
				StateRepeatCnt[cnt] = 0;
				StateRepeat[cnt] = 0;
			}
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		DirectInputDevice->Acquire();
	}

	return S_OK;
}

//==== �L�[�{�[�h�̏I�� ====//
void DirectInput::Keyboard::Uninit(void)
{
	if(DirectInputDevice)
	{
		DirectInputDevice->Release();
		DirectInputDevice = NULL;
	}
}

//----�L�[�{�[�h�̏����擾--------
bool DirectInput::Keyboard::Pressed(int key)
{
	return (State[key] & 0x80) ? true : false;
}
bool DirectInput::Keyboard::Trigger(int key)
{
	return (StateTrigger[key] & 0x80) ? true : false;
}
bool DirectInput::Keyboard::Repeat(int key)
{
	return (StateRepeat[key] & 0x80) ? true : false;
}
bool DirectInput::Keyboard::Release(int key)
{
	return (StateRelease[key] & 0x80) ? true : false;
}


/*================================================================*/
/* �}�E�X�֌W�̏��� */
/*================================================================*/
//==== �}�E�X�̏����� ====//
HRESULT DirectInput::Mouse::Init(HINSTANCE hInst,HWND hWindow)
{
	HRESULT result;
	// �f�o�C�X�쐬
	result = DirectInput8->CreateDevice(GUID_SysMouse,&DirectInputDevice,NULL);
	if(FAILED(result) || DirectInputDevice==NULL)
	{
		MessageBox(hWindow,"No mouse","Warning",MB_OK | MB_ICONWARNING);
		return result;
	}
	// �f�[�^�t�H�[�}�b�g�ݒ�
	result = DirectInputDevice->SetDataFormat(&c_dfDIMouse2);
	if(FAILED(result))
	{
		MessageBox(hWindow,"Can't setup mouse","Warning",MB_OK | MB_ICONWARNING);
		return result;
	}
	// ���̃A�v���Ƌ������[�h�ɐݒ�
	result = DirectInputDevice->SetCooperativeLevel(hWindow, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(result))
	{
		MessageBox(hWindow,"Mouse mode error","Warning",MB_OK | MB_ICONWARNING);
		return result;
	}
	
	// �f�o�C�X�̐ݒ�
	DIPROPDWORD prop;
	
	prop.diph.dwSize = sizeof(prop);
	prop.diph.dwHeaderSize = sizeof(prop.diph);
	prop.diph.dwObj = 0;
	prop.diph.dwHow = DIPH_DEVICE;
	prop.dwData = DIPROPAXISMODE_REL;		// �}�E�X�̈ړ��l ���Βl

	result = DirectInputDevice->SetProperty(DIPROP_AXISMODE,&prop.diph);
	if(FAILED(result))
	{
		MessageBox(hWindow,"Mouse property error","Warning",MB_OK | MB_ICONWARNING);
		return result;	
	}
	
	// �A�N�Z�X���𓾂�
	DirectInputDevice->Acquire();
	return result;
}

//==== �}�E�X�̍X�V ====//
HRESULT DirectInput::Mouse::Update()
{
	HRESULT result;

	// �O��̒l�ۑ�
	DIMOUSESTATE2 lastMouseState = State;
	// �f�[�^�擾
	result = DirectInputDevice->GetDeviceState(sizeof(State), &State);
	if (SUCCEEDED(result))
	{
		Trigger.lX = State.lX;
		Trigger.lY = State.lY;
		Trigger.lZ = State.lZ;
		// �}�E�X�̃{�^�����
		for (int i = 0; i < 8; i++)
		{
			Trigger.rgbButtons[i] = ((lastMouseState.rgbButtons[i] ^
				State.rgbButtons[i]) & State.rgbButtons[i]);
		}
	}
	else	// �擾���s
	{
		// �A�N�Z�X���𓾂Ă݂�
		result = DirectInputDevice->Acquire();
	}

	//�}�E�X�̌��݂̍��W���擾����
	GetCursorPos(&Coordinate);

	return result;
}

//==== �}�E�X�̏I�� ====//
void DirectInput::Mouse::Uninit()
{
	if(DirectInputDevice)
	{
		DirectInputDevice->Unacquire();
		DirectInputDevice->Release();
		DirectInputDevice = NULL;
	}

}

/*----�}�E�X�̏����擾--------*/
//----�N���b�N���--------
BOOL DirectInput::Mouse::LPressed(void)
{
	return (BOOL)(State.rgbButtons[0] & 0x80);	// �����ꂽ�Ƃ��ɗ��r�b�g������
}
BOOL DirectInput::Mouse::LTrigger(void)
{
	return (BOOL)(Trigger.rgbButtons[0] & 0x80);
}
BOOL DirectInput::Mouse::RPressed(void)
{
	return (BOOL)(State.rgbButtons[1] & 0x80);
}
BOOL DirectInput::Mouse::RTrigger(void)
{
	return (BOOL)(Trigger.rgbButtons[1] & 0x80);
}
BOOL DirectInput::Mouse::CPressed(void)
{
	return (BOOL)(State.rgbButtons[2] & 0x80);
}
BOOL DirectInput::Mouse::CTrigger(void)
{
	return (BOOL)(Trigger.rgbButtons[2] & 0x80);
}
//----�ړ���--------
long DirectInput::Mouse::MovementX(void)
{
	return State.lX;
}
long DirectInput::Mouse::MovementY(void)
{
	return State.lY;
}
long DirectInput::Mouse::MovementZ(void)
{
	return State.lZ;
}
//----���W--------
POINT   DirectInput::Mouse::GlobalCoord(void)
{
	return Coordinate;
}
Vector2 DirectInput::Mouse::LocalCoord(void)
{
	/* �}�E�X�̃X�N���[���i�O���[�o���j���W */
	X2<LONG> mousePoint = X2<LONG>(Coordinate.x, Coordinate.y);

	/* �E�B���h�E�̍�����W���擾 */
	RECT rect;
	GetWindowRect(WindowClass::GetHWnd(), &rect);
	X2<LONG> windowPoint = X2<LONG>(rect.left, rect.top);

	/* �E�B���h�E�g���̍������v�Z���AWindow�̌��_�̃X�N���[�����W�����߂� */
	X2<LONG> windOrigin;
	windOrigin.x = windowPoint.x + (LONG)GetSystemMetrics(SM_CXDLGFRAME);
	windOrigin.y = windowPoint.y + (LONG)GetSystemMetrics(SM_CXDLGFRAME) + (LONG)GetSystemMetrics(SM_CYCAPTION);

	/* �}�E�X�̃��[�J�����W�����߂� */
	X2<LONG> retCoord = mousePoint - windOrigin;

	return Vector2((float)retCoord.x, (float)retCoord.y);
}


/*================================================================*/
/* �Q�[���p�b�h�֌W�̏��� */
/*================================================================*/
//==== �R�[���o�b�N�֐� ====//
BOOL CALLBACK DirectInput::GamePad::Callback(LPDIDEVICEINSTANCE lpddi, LPVOID )
{
	HRESULT result;

	result = DirectInput8->CreateDevice(lpddi->guidInstance, &DirectInputDevice[Count++], NULL);
	return DIENUM_CONTINUE;	// ���̃f�o�C�X���

}

//==== �Q�[���p�b�h�̏����� ====//
HRESULT DirectInput::GamePad::Init(void)			// �p�b�h������
{
	HRESULT		result;
	int			i;

	Count = 0;
	// �W���C�p�b�h��T��
	DirectInput8->EnumDevices(DI8DEVCLASS_GAMECTRL,
		(LPDIENUMDEVICESCALLBACK)DirectInput::GamePad::Callback,
		NULL,
		DIEDFL_ATTACHEDONLY);
	// �Z�b�g�����R�[���o�b�N�֐����A�p�b�h�𔭌������������Ă΂��B

	for (i = 0; i < Count; i++) {
		// �W���C�X�e�B�b�N�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�
		result = DirectInputDevice[i]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(result))
			return false; // �f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s

		// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
//		result = DirectInputDevice[i]->SetCooperativeLevel(hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
//		if ( FAILED(result) )
//			return false; // ���[�h�̐ݒ�Ɏ��s

		// ���̒l�͈̔͂�ݒ�
		// X���AY���̂��ꂼ��ɂ��āA�I�u�W�F�N�g���񍐉\�Ȓl�͈̔͂��Z�b�g����B
		// (max-min)�́A�ő�10,000(?)�B(max-min)/2�������l�ɂȂ�B
		// ����傫������΁A�A�i���O�l�ׂ̍��ȓ�����߂炦����B(�p�b�h�̐��\�ɂ��)
		DIPROPRANGE				diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = -RANGE_MAX; //* /=RANGE_MIN
		diprg.lMax = RANGE_MAX;
		// X���͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_X;
		DirectInputDevice[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y���͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_Y;
		DirectInputDevice[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Z���͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_Z;
		DirectInputDevice[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// X��]�͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_RX;
		DirectInputDevice[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y��]�͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_RY;
		DirectInputDevice[i]->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �e�����ƂɁA�����̃]�[���l��ݒ肷��B
		// �����]�[���Ƃ́A��������̔����ȃW���C�X�e�B�b�N�̓����𖳎�����͈͂̂��ƁB
		// �w�肷��l�́A10000�ɑ΂��鑊�Βl(2000�Ȃ�20�p�[�Z���g)�B
		DIPROPDWORD				dipdw;
		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwHow = DIPH_BYOFFSET;
		dipdw.dwData = DEADZONE;
		//X���̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_X;
		DirectInputDevice[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Y���̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_Y;
		DirectInputDevice[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Z���̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_Z;
		DirectInputDevice[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//X��]�̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_RX;
		DirectInputDevice[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Y��]�̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_RY;
		DirectInputDevice[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

		//�W���C�X�e�B�b�N���͐���J�n
		DirectInputDevice[i]->Acquire();
	}

	return true;

}

//==== �Q�[���p�b�h�̍X�V ====//
HRESULT DirectInput::GamePad::Update(void)
{
	HRESULT			result = S_OK;
	DIJOYSTATE2		dijs;
	int				i;

	for (i = 0; i < Count; i++)
	{
		DWORD lastPadState;
		lastPadState = State[i];
		State[i] = 0x00000000l;	// ������

		result = DirectInputDevice[i]->Poll();	// �W���C�X�e�B�b�N�Ƀ|�[����������
		if (FAILED(result)) {
			result = DirectInputDevice[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = DirectInputDevice[i]->Acquire();
		}

		result = DirectInputDevice[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// �f�o�C�X��Ԃ�ǂݎ��
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED) {
			result = DirectInputDevice[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = DirectInputDevice[i]->Acquire();
		}

		// �R�Q�̊e�r�b�g�ɈӖ����������A�{�^�������ɉ����ăr�b�g���I���ɂ���
		//* y-axis (Lforward)
		if (dijs.lY < 0)			State[i] |= LSTICK_UP;
		//* y-axis (Lbackward)
		if (dijs.lY > 0)			State[i] |= LSTICK_DOWN;
		//* x-axis (Lleft)
		if (dijs.lX < 0)			State[i] |= LSTICK_LEFT;
		//* x-axis (Lright)
		if (dijs.lX > 0)			State[i] |= LSTICK_RIGHT;
		//* z-axis (lefttrigger)
		if (dijs.lZ > 0)			State[i] |= TRIGGER_LEFT;
		//* z-axis (righttrigger)
		if (dijs.lZ < 0)			State[i] |= TRIGGER_RIGHT;
		//* y-axis (Rforward)
		if (dijs.lRy < 0)			State[i] |= RSTICK_UP;
		//* y-axis (Rbackward)
		if (dijs.lRy > 0)			State[i] |= RSTICK_DOWN;
		//* x-axis (Rleft)
		if (dijs.lRx < 0)			State[i] |= RSTICK_LEFT;
		//* x-axis (Rright)
		if (dijs.lRx > 0)			State[i] |= RSTICK_RIGHT;

		//* �\���L�[��
		if (dijs.rgdwPOV[0] == 0)		State[i] |= POV_UP;
		//* �\���L�[�E
		if (dijs.rgdwPOV[0] == 9000)	State[i] |= POV_RIGHT;
		//* �\���L�[��
		if (dijs.rgdwPOV[0] == 18000)	State[i] |= POV_DOWN;
		//* �\���L�[��
		if (dijs.rgdwPOV[0] == 27000)	State[i] |= POV_LEFT;
		//* �`�{�^��
		if (dijs.rgbButtons[0] & 0x80)	State[i] |= BUTTON_A;
		//* �a�{�^��
		if (dijs.rgbButtons[1] & 0x80)	State[i] |= BUTTON_B;
		//* �w�{�^��
		if (dijs.rgbButtons[2] & 0x80)	State[i] |= BUTTON_X;
		//* �x�{�^��
		if (dijs.rgbButtons[3] & 0x80)	State[i] |= BUTTON_Y;
		//* LB�{�^��
		if (dijs.rgbButtons[4] & 0x80)	State[i] |= BUTTON_L;
		//* RB�{�^��
		if (dijs.rgbButtons[5] & 0x80)	State[i] |= BUTTON_R;
		//* BACK�{�^��
		if (dijs.rgbButtons[6] & 0x80)	State[i] |= BUTTON_BACK;
		//* START�{�^��
		if (dijs.rgbButtons[7] & 0x80)	State[i] |= BUTTON_START;
		//* ���X�e�B�b�N�{�^��
		if (dijs.rgbButtons[8] & 0x80)	State[i] |= BUTTON_LS;
		//* �E�X�e�B�b�N�{�^��
		if (dijs.rgbButtons[9] & 0x80)	State[i] |= BUTTON_RS;

		// Trigger�ݒ�
		StateTrigger[i] = ((lastPadState ^ State[i])	// �O��ƈ���Ă���
			& State[i]);					// ��������ON�̂��

		// Roll�ݒ�
//		padLsRoll[i] = D3DXVECTOR2(dijs.lX / (float)(RANGE_MAX), -(dijs.lY / (float)(RANGE_MAX)));
//		padRsRoll[i] = D3DXVECTOR2(dijs.lRx / (float)(RANGE_MAX), dijs.lRy / (float)(RANGE_MAX));
	}

	//PrintDebugProcess("l   : (%ld)(%ld)(%ld)\n", dijs.lX, dijs.lY, dijs.lZ);
	//PrintDebugProcess("lR  : (%ld)(%ld)(%ld)\n", dijs.lRx, dijs.lRy, dijs.lRz);
	//	PrintDebugProcess("rS  : (%ld)(%ld)\n", dijs.rglSlider[0], dijs.rglSlider[1]);
	//	PrintDebugProcess("�\���L�[ : (%ld)", dijs.rgdwPOV[0]);
	//	PrintDebugProcess("(%ld)", dijs.rgdwPOV[1]);
	//	PrintDebugProcess("(%ld)", dijs.rgdwPOV[2]);
	//	PrintDebugProcess("(%ld)\n", dijs.rgdwPOV[3]);
	//	PrintDebugProcess("lV  : (%ld)(%ld)(%ld)\n", dijs.lVX, dijs.lVY, dijs.lVZ);
	//	PrintDebugProcess("lVR : (%ld)(%ld)(%ld)\n", dijs.lVRx, dijs.lVRy, dijs.lVRz);
	//	PrintDebugProcess("rVS : (%ld)(%ld)\n", dijs.rglVSlider[0], dijs.rglVSlider[1]);
	//	PrintDebugProcess("lA  : (%ld)(%ld)(%ld)\n", dijs.lAX, dijs.lAY, dijs.lAZ);
	//	PrintDebugProcess("lAR : (%ld)(%ld)(%ld)\n", dijs.lARx, dijs.lARy, dijs.lARz);
	//	PrintDebugProcess("rAS : (%ld)(%ld)\n", dijs.rglASlider[0], dijs.rglASlider[1]);
	//	PrintDebugProcess("lF  : (%ld)(%ld)(%ld)\n", dijs.lFX, dijs.lFY, dijs.lFZ);
	//	PrintDebugProcess("lFR : (%ld)(%ld)(%ld)\n", dijs.lFRx, dijs.lFRy, dijs.lFRz);
	//	PrintDebugProcess("rFS : (%ld)(%ld)\n", dijs.rglFSlider[0], dijs.rglFSlider[1]);
	//	PrintDebugProcess("\n");
	return result;
}

//==== �Q�[���p�b�h�̏I������ ====//
void DirectInput::GamePad::Uninit(void)
{
	for (int i=0 ; i<GAMEPADMAX ; i++) {
		if ( DirectInputDevice[i] )
		{
			DirectInputDevice[i]->Unacquire();
			DirectInputDevice[i]->Release();
		}
	}

}

/*----�Q�[���p�b�h�̏����擾--------*/
//----�{�^���̉���--------
BOOL DirectInput::GamePad::Pressed(int padNo, DWORD button)
{
	return (button & State[padNo]);
}
BOOL DirectInput::GamePad::Trigger(int padNo, DWORD button)
{
	return (button & StateTrigger[padNo]);
}
//----���[���̉������ݗ�--------
Vector2 DirectInput::GamePad::LStickVolume(int padNo)
{
	return LsRoll[padNo];
}
Vector2 DirectInput::GamePad::RStickVolume(int padNo)
{
	return RsRoll[padNo];
}

