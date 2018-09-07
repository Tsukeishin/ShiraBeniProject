//=============================================================================
//
// デバッグ表示処理 [DebugProcess.cpp]
//
//=============================================================================
#include "DebugProcess.h"
#include "Common.h"
#include "Direct3D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXFONT Dx9DebugFont = NULL;			// フォントへのポインタ
char       DebugString[1024] = {"\0"};	// デバッグ情報


//=============================================================================
// デバッグ表示処理の初期化
//=============================================================================
HRESULT InitDebugProcess(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();
	HRESULT hr;

	// 情報表示用フォントを設定
	hr = D3DXCreateFont(pDevice,// 3Dデバイス
		18,						// フォントの高さ
		 0,						// フォントの横幅
		 0,						// フォントの太さ
		 0,						// ミニマップ数(1か0で十分)
		FALSE,					// イタリック
		SHIFTJIS_CHARSET,		// フォントタイプ
		OUT_DEFAULT_PRECIS,		// 「OUT_DEFAULT_PRECIS」固定っぽい
		DEFAULT_QUALITY,		// 実際フォントと目的フォントの一致方法を指定
		DEFAULT_PITCH,			// ぱっちあんどふぁみりー
		"Terminal",				// フォントデータ名
		&Dx9DebugFont);			// フォントデータ保管場所

	// 情報クリア
	memset(DebugString, 0, sizeof DebugString);

	return hr;
}

//=============================================================================
// デバッグ表示処理の終了処理
//=============================================================================
void UninitDebugProcess(void)
{
	if(Dx9DebugFont != NULL)
	{// 情報表示用フォントの開放
		Dx9DebugFont->Release();
		Dx9DebugFont = NULL;
	}
}

//=============================================================================
// デバッグ表示処理の更新処理
//=============================================================================
void UpdateDebugProcess(void)
{

}

//=============================================================================
// デバッグ表示処理の描画処理
//=============================================================================
void DrawDebugProcess(void)
{
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

	// 情報表示
	Dx9DebugFont->DrawText(NULL, DebugString, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xFF, 0x00, 0x00, 0x00));

	// 情報クリア
	memset(DebugString, 0, sizeof DebugString);
}

//=============================================================================
// デバッグ表示の登録
//=============================================================================
void PrintDebugProcess(const char *fmt,...)
{
#if 0
	long *pParam;
	static char aBuf[256];

	pParam = (long*)&fmt;
	sprintf(aBuf, fmt, pParam[1], pParam[2], pParam[3], pParam[4],
									pParam[5], pParam[6], pParam[7], pParam[8],
									pParam[9], pParam[10], pParam[11], pParam[12]);
#else
	va_list list;			// 可変引数を処理する為に使用する変数
	char *pCur;
	char aBuf[256]={"\0"};
	char aWk[32];

	// 可変引数にアクセスする前の初期処理
	va_start(list, fmt);

	pCur = (char*)fmt;
	for( ; *pCur; ++pCur)
	{
		if(*pCur != '%')
		{
			sprintf(aWk, "%c", *pCur);
		}
		else
		{
			pCur++;

			switch(*pCur)
			{
			case 'd':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%d", va_arg(list, int));
				break;

			case 'x':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%x", va_arg(list, int));
				break;

			case 'l':
				pCur++;

				if (*pCur == 'd')
				{
					// 可変引数にアクセスしてその変数を取り出す処理
					sprintf(aWk, "%ld", va_arg(list, long));

				}
				else
				{
					// 可変引数にアクセスしてその変数を取り出す処理
					sprintf(aWk, "%.3lf", va_arg(list, double));
				}
				break;

			case 'f':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%.2f", va_arg(list, double));		// double型で指定
				break;

			case 's':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%s", va_arg(list, char*));
				break;

			case 'c':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%c", va_arg(list, char));
				break;

			case 'v':
				{// 可変引数にアクセスしてその変数を取り出す処理
					D3DXVECTOR3 vec = va_arg(list, D3DXVECTOR3);
					sprintf(aWk, "%.2f, %.2f, %.2f", vec.x, vec.y, vec.z);
				}
				break;

			default:
				sprintf(aWk, "%c", *pCur);
				break;
			}
		}
		strcat(aBuf, aWk);
	}

	// 可変引数にアクセスした後の終了処理
	va_end(list);

	// 連結
	if((strlen(DebugString) + strlen(aBuf)) < sizeof DebugString - 1)
	{
		strcat(DebugString, aBuf);
	}
#endif
}

