//=============================================================================
//
// 入力処理 [input.cpp]
//
//=============================================================================
#include "Input.h"
#include "Math.h"
#include "WindowClass.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_KEY_MAX		(256)


// game pad用設定値
#define DEADZONE		(1000)			// 各軸の10%を無効ゾーンとする
#define RANGE_MAX		 RANGE_VALUE	// 有効範囲の最大値
#define RANGE_MIN		-RANGE_VALUE	// 有効範囲の最小値 (*上より代用中)
#define RANGE_LIMIT		(1)				//* 有効範囲規定ON/OFF


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd);
void UninitKeyboard(void);
HRESULT UpdateKeyboard(void);

HRESULT InitializeMouse(HINSTANCE hInst, HWND hWindow); // マウスの初期化
void UninitMouse();						// マウスの終了処理
HRESULT UpdateMouse();					// マウスの更新処理

//HRESULT InitializePad(void);			// パッド初期化
//BOOL CALLBACK SearchPadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID);	// パッド検査コールバック
void UpdatePad(void);
void UninitPad(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//---------------------- キーボード (keyboard)
LPDIRECTINPUT8			g_pDInput = NULL;					// IDirectInput8インターフェースへのポインタ
LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard = NULL;			// IDirectInputDevice8インターフェースへのポインタ(キーボード)
BYTE					g_keyState[NUM_KEY_MAX];			// キーボードの状態を受け取るワーク
BYTE					g_keyStateTrigger[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
BYTE					g_keyStateRepeat[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
BYTE					g_keyStateRelease[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
int						g_keyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ

//-------------------------- マウス (mouse)
LPDIRECTINPUTDEVICE8 pMouse = NULL;	// mouse

DIMOUSESTATE2	mouseState;			// マウスのダイレクトな状態
DIMOUSESTATE2	mouseTrigger;		// 押された瞬間だけON
DIMOUSESTATE2	mouseRepeat;		// 押され続けたら
DIMOUSESTATE2	mouseRelease;		// 離れた瞬間
int				mouseRepeatCnt[8];	// マウスのリピートカウンタ

POINT			s_MouseCursor;		// マウスカーソルの絶対位置(スクリーン)の取得

//-------------------------- ゲームパッド (game pad)

LPDIRECTINPUTDEVICE8	pGamePad[GAMEPADMAX] = {NULL,NULL,NULL,NULL};// パッドデバイス

DWORD		padState[GAMEPADMAX];		// パッド情報（複数対応）
DWORD		padTrigger[GAMEPADMAX];
D3DXVECTOR2	padLsRoll[GAMEPADMAX];		// 左スティックの倒状態
D3DXVECTOR2	padRsRoll[GAMEPADMAX];		// 右スティックの倒状態
int			padCount = 0;					// 検出したパッドの数


//=============================================================================
// 入力処理の初期化
//=============================================================================
HRESULT InitInput(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	if(!g_pDInput)
	{
		// DirectInputオブジェクトの作成
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
									IID_IDirectInput8, (void**)&g_pDInput, NULL);
	}

	// キーボードの初期化
	InitKeyboard(hInst, hWnd);

 	// マウスの初期化
	InitializeMouse(hInst, hWnd);
	
	// パッドの初期化
	InitializePad();

	return S_OK;
}

//=============================================================================
// 入力処理の終了処理
//=============================================================================
void UninitInput(void)
{
	// キーボードの終了処理
	UninitKeyboard();

	// マウスの終了処理
	UninitMouse();

	// パッドの終了処理
	UninitPad();

	if(g_pDInput)
	{
		g_pDInput->Release();
		g_pDInput = NULL;
	}
}

//=============================================================================
// 入力処理の更新処理
//=============================================================================
void UpdateInput(void)
{
	// キーボードの更新
	UpdateKeyboard();
	
	// マウスの更新
	UpdateMouse();
	
	// パッドの更新
	UpdatePad();

}

//=============================================================================
// キーボードの初期化
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// デバイスオブジェクトを作成
	hr = g_pDInput->CreateDevice(GUID_SysKeyboard, &g_pDIDevKeyboard, NULL);
	if(FAILED(hr) || g_pDIDevKeyboard == NULL)
	{
		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return hr;
	}

	// データフォーマットを設定
	hr = g_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = g_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	g_pDIDevKeyboard->Acquire();

	return S_OK;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void UninitKeyboard(void)
{
	if(g_pDIDevKeyboard)
	{
		g_pDIDevKeyboard->Release();
		g_pDIDevKeyboard = NULL;
	}
}

//=============================================================================
// キーボードの更新
//=============================================================================
HRESULT UpdateKeyboard(void)
{
	HRESULT hr;
	BYTE keyStateOld[256];

	// 前回のデータを保存
	memcpy(keyStateOld, g_keyState, NUM_KEY_MAX);

	// デバイスからデータを取得
	hr = g_pDIDevKeyboard->GetDeviceState(sizeof(g_keyState), g_keyState);
	if(SUCCEEDED(hr))
	{
		for(int cnt = 0; cnt < NUM_KEY_MAX; cnt++)
		{
			g_keyStateTrigger[cnt] = (keyStateOld[cnt] ^ g_keyState[cnt]) & g_keyState[cnt];
			g_keyStateRelease[cnt] = (keyStateOld[cnt] ^ g_keyState[cnt]) & ~g_keyState[cnt];
			g_keyStateRepeat[cnt] = g_keyStateTrigger[cnt];

			if(g_keyState[cnt])
			{
				g_keyStateRepeatCnt[cnt]++;
				if(g_keyStateRepeatCnt[cnt] >= 20)
				{
					g_keyStateRepeat[cnt] = g_keyState[cnt];
				}
			}
			else
			{
				g_keyStateRepeatCnt[cnt] = 0;
				g_keyStateRepeat[cnt] = 0;
			}
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		g_pDIDevKeyboard->Acquire();
	}

	return S_OK;
}

//=============================================================================
// キーボードのプレス状態を取得
//=============================================================================
bool GetKeyboardPress(int key)
{
	return (g_keyState[key] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのトリガー状態を取得
//=============================================================================
bool GetKeyboardTrigger(int key)
{
	return (g_keyStateTrigger[key] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのリピート状態を取得
//=============================================================================
bool GetKeyboardRepeat(int key)
{
	return (g_keyStateRepeat[key] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのリリ－ス状態を取得
//=============================================================================
bool GetKeyboardRelease(int key)
{
	return (g_keyStateRelease[key] & 0x80) ? true : false;
}


//=============================================================================
// マウス関係の処理
//=============================================================================
// マウスの初期化
HRESULT InitializeMouse(HINSTANCE hInst,HWND hWindow)
{
	HRESULT result;
	// デバイス作成
	result = g_pDInput->CreateDevice(GUID_SysMouse,&pMouse,NULL);
	if(FAILED(result) || pMouse==NULL)
	{
		MessageBox(hWindow,"No mouse","Warning",MB_OK | MB_ICONWARNING);
		return result;
	}
	// データフォーマット設定
	result = pMouse->SetDataFormat(&c_dfDIMouse2);
	if(FAILED(result))
	{
		MessageBox(hWindow,"Can't setup mouse","Warning",MB_OK | MB_ICONWARNING);
		return result;
	}
	// 他のアプリと協調モードに設定
	result = pMouse->SetCooperativeLevel(hWindow, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
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

	result = pMouse->SetProperty(DIPROP_AXISMODE,&prop.diph);
	if(FAILED(result))
	{
		MessageBox(hWindow,"Mouse property error","Warning",MB_OK | MB_ICONWARNING);
		return result;	
	}
	
	// アクセス権を得る
	pMouse->Acquire();
	return result;
}
//---------------------------------------------------------
void UninitMouse()
{
	if(pMouse)
	{
		pMouse->Unacquire();
		pMouse->Release();
		pMouse = NULL;
	}

}
//-----------------------------------------------------------
HRESULT UpdateMouse()
{
	HRESULT result;

	// 前回の値保存
	DIMOUSESTATE2 lastMouseState = mouseState;
	// データ取得
	result = pMouse->GetDeviceState(sizeof(mouseState), &mouseState);
	if (SUCCEEDED(result))
	{
		mouseTrigger.lX = mouseState.lX;
		mouseTrigger.lY = mouseState.lY;
		mouseTrigger.lZ = mouseState.lZ;

		// マウスのボタン状態
		for (int i = 0; i < 8; i++)
		{
			mouseTrigger.rgbButtons[i] = (lastMouseState.rgbButtons[i] ^ mouseState.rgbButtons[i]) & 
				mouseState.rgbButtons[i];

			mouseRelease.rgbButtons[i] = (lastMouseState.rgbButtons[i] ^ mouseState.rgbButtons[i]) &
				~mouseState.rgbButtons[i];
			
			mouseRepeat.rgbButtons[i] = 0;
			if (mouseState.rgbButtons[i])
			{
				mouseRepeatCnt[i]++;
				if (mouseRepeatCnt[i] >= 20)
				{
					mouseRepeat.rgbButtons[i] = mouseState.rgbButtons[i];
				}
			}
			else
			{
				mouseRepeatCnt[i] = 0;
				mouseRepeat.rgbButtons[i] = 0;
			}

		}
	}
	else	// 取得失敗
	{
		// アクセス権を得てみる
		result = pMouse->Acquire();
	}

	//マウスの現在の座標を取得する
	GetCursorPos(&s_MouseCursor);

	return result;
}

//----------------------------------------------
// 左ボタンの状態
//----------------------------------------------
//----押下----
BOOL IsMouseLeftPressed(void)
{
	return (BOOL)(mouseState.rgbButtons[0] & 0x80);	// 押されたときに立つビットを検査
}
//----トリガー----
BOOL IsMouseLeftTriggered(void)
{
	return (BOOL)(mouseTrigger.rgbButtons[0] & 0x80);
}
//----リピート----
BOOL IsMouseLeftRepeat(void)
{
	return (BOOL)(mouseRepeat.rgbButtons[0] & 0x80);
}
//----リリース----
BOOL IsMouseLeftRelease(void)
{
	return (BOOL)(mouseRelease.rgbButtons[0] & 0x80);
}

//----------------------------------------------
// 右ボタンの状態
//----------------------------------------------
//----押下----
BOOL IsMouseRightPressed(void)
{
	return (BOOL)(mouseState.rgbButtons[1] & 0x80);
}
//----トリガー----
BOOL IsMouseRightTriggered(void)
{
	return (BOOL)(mouseTrigger.rgbButtons[1] & 0x80);
}
//----リピート----
BOOL IsMouseRightRepeat(void)
{
	return (BOOL)(mouseRepeat.rgbButtons[1] & 0x80);
}
//----リリース----
BOOL IsMouseRightRelease(void)
{
	return (BOOL)(mouseRelease.rgbButtons[1] & 0x80);
}
//----------------------------------------------
// 中ボタンの状態
//----------------------------------------------
//----押下----
BOOL IsMouseCenterPressed(void)
{
	return (BOOL)(mouseState.rgbButtons[2] & 0x80);
}
//----トリガー----
BOOL IsMouseCenterTriggered(void)
{
	return (BOOL)(mouseTrigger.rgbButtons[2] & 0x80);
}
//----リピート----
BOOL IsMouseCenterRepeat(void)
{
	return (BOOL)(mouseRepeat.rgbButtons[2] & 0x80);
}
//----リリース----
BOOL IsMouseCenterRelease(void)
{
	return (BOOL)(mouseRelease.rgbButtons[2] & 0x80);
}
//----------------------------------------------
// マウスのダイレクト情報
//----------------------------------------------
//------------------ (移動量)
long GetMouseX(void)
{
	return mouseState.lX;
}
long GetMouseY(void)
{
	return mouseState.lY;
}
long GetMouseZ(void)
{
	return mouseState.lZ;
}
//------------------ (座標)
POINT GetScreenMouse(void)
{
	return s_MouseCursor;
}
Vector2 GetLocalMouse(void)
{
	/* マウスのスクリーン（グローバル）座標 */
	X2<LONG> mousePoint = X2<LONG>(s_MouseCursor.x, s_MouseCursor.y);
	
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


//=============================================================================
// ゲームパッド関係の処理
//=============================================================================
//---------------------------------------- コールバック関数
BOOL CALLBACK SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID )
{
	HRESULT result;

	result = g_pDInput->CreateDevice(lpddi->guidInstance, &pGamePad[padCount++], NULL);
	return DIENUM_CONTINUE;	// 次のデバイスを列挙

}
//---------------------------------------- 初期化
HRESULT InitializePad(void)			// パッド初期化
{
	HRESULT		result;
	int			i;

	padCount = 0;
	// ジョイパッドを探す
	g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL,
		(LPDIENUMDEVICESCALLBACK)SearchGamePadCallback,
		NULL,
		DIEDFL_ATTACHEDONLY);
	// セットしたコールバック関数が、パッドを発見した数だけ呼ばれる。

	for (i = 0; i < padCount; i++) {
		// ジョイスティック用のデータ・フォーマットを設定
		result = pGamePad[i]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(result))
			return false; // データフォーマットの設定に失敗

		// モードを設定（フォアグラウンド＆非排他モード）
//		result = pGamePad[i]->SetCooperativeLevel(hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
//		if ( FAILED(result) )
//			return false; // モードの設定に失敗

#if RANGE_LIMIT
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
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y軸の範囲を設定
		diprg.diph.dwObj = DIJOFS_Y;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Z軸の範囲を設定
		diprg.diph.dwObj = DIJOFS_Z;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// X回転の範囲を設定
		diprg.diph.dwObj = DIJOFS_RX;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y回転の範囲を設定
		diprg.diph.dwObj = DIJOFS_RY;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
#endif // RANGE_LIMIT



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
		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Y軸の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_Y;
		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Z軸の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_Z;
		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//X回転の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_RX;
		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Y回転の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_RY;
		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

		//ジョイスティック入力制御開始
		pGamePad[i]->Acquire();
	}

	return true;

}
//------------------------------------------- 終了処理
void UninitPad(void)
{
	for (int i=0 ; i<GAMEPADMAX ; i++) {
		if ( pGamePad[i] )
		{
			pGamePad[i]->Unacquire();
			pGamePad[i]->Release();
		}
	}

}

//------------------------------------------ 更新
void UpdatePad(void)
{
	HRESULT			result;
	DIJOYSTATE2		dijs;
	int				i;

	for (i = 0; i < padCount; i++)
	{
		DWORD lastPadState;
		lastPadState = padState[i];
		padState[i] = 0x00000000l;	// 初期化

		result = pGamePad[i]->Poll();	// ジョイスティックにポールをかける
		if (FAILED(result)) {
			result = pGamePad[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = pGamePad[i]->Acquire();
		}

		result = pGamePad[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// デバイス状態を読み取る
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED) {
			result = pGamePad[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = pGamePad[i]->Acquire();
		}

		// ３２の各ビットに意味を持たせ、ボタン押下に応じてビットをオンにする
#if RANGE_LIMIT
		//* y-axis (Lforward)
		if (dijs.lY < 0)				padState[i] |= LSTICK_UP;
		//* y-axis (Lbackward)
		if (dijs.lY > 0)				padState[i] |= LSTICK_DOWN;
		//* x-axis (Lleft)
		if (dijs.lX < 0)				padState[i] |= LSTICK_LEFT;
		//* x-axis (Lright)
		if (dijs.lX > 0)				padState[i] |= LSTICK_RIGHT;
		//* z-axis (lefttrigger)
		if (dijs.lZ > 0)				padState[i] |= TRIGGER_LEFT;
		//* z-axis (righttrigger)
		if (dijs.lZ < 0)				padState[i] |= TRIGGER_RIGHT;
		//* y-axis (Rforward)
		if (dijs.lRy < 0)				padState[i] |= RSTICK_UP;
		//* y-axis (Rbackward)
		if (dijs.lRy > 0)				padState[i] |= RSTICK_DOWN;
		//* x-axis (Rleft)
		if (dijs.lRx < 0)				padState[i] |= RSTICK_LEFT;
		//* x-axis (Rright)
		if (dijs.lRx > 0)				padState[i] |= RSTICK_RIGHT;
#else
		//* y-axis (Lforward)
		if (dijs.lY < 0x7FFF)				padState[i] |= LSTICK_UP;
		//* y-axis (Lbackward)
		if (dijs.lY > 0x7FFF)				padState[i] |= LSTICK_DOWN;
		//* x-axis (Lleft)
		if (dijs.lX < 0x7FFF)				padState[i] |= LSTICK_LEFT;
		//* x-axis (Lright)
		if (dijs.lX > 0x7FFF)				padState[i] |= LSTICK_RIGHT;
		//* z-axis (lefttrigger)
		if (dijs.lZ > 0x7FFF)				padState[i] |= TRIGGER_LEFT;
		//* z-axis (righttrigger)
		if (dijs.lZ < 0x7FFF)				padState[i] |= TRIGGER_RIGHT;
		//* y-axis (Rforward)
		if (dijs.lRy < 0x7FFF)				padState[i] |= RSTICK_UP;
		//* y-axis (Rbackward)
		if (dijs.lRy > 0x7FFF)				padState[i] |= RSTICK_DOWN;
		//* x-axis (Rleft)
		if (dijs.lRx < 0x7FFF)				padState[i] |= RSTICK_LEFT;
		//* x-axis (Rright)
		if (dijs.lRx > 0x7FFF)				padState[i] |= RSTICK_RIGHT;
#endif // RANGE_LIMIT

		//* 十字キー上
		if (dijs.rgdwPOV[0] == 0)			padState[i] |= POV_UP;
		//* 十字キー右
		if (dijs.rgdwPOV[0] == 9000)		padState[i] |= POV_RIGHT;
		//* 十字キー下
		if (dijs.rgdwPOV[0] == 18000)		padState[i] |= POV_DOWN;
		//* 十字キー左
		if (dijs.rgdwPOV[0] == 27000)		padState[i] |= POV_LEFT;
		//* Ａボタン
		if (dijs.rgbButtons[0] & 0x80)		padState[i] |= BUTTON_A;
		//* Ｂボタン
		if (dijs.rgbButtons[1] & 0x80)		padState[i] |= BUTTON_B;
		//* Ｘボタン
		if (dijs.rgbButtons[2] & 0x80)		padState[i] |= BUTTON_X;
		//* Ｙボタン
		if (dijs.rgbButtons[3] & 0x80)		padState[i] |= BUTTON_Y;
		//* LBボタン
		if (dijs.rgbButtons[4] & 0x80)		padState[i] |= BUTTON_L;
		//* RBボタン
		if (dijs.rgbButtons[5] & 0x80)		padState[i] |= BUTTON_R;
		//* BACKボタン
		if (dijs.rgbButtons[6] & 0x80)		padState[i] |= BUTTON_BACK;
		//* STARTボタン
		if (dijs.rgbButtons[7] & 0x80)		padState[i] |= BUTTON_START;
		//* 左スティックボタン
		if (dijs.rgbButtons[8] & 0x80)		padState[i] |= BUTTON_LS;
		//* 右スティックボタン
		if (dijs.rgbButtons[9] & 0x80)		padState[i] |= BUTTON_RS;

		// Trigger設定
		padTrigger[i] = ((lastPadState ^ padState[i])	// 前回と違っていて
			& padState[i]);					// しかも今ONのやつ

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

}
//----------------------------------------------- 検査
BOOL IsButtonPressed(int padNo, DWORD button)
{
	return (button & padState[padNo]);
}

BOOL IsButtonTriggered(int padNo, DWORD button)
{
	return (button & padTrigger[padNo]);
}

D3DXVECTOR2 GetLStickVolume(int padNo)
{
	return padLsRoll[padNo];
}

D3DXVECTOR2 GetRStickVolume(int padNo)
{
	return padRsRoll[padNo];
}

