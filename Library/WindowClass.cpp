#include "WindowClass.h"
#include "Common.h"
#include "../resource.h"
#include <string.h>


HINSTANCE   WindowClass::Instance = NULL;
HWND        WindowClass::Handle = NULL;
MSG         WindowClass::Message;
LPCSTR      WindowClass::ClassName;
LPCSTR      WindowClass::WindowName;
bool        WindowClass::WindowMode = true;


//----Windowsの初期化処理--------
HRESULT WindowClass::Init(HINSTANCE hInstance, LPCSTR className, LPCSTR windowName)
{
	Instance = hInstance;
	ClassName = className;
	WindowName = windowName;

	// ウィンドウクラスを登録する
	WNDCLASSEX wcex = {};

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_CLASSDC;
	wcex.lpfnWndProc = WindowProcess;
	wcex.hInstance = Instance;
	wcex.lpszClassName = ClassName;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);
	wcex.hIcon = LoadIcon(Instance, MAKEINTRESOURCE(IDI_ICON1));

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);


	// ウィンドウオブジェクトを作成する.
	Handle = CreateWindowEx(
		0,														//拡張スタイル（任意）
		ClassName,												//クラス名
		WindowName,												//ウィンドウ名（タイトル）
		(WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU),			//スタイル
		((GetSystemMetrics(SM_CXSCREEN) - SCREEN_WIDTH)  / 2),	//横方向の位置
		((GetSystemMetrics(SM_CYSCREEN) - SCREEN_HEIGHT) / 2),	//縦方向の位置
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,									//幅
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	//高さ
		NULL,						//親ウィンドウ
		NULL,						//メニュー
		Instance,					//アプリケーションインスタンスのハンドル
		NULL						//ウィンドウ作成データ
	);

	if (Handle == NULL)
		return E_FAIL;

	//ウィンドウをスクリーンに表示する
	ShowWindow(Handle, SW_SHOW);
	UpdateWindow(Handle);

	return S_OK;
}

//----Windowsの終了処理--------
void WindowClass::Uninit(void)
{
	// ウィンドウのデストロイド
	//DestroyWindow(Handle);
	Handle = NULL;

	// ウィンドウクラスの登録を解除
	UnregisterClass(ClassName, Instance);
	Instance = NULL;
}

//----プロシージャ--------
LRESULT CALLBACK WindowClass::WindowProcess(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		if (true)
		{// 終了処理を実行
			DestroyWindow(hWnd);	// ウィンドウを破棄するよう指示する
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//----チェックメッセージ--------
int WindowClass::CheckMessage(void)
{
	if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
	{
		// PostQuitMessage()が呼ばれたらゲーム終了
		if (Message.message == WM_QUIT)
		{
			return 1;
		}
		// メッセージの翻訳とディスパッチ
		else
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return 0;

}

//----取得関数--------
HWND        WindowClass::GetHWnd(void)
{
	return Handle;
}
HINSTANCE   WindowClass::GetHInstance(void)
{
	return Instance;
}
bool        WindowClass::GetWindowMode(void)
{
	return WindowMode;
}

//----ウィンドウ設定--------
void WindowClass::SetWindowMode(bool mode)
{
	//if (!Direct3D::SetWindowMode(mode))
	//	return;

	if (mode)
	{
		//SetWindowLong(s_hWnd, GWL_STYLE, WS_CAPTION | WS_THICKFRAME | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU);
		SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	//else
	//{
	//	SetWindowLong(s_hWnd, GWL_STYLE, WS_POPUP | WS_EX_TOPMOST);
	//}


	//ShowWindow(s_hWnd, SW_SHOW);

	WindowMode = mode;
}
void WindowClass::SetWindowSize(int x, int y)
{
	SetWindowPos(Handle, NULL,
		/*(GetSystemMetrics(SM_CXSCREEN) - x) / 2*/0,
		/*(GetSystemMetrics(SM_CYSCREEN) - y) / 2*/0,
		x + GetSystemMetrics(SM_CXDLGFRAME) * 2,
		y + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
		SWP_NOZORDER | SWP_SHOWWINDOW);
}


RECT WindowClass::GetRect()
{
	RECT ret = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	return ret;
}

