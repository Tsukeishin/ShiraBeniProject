//=============================================================================
//
// 入力処理 [input.h]
//
//=============================================================================
#ifndef __INPUT_INCLUDE_H__
#define __INPUT_INCLUDE_H__

#include "LinkLibrary.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
// プログラム分けするときに使う
#define USE_KEYBOARD										// 宣言するとキーボードで操作可能になる
#define USE_MOUSE											// 宣言するとマウスで操作可能になる
#define USE_PAD												// 宣言するとパッドで操作可能になる

/* マウス表示状態 */
// 制御
#define MOUSE_STETUS_HIDE	ShowCursor(false)
#define MOUSE_STETUS_VIEW	ShowCursor(true)
#define MOUSE_SET_CENTER	SetCursorPos((int)LAST_GAME_SCREEN_CENTER_X, (int)LAST_GAME_SCREEN_CENTER_Y)

/* GamePad */
#define RANGE_VALUE (1000)	// 有効範囲（絶対値）

enum CURSORSTATUS
{
	CSR_HIDE,
	CSR_KEEPCENTER,
	CSR_FREE,
	CSR_MAX
};

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
BOOL IsMouseRightPressed(void);     // 右クリックした状態
BOOL IsMouseRightTriggered(void);   // 右クリックした瞬間
BOOL IsMouseCenterPressed(void);    // 中クリックした状態
BOOL IsMouseCenterTriggered(void);  // 中クリックした瞬間
long GetMouseX(void);               // マウスがX方向に動いた相対値
long GetMouseY(void);               // マウスがY方向に動いた相対値
long GetMouseZ(void);               // マウスホイールが動いた相対値
POINT GetMousePoint(void);          // マウスの座標
CURSORSTATUS SetMouseCursorStatus(CURSORSTATUS status); // マウスの表示状況

//---------------------------- game pad
BOOL IsButtonPressed(int padNo, DWORD button);
BOOL IsButtonTriggered(int padNo, DWORD button);
D3DXVECTOR2 GetLStickVolume(int padNo);
D3DXVECTOR2 GetRStickVolume(int padNo);

HRESULT InitializePad(void);			// パッド初期化

#endif