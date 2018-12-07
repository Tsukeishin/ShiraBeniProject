/*===========================================================================*/
/*                                                                           */
/* DirectInput.cpp                                                           */
/*                                                                           */
/*===========================================================================*/
#include "DirectInput.h"
#include "Math.h"
#include "WindowClass.h"


// game pad用設定値
#define DEADZONE		(1000)		// 各軸の10%を無効ゾーンとする
#define RANGE_MAX		 RANGE_VALUE	// 有効範囲の最大値
#define RANGE_MIN		-RANGE_VALUE	// 有効範囲の最小値 (*上より代用中)


//----DirectInput8 Interface--------
LPDIRECTINPUT8  DirectInput::DirectInput8 = NULL;	// IDirectInput8インターフェースへのポインタ

//----キーボード (keyboard)--------
LPDIRECTINPUTDEVICE8 DirectInput::Keyboard::DirectInputDevice = NULL;		// キーボードの(IP)
BYTE                 DirectInput::Keyboard::State[NUM_KEY_MAX];				// キーボードの状態ワーク
BYTE                 DirectInput::Keyboard::StateTrigger[NUM_KEY_MAX];		// キーボードの状態ワーク
BYTE                 DirectInput::Keyboard::StateRepeat[NUM_KEY_MAX];		// キーボードの状態ワーク
BYTE                 DirectInput::Keyboard::StateRelease[NUM_KEY_MAX];		// キーボードの状態ワーク
int                  DirectInput::Keyboard::StateRepeatCnt[NUM_KEY_MAX];	// キーボードのRepeatCnt

//----マウス (mouse)--------
LPDIRECTINPUTDEVICE8 DirectInput::Mouse::DirectInputDevice = NULL;	// マウスのIP
DIMOUSESTATE2        DirectInput::Mouse::State;						// マウスのダイレクトな状態
DIMOUSESTATE2        DirectInput::Mouse::Trigger;					// 押された瞬間だけON
POINT                DirectInput::Mouse::Coordinate;				// マウスカーソルの絶対座標の取得

//----ゲームパッド (game pad)--------

LPDIRECTINPUTDEVICE8 DirectInput::GamePad::DirectInputDevice[GAMEPADMAX] = { NULL };// ゲームパッドのIP
DWORD                DirectInput::GamePad::State[GAMEPADMAX];			// パッド情報
DWORD                DirectInput::GamePad::StateTrigger[GAMEPADMAX];	// パッド情報
Vector2              DirectInput::GamePad::LsRoll[GAMEPADMAX];			// 左スティックの倒状態
Vector2              DirectInput::GamePad::RsRoll[GAMEPADMAX];			// 右スティックの倒状態
int                  DirectInput::GamePad::Count;						// 検出したパッドの数


/*================================================================*/
/* 入力処理の初期化 */
/*================================================================*/
HRESULT DirectInput::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	if(!DirectInput8)
	{
		// DirectInputオブジェクトの作成
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
									IID_IDirectInput8, (void**)&DirectInput8, NULL);
	}

	// キーボードの初期化
	DirectInput::Keyboard::Init(hInst, hWnd);

 	// マウスの初期化
	DirectInput::Mouse::Init(hInst, hWnd);
	
	// パッドの初期化
	DirectInput::GamePad::Init();

	return S_OK;
}

/*================================================================*/
/* 入力処理の更新処理 */
/*================================================================*/
HRESULT DirectInput::Update()
{
	// キーボードの更新
	DirectInput::Keyboard::Update();
	
	// マウスの更新
	DirectInput::Mouse::Update();
	
	// パッドの更新
	DirectInput::GamePad::Update();

	return S_OK;
}

/*================================================================*/
/* 入力処理の終了処理 */
/*================================================================*/
void DirectInput::Uninit()
{
	// キーボードの終了処理
	DirectInput::Keyboard::Uninit();

	// マウスの終了処理
	DirectInput::Mouse::Uninit();

	// パッドの終了処理
	DirectInput::GamePad::Uninit();

	if(DirectInput8)
	{
		DirectInput8->Release();
		DirectInput8 = NULL;
	}
}


/*================================================================*/
/* キーボード関係の処理 */
/*================================================================*/
//==== キーボードの初期化 ====//
HRESULT DirectInput::Keyboard::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// デバイスオブジェクトを作成
	hr = DirectInput8->CreateDevice(GUID_SysKeyboard, &DirectInputDevice, NULL);
	if(FAILED(hr) || DirectInputDevice == NULL)
	{
		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return hr;
	}

	// データフォーマットを設定
	hr = DirectInputDevice->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = DirectInputDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	DirectInputDevice->Acquire();

	return S_OK;
}

//==== キーボードの更新 ====//
HRESULT DirectInput::Keyboard::Update(void)
{
	HRESULT hr;
	BYTE keyStateOld[256];

	// 前回のデータを保存
	memcpy(keyStateOld, State, NUM_KEY_MAX);

	// デバイスからデータを取得
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
		// キーボードへのアクセス権を取得
		DirectInputDevice->Acquire();
	}

	return S_OK;
}

//==== キーボードの終了 ====//
void DirectInput::Keyboard::Uninit(void)
{
	if(DirectInputDevice)
	{
		DirectInputDevice->Release();
		DirectInputDevice = NULL;
	}
}

//----キーボードの情報を取得--------
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
/* マウス関係の処理 */
/*================================================================*/
//==== マウスの初期化 ====//
HRESULT DirectInput::Mouse::Init(HINSTANCE hInst,HWND hWindow)
{
	HRESULT result;
	// デバイス作成
	result = DirectInput8->CreateDevice(GUID_SysMouse,&DirectInputDevice,NULL);
	if(FAILED(result) || DirectInputDevice==NULL)
	{
		MessageBox(hWindow,"No mouse","Warning",MB_OK | MB_ICONWARNING);
		return result;
	}
	// データフォーマット設定
	result = DirectInputDevice->SetDataFormat(&c_dfDIMouse2);
	if(FAILED(result))
	{
		MessageBox(hWindow,"Can't setup mouse","Warning",MB_OK | MB_ICONWARNING);
		return result;
	}
	// 他のアプリと協調モードに設定
	result = DirectInputDevice->SetCooperativeLevel(hWindow, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(result))
	{
		MessageBox(hWindow,"Mouse mode error","Warning",MB_OK | MB_ICONWARNING);
		return result;
	}
	
	// デバイスの設定
	DIPROPDWORD prop;
	
	prop.diph.dwSize = sizeof(prop);
	prop.diph.dwHeaderSize = sizeof(prop.diph);
	prop.diph.dwObj = 0;
	prop.diph.dwHow = DIPH_DEVICE;
	prop.dwData = DIPROPAXISMODE_REL;		// マウスの移動値 相対値

	result = DirectInputDevice->SetProperty(DIPROP_AXISMODE,&prop.diph);
	if(FAILED(result))
	{
		MessageBox(hWindow,"Mouse property error","Warning",MB_OK | MB_ICONWARNING);
		return result;	
	}
	
	// アクセス権を得る
	DirectInputDevice->Acquire();
	return result;
}

//==== マウスの更新 ====//
HRESULT DirectInput::Mouse::Update()
{
	HRESULT result;

	// 前回の値保存
	DIMOUSESTATE2 lastMouseState = State;
	// データ取得
	result = DirectInputDevice->GetDeviceState(sizeof(State), &State);
	if (SUCCEEDED(result))
	{
		Trigger.lX = State.lX;
		Trigger.lY = State.lY;
		Trigger.lZ = State.lZ;
		// マウスのボタン状態
		for (int i = 0; i < 8; i++)
		{
			Trigger.rgbButtons[i] = ((lastMouseState.rgbButtons[i] ^
				State.rgbButtons[i]) & State.rgbButtons[i]);
		}
	}
	else	// 取得失敗
	{
		// アクセス権を得てみる
		result = DirectInputDevice->Acquire();
	}

	//マウスの現在の座標を取得する
	GetCursorPos(&Coordinate);

	return result;
}

//==== マウスの終了 ====//
void DirectInput::Mouse::Uninit()
{
	if(DirectInputDevice)
	{
		DirectInputDevice->Unacquire();
		DirectInputDevice->Release();
		DirectInputDevice = NULL;
	}

}

