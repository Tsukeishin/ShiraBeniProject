/*===========================================================================*/
/*                                                                           */
/* DirectInput.h                                                             */
/*                                                                           */
/*===========================================================================*/
#ifndef __DIRECT_INPUT_H_INCLUDE__
#define __DIRECT_INPUT_H_INCLUDE__


#define DIRECTINPUT_VERSION (0x0800)	// 警告対策
#include "Vector.h"
#include <Windows.h>
#include <dinput.h>
#include <tchar.h>
#pragma comment (lib, "dinput8.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// プログラム分けするときに使う
#define USE_KEYBOARD	// 宣言するとキーボードで操作可能になる
#define USE_MOUSE		// 宣言するとマウスで操作可能になる
#define USE_PAD			// 宣言するとパッドで操作可能になる

/* キーボード */
#define	NUM_KEY_MAX (256)

/* マウス表示状態 */
// 制御
#define MOUSE_SET_CENTER	SetCursorPos((int)LAST_GAME_SCREEN_CENTER_X, (int)LAST_GAME_SCREEN_CENTER_Y)

/* GamePad */
#define RANGE_VALUE (1000)	// 有効範囲（絶対値）

/* game pad情報 */
#define LSTICK_UP		0x00000001l	// 左スティック上(.IY<0)
#define LSTICK_DOWN		0x00000002l	// 左スティック下(.IY>0)
#define LSTICK_LEFT		0x00000004l	// 左スティック左(.IX<0)
#define LSTICK_RIGHT	0x00000008l	// 左スティック右(.IX>0)
#define TRIGGER_LEFT	0x00000010l	// 左トリガー(.IZ<0)
#define TRIGGER_RIGHT	0x00000020l	// 右トリガー(.IZ>0)
#define RSTICK_UP		0x00000100l	// 右スティック上(.IRy<0)
#define RSTICK_DOWN		0x00000200l	// 右スティック下(.IRy>0)
#define RSTICK_LEFT		0x00000400l	// 右スティック左(.IRx<0)
#define RSTICK_RIGHT	0x00000800l	// 右スティック右(.IRx>0)
#define POV_UP			0x00001000l	// 十字キー上(.rgdwPOV[0]==0)
#define POV_RIGHT		0x00002000l	// 十字キー右(.rgdwPOV[0]==9000)
#define POV_DOWN		0x00004000l	// 十字キー下(.rgdwPOV[0]==18000)
#define POV_LEFT		0x00008000l	// 十字キー左(.rgdwPOV[0]==27000)
#define BUTTON_A		0x00100000l	// Ａボタン(.rgbButtons[0]&0x80)
#define BUTTON_B		0x00200000l	// Ｂボタン(.rgbButtons[1]&0x80)
#define BUTTON_X		0x00400000l	// Ｘボタン(.rgbButtons[2]&0x80)
#define BUTTON_Y		0x00800000l	// Ｙボタン(.rgbButtons[3]&0x80)
#define BUTTON_L		0x01000000l	// LBボタン(.rgbButtons[4]&0x80)
#define BUTTON_R		0x02000000l	// RBボタン(.rgbButtons[5]&0x80)
#define BUTTON_BACK		0x04000000l	// BACKボタン(.rgbButtons[6]&0x80)
#define BUTTON_START	0x08000000l	// STARTボタン(.rgbButtons[7]&0x80)
#define BUTTON_LS		0x10000000l	// 左スティックボタン(.rgbButtons[8]&0x80)
#define BUTTON_RS		0x20000000l	// 右スティックボタン(.rgbButtons[9]&0x80)
#define GAMEPADMAX		4			// 同時に接続するジョイパッドの最大数をセット


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
typedef class DirectInput
{
	static LPDIRECTINPUT8 DirectInput8;		// IDirectInput8インターフェースへのポインタ

public:
	static HRESULT Init(HINSTANCE hInst, HWND hWnd);
	static HRESULT Update();
	static void    Uninit();

	class Keyboard
	{
		static LPDIRECTINPUTDEVICE8 DirectInputDevice;		// キーボードのインターフェースへのポインタ(IP)
		static BYTE                 State[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
		static BYTE                 StateTrigger[NUM_KEY_MAX];	// キーボードの状態を受け取るワーク
		static BYTE                 StateRelease[NUM_KEY_MAX];	// キーボードの状態を受け取るワーク
		static BYTE                 StateRepeat[NUM_KEY_MAX];	// キーボードの状態を受け取るワーク
		static int                  StateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ

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
		static LPDIRECTINPUTDEVICE8 DirectInputDevice;	// キーボードのIP
		static DIMOUSESTATE2        State;				// マウスのダイレクトな状態
		static DIMOUSESTATE2        Trigger;			// 押された瞬間だけON
		static POINT                Coordinate;			// マウスカーソルの絶対位置(スクリーン)

	public:
		static HRESULT Init(HINSTANCE hInst, HWND hWnd);
		static HRESULT Update();
		static void    Uninit();

		static BOOL     LPressed(void);		// 左クリックした状態
		static BOOL     LTrigger(void);		// 左クリックした瞬間
		static BOOL     RPressed(void);		// 右クリックした状態
		static BOOL     RTrigger(void);		// 右クリックした瞬間
		static BOOL     CPressed(void);		// 中クリックした状態
		static BOOL     CTrigger(void);		// 中クリックした瞬間
		static long     MovementX(void);	// マウスがX方向に動いた相対値
		static long     MovementY(void);	// マウスがY方向に動いた相対値
		static long     MovementZ(void);	// マウスホイールが動いた相対値
		static POINT    GlobalCoord(void);	// マウスのグローバル座標
		static Vector2  LocalCoord(void);	// マウスのローカル座標

	};
	class GamePad
	{
		static LPDIRECTINPUTDEVICE8 DirectInputDevice[GAMEPADMAX];	// ゲームパッドのIP
		static DWORD                State[GAMEPADMAX];				// パッド情報（複数対応）
		static DWORD                StateTrigger[GAMEPADMAX];		// パッド情報（複数対応）
		static Vector2              LsRoll[GAMEPADMAX];				// 左スティックの倒状態
		static Vector2              RsRoll[GAMEPADMAX];				// 右スティックの倒状態
		static int                  Count;							// 検出したパッドの数

	public:
		static HRESULT Init();
		static BOOL CALLBACK Callback(LPDIDEVICEINSTANCE lpddi, LPVOID);	// パッド検査コールバック
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