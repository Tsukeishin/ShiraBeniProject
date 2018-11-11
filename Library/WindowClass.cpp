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


//----Windows�̏���������--------
HRESULT WindowClass::Init(HINSTANCE hInstance, LPCSTR className, LPCSTR windowName)
{
	Instance = hInstance;
	ClassName = className;
	WindowName = windowName;

	// �E�B���h�E�N���X��o�^����
	WNDCLASSEX wcex = {};

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_CLASSDC;
	wcex.lpfnWndProc = WindowProcess;
	wcex.hInstance = Instance;
	wcex.lpszClassName = ClassName;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);
	wcex.hIcon = LoadIcon(Instance, MAKEINTRESOURCE(IDI_ICON1));

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);


	// �E�B���h�E�I�u�W�F�N�g���쐬����.
	Handle = CreateWindowEx(
		0,														//�g���X�^�C���i�C�Ӂj
		ClassName,												//�N���X��
		WindowName,												//�E�B���h�E���i�^�C�g���j
		(WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU),			//�X�^�C��
		((GetSystemMetrics(SM_CXSCREEN) - SCREEN_WIDTH)  / 2),	//�������̈ʒu
		((GetSystemMetrics(SM_CYSCREEN) - SCREEN_HEIGHT) / 2),	//�c�����̈ʒu
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,									//��
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	//����
		NULL,						//�e�E�B���h�E
		NULL,						//���j���[
		Instance,					//�A�v���P�[�V�����C���X�^���X�̃n���h��
		NULL						//�E�B���h�E�쐬�f�[�^
	);

	if (Handle == NULL)
		return E_FAIL;

	//�E�B���h�E���X�N���[���ɕ\������
	ShowWindow(Handle, SW_SHOW);
	UpdateWindow(Handle);

	return S_OK;
}

//----Windows�̏I������--------
void WindowClass::Uninit(void)
{
	// �E�B���h�E�̃f�X�g���C�h
	//DestroyWindow(Handle);
	Handle = NULL;

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(ClassName, Instance);
	Instance = NULL;
}

//----�v���V�[�W��--------
LRESULT CALLBACK WindowClass::WindowProcess(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		if (true)
		{// �I�����������s
			DestroyWindow(hWnd);	// �E�B���h�E��j������悤�w������
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

//----�`�F�b�N���b�Z�[�W--------
int WindowClass::CheckMessage(void)
{
	if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
	{
		// PostQuitMessage()���Ă΂ꂽ��Q�[���I��
		if (Message.message == WM_QUIT)
		{
			return 1;
		}
		// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
		else
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return 0;

}

//----�擾�֐�--------
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

//----�E�B���h�E�ݒ�--------
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