/*----マウスの情報を取得--------*/
//----クリック状態--------
BOOL DirectInput::Mouse::LPressed(void)
{
	return (BOOL)(State.rgbButtons[0] & 0x80);	// 押されたときに立つビットを検査
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
//----移動量--------
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
//----座標--------
POINT   DirectInput::Mouse::GlobalCoord(void)
{
	return Coordinate;
}
Vector2 DirectInput::Mouse::LocalCoord(void)
{
	/* マウスのスクリーン（グローバル）座標 */
	X2<LONG> mousePoint = X2<LONG>(Coordinate.x, Coordinate.y);

	/* ウィンドウの左上座標を取得 */
	RECT rect;
	GetWindowRect(WindowClass::GetHWnd(), &rect);
	X2<LONG> windowPoint = X2<LONG>(rect.left, rect.top);

	/* ウィンドウ枠部の差分を計算し、Windowの原点のスクリーン座標を求める */
	X2<LONG> windOrigin;
	windOrigin.x = windowPoint.x + (LONG)GetSystemMetrics(SM_CXDLGFRAME);
	windOrigin.y = windowPoint.y + (LONG)GetSystemMetrics(SM_CXDLGFRAME) + (LONG)GetSystemMetrics(SM_CYCAPTION);

	/* マウスのローカル座標を求める */
	X2<LONG> retCoord = mousePoint - windOrigin;

	return Vector2((float)retCoord.x, (float)retCoord.y);
}


/*================================================================*/
/* ゲームパッド関係の処理 */
/*================================================================*/
//==== コールバック関数 ====//
BOOL CALLBACK DirectInput::GamePad::Callback(LPDIDEVICEINSTANCE lpddi, LPVOID )
{
	HRESULT result;

	result = DirectInput8->CreateDevice(lpddi->guidInstance, &DirectInputDevice[Count++], NULL);
	return DIENUM_CONTINUE;	// 次のデバイスを列挙

}

//==== ゲームパッドの初期化 ====//
HRESULT DirectInput::GamePad::Init(void)			// パッド初期化
{
	HRESULT		result;
	int			i;

	Count = 0;
	// ジョイパッドを探す
	DirectInput8->EnumDevices(DI8DEVCLASS_GAMECTRL,
		(LPDIENUMDEVICESCALLBACK)DirectInput::GamePad::Callback,
		NULL,
		DIEDFL_ATTACHEDONLY);
	// セットしたコールバック関数が、パッドを発見した数だけ呼ばれる。

	for (i = 0; i < Count; i++) {
		// ジョイスティック用のデータ・フォーマットを設定
		result = DirectInputDevice[i]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(result))
			return false; // データフォーマットの設定に失敗

		// モードを設定（フォアグラウンド＆非排他モード）
//		result = DirectInputDevice[i]->SetCooperativeLevel(hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
//		if ( FAILED(result) )
//			return false; // モードの設定に失敗

		// 軸の値の範囲を設定
		// X軸、Y軸のそれぞれについて、オブジェクトが報告可能な値の範囲をセットする。
		// (max-min)は、最大10,000(?)。(max-min)/2が中央値になる。
		// 差を大きくすれば、アナログ値の細かな動きを捕らえられる。(パッドの性能による)
		DIPROPRANGE				diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = -RANGE_MAX; //* /=RANGE_MIN
		diprg.lMax = RANGE_MAX;
		// X軸の範囲を設定
		diprg.diph.dwObj = DIJOFS_X;
		DirectInputDevice[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y軸の範囲を設定
		diprg.diph.dwObj = DIJOFS_Y;
		DirectInputDevice[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Z軸の範囲を設定
		diprg.diph.dwObj = DIJOFS_Z;
		DirectInputDevice[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// X回転の範囲を設定
		diprg.diph.dwObj = DIJOFS_RX;
		DirectInputDevice[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y回転の範囲を設定
		diprg.diph.dwObj = DIJOFS_RY;
		DirectInputDevice[i]->SetProperty(DIPROP_RANGE, &diprg.diph);

		// 各軸ごとに、無効のゾーン値を設定する。
		// 無効ゾーンとは、中央からの微少なジョイスティックの動きを無視する範囲のこと。
		// 指定する値は、10000に対する相対値(2000なら20パーセント)。
		DIPROPDWORD				dipdw;
		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwHow = DIPH_BYOFFSET;
		dipdw.dwData = DEADZONE;
		//X軸の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_X;
		DirectInputDevice[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Y軸の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_Y;
		DirectInputDevice[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Z軸の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_Z;
		DirectInputDevice[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//X回転の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_RX;
		DirectInputDevice[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Y回転の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_RY;
		DirectInputDevice[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

		//ジョイスティック入力制御開始
		DirectInputDevice[i]->Acquire();
	}

	return true;

}

//==== ゲームパッドの更新 ====//
HRESULT DirectInput::GamePad::Update(void)
{
	HRESULT			result = S_OK;
	DIJOYSTATE2		dijs;
	int				i;

	for (i = 0; i < Count; i++)
	{
		DWORD lastPadState;
		lastPadState = State[i];
		State[i] = 0x00000000l;	// 初期化

		result = DirectInputDevice[i]->Poll();	// ジョイスティックにポールをかける
		if (FAILED(result)) {
			result = DirectInputDevice[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = DirectInputDevice[i]->Acquire();
		}

		result = DirectInputDevice[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// デバイス状態を読み取る
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED) {
			result = DirectInputDevice[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = DirectInputDevice[i]->Acquire();
		}

		// ３２の各ビットに意味を持たせ、ボタン押下に応じてビットをオンにする
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

		//* 十字キー上
		if (dijs.rgdwPOV[0] == 0)		State[i] |= POV_UP;
		//* 十字キー右
		if (dijs.rgdwPOV[0] == 9000)	State[i] |= POV_RIGHT;
		//* 十字キー下
		if (dijs.rgdwPOV[0] == 18000)	State[i] |= POV_DOWN;
		//* 十字キー左
		if (dijs.rgdwPOV[0] == 27000)	State[i] |= POV_LEFT;
		//* Ａボタン
		if (dijs.rgbButtons[0] & 0x80)	State[i] |= BUTTON_A;
		//* Ｂボタン
		if (dijs.rgbButtons[1] & 0x80)	State[i] |= BUTTON_B;
		//* Ｘボタン
		if (dijs.rgbButtons[2] & 0x80)	State[i] |= BUTTON_X;
		//* Ｙボタン
		if (dijs.rgbButtons[3] & 0x80)	State[i] |= BUTTON_Y;
		//* LBボタン
		if (dijs.rgbButtons[4] & 0x80)	State[i] |= BUTTON_L;
		//* RBボタン
		if (dijs.rgbButtons[5] & 0x80)	State[i] |= BUTTON_R;
		//* BACKボタン
		if (dijs.rgbButtons[6] & 0x80)	State[i] |= BUTTON_BACK;
		//* STARTボタン
		if (dijs.rgbButtons[7] & 0x80)	State[i] |= BUTTON_START;
		//* 左スティックボタン
		if (dijs.rgbButtons[8] & 0x80)	State[i] |= BUTTON_LS;
		//* 右スティックボタン
		if (dijs.rgbButtons[9] & 0x80)	State[i] |= BUTTON_RS;

		// Trigger設定
		StateTrigger[i] = ((lastPadState ^ State[i])	// 前回と違っていて
			& State[i]);					// しかも今ONのやつ

		// Roll設定
//		padLsRoll[i] = D3DXVECTOR2(dijs.lX / (float)(RANGE_MAX), -(dijs.lY / (float)(RANGE_MAX)));
//		padRsRoll[i] = D3DXVECTOR2(dijs.lRx / (float)(RANGE_MAX), dijs.lRy / (float)(RANGE_MAX));
	}

	//PrintDebugProcess("l   : (%ld)(%ld)(%ld)\n", dijs.lX, dijs.lY, dijs.lZ);
	//PrintDebugProcess("lR  : (%ld)(%ld)(%ld)\n", dijs.lRx, dijs.lRy, dijs.lRz);
	//	PrintDebugProcess("rS  : (%ld)(%ld)\n", dijs.rglSlider[0], dijs.rglSlider[1]);
	//	PrintDebugProcess("十字キー : (%ld)", dijs.rgdwPOV[0]);
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

//==== ゲームパッドの終了処理 ====//
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

/*----ゲームパッドの情報を取得--------*/
//----ボタンの押下--------
BOOL DirectInput::GamePad::Pressed(int padNo, DWORD button)
{
	return (button & State[padNo]);
}
BOOL DirectInput::GamePad::Trigger(int padNo, DWORD button)
{
	return (button & StateTrigger[padNo]);
}
//----ロールの押し込み量--------
Vector2 DirectInput::GamePad::LStickVolume(int padNo)
{
	return LsRoll[padNo];
}
Vector2 DirectInput::GamePad::RStickVolume(int padNo)
{
	return RsRoll[padNo];
}

