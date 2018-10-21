//=============================================================================
//
// 入力処理 [input.h]
//
//=============================================================================
#ifndef __INPUT_INCLUDE_H__
#define __INPUT_INCLUDE_H__


#define DIRECTINPUT_VERSION (0x0800)	// 警告対策
#include "Vector.h"
#include <dinput.h>
#include <Windows.h>
#include <tchar.h>
#pragma comment (lib, "dinput8.lib")


//*****************************************************************************
// マクロ定義
//*****************************************************************************
// プログラム分けするときに使う
#define USE_KEYBOARD	// 宣言するとキーボードで操作可能になる
#define USE_MOUSE		// 宣言するとマウスで操作可能になる
#define USE_PAD			// 宣言するとパッドで操作可能になる

/* マウス表示状態 */
// 制御
#define MOUSE_SET_CENTER	SetCursorPos((int)LAST_GAME_SCREEN_CENTER_X, (int)LAST_GAME_SCREEN_CENTER_Y)

/* GamePad */
#define RANGE_VALUE (1000)	// 有効範囲（絶対値）

/* game pad情報 */
#define LSTICK_UP       0x00000001L	// 左スティック上(.IY<0)
#define LSTICK_DOWN     0x00000002L	// 左スティック下(.IY>0)
#define LSTICK_LEFT     0x00000004L	// 左スティック左(.IX<0)
#define LSTICK_RIGHT    0x00000008L	// 左スティック右(.IX>0)
#define TRIGGER_LEFT    0x00000010L	// 左トリガー(.IZ<0)
#define TRIGGER_RIGHT   0x00000020L	// 右トリガー(.IZ>0)
#define RSTICK_UP       0x00000100L	// 右スティック上(.IRy<0)
#define RSTICK_DOWN     0x00000200L	// 右スティック下(.IRy>0)
#define RSTICK_LEFT     0x00000400L	// 右スティック左(.IRx<0)
#define RSTICK_RIGHT    0x00000800L	// 右スティック右(.IRx>0)
#define POV_UP          0x00001000L	// 十字キー上(.rgdwPOV[0]==0)
#define POV_RIGHT       0x00002000L	// 十字キー右(.rgdwPOV[0]==9000)
#define POV_DOWN        0x00004000L	// 十字キー下(.rgdwPOV[0]==18000)
#define POV_LEFT        0x00008000L	// 十字キー左(.rgdwPOV[0]==27000)
#define BUTTON_A        0x00100000L	// Ａボタン(.rgbButtons[0]&0x80)
#define BUTTON_B        0x00200000L	// Ｂボタン(.rgbButtons[1]&0x80)
#define BUTTON_X        0x00400000L	// Ｘボタン(.rgbButtons[2]&0x80)
#define BUTTON_Y        0x00800000L	// Ｙボタン(.rgbButtons[3]&0x80)
#define BUTTON_L        0x01000000L	// LBボタン(.rgbButtons[4]&0x80)
#define BUTTON_R        0x02000000L	// RBボタン(.rgbButtons[5]&0x80)
#define BUTTON_BACK     0x04000000L	// BACKボタン(.rgbButtons[6]&0x80)
#define BUTTON_START    0x08000000L	// STARTボタン(.rgbButtons[7]&0x80)
#define BUTTON_LS       0x10000000L	// 左スティックボタン(.rgbButtons[8]&0x80)
#define BUTTON_RS       0x20000000L	// 右スティックボタン(.rgbButtons[9]&0x80)
#define GAMEPADMAX      4			// 同時に接続するジョイパッドの最大数をセット


//*****************************************************************************
// プロトタイプ宣言
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
BOOL IsMouseLeftPressed(void);      // 左クリックした状態
BOOL IsMouseLeftTriggered(void);    // 左クリックした瞬間
BOOL IsMouseLeftRepeat(void);       // 左クリックし続けた
BOOL IsMouseLeftRelease(void);      // 左を離した瞬間
BOOL IsMouseRightPressed(void);     // 右クリックした状態
BOOL IsMouseRightTriggered(void);   // 右クリックした瞬間
BOOL IsMouseRightRepeat(void);      // 右クリックし続けた
BOOL IsMouseRightRelease(void);     // 右を離した瞬間
BOOL IsMouseCenterPressed(void);    // 中クリックした状態
BOOL IsMouseCenterTriggered(void);  // 中クリックした瞬間
BOOL IsMouseCenterRepeat(void);     // 中クリックし続けた
BOOL IsMouseCenterRelease(void);    // 中を離した瞬間
long GetMouseX(void);               // マウスがX方向に動いた相対値
long GetMouseY(void);               // マウスがY方向に動いた相対値
long GetMouseZ(void);               // マウスホイールが動いた相対値
POINT GetScreenMouse(void);         // マウスのスクリーン座標
Vector2 GetLocalMouse(void);        // マウスのローカル座標

//---------------------------- game pad
BOOL IsButtonPressed(int padNo, DWORD button);
BOOL IsButtonTriggered(int padNo, DWORD button);
D3DXVECTOR2 GetLStickVolume(int padNo);
D3DXVECTOR2 GetRStickVolume(int padNo);

HRESULT InitializePad(void);			// パッド初期化

#endif