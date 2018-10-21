#include "Dx9Font.h"
#include "WindowClass.h"
#include "Direct3D.h"
#include <stdio.h>


HRESULT Dx9Font::Create(INT height, UINT width, UINT weight, LPCSTR fontName)
{
	Format = DT_LEFT;
	Color = DX9COLOR_WHITE;
	// ���\���p�t�H���g��ݒ�
	return D3DXCreateFont(Direct3D::GetD3DDevice(),// 3D�f�o�C�X
		height,					// �t�H���g�̍���
		width,					// �t�H���g�̉���
		weight,					// �t�H���g�̑���
		0,						// �~�j�}�b�v��(1��0�ŏ\��)
		FALSE,					// �C�^���b�N
		SHIFTJIS_CHARSET,		// �t�H���g�^�C�v
		OUT_DEFAULT_PRECIS,		// �uOUT_DEFAULT_PRECIS�v�Œ���ۂ�
		DEFAULT_QUALITY,		// ���ۃt�H���g�ƖړI�t�H���g�̈�v���@���w��
		DEFAULT_PITCH,			// �ς�������ǂӂ��݂�[
		fontName,				// �t�H���g�f�[�^�� ("Terminal")
		&FontPointer);			// �t�H���g�f�[�^�ۊǏꏊ
}

void Dx9Font::Release(void)
{
	if(FontPointer != NULL)
	{
		FontPointer->Release();
		FontPointer = NULL;
	}
}

void Dx9Font::Draw(int x, int y, LPCSTR string)
{
	RECT rect = WindowClass::GetRect();
	rect.left += x;
	rect.top += y;
	// ���\��
	FontPointer->DrawText(NULL,
		string,
		-1,
		&rect,
		Format,
		Color);
}
void Dx9Font::Draw(int x, int y, LPCSTR string, D3DCOLOR color)
{
	RECT rect = WindowClass::GetRect();
	rect.left += x;
	rect.top += y;
	// ���\��
	FontPointer->DrawText(NULL,
		string,
		-1,
		&rect,
		Format,
		color);
}

//=============================================================================
// �f�o�b�O�\���̓o�^
//=============================================================================
//void PrintDebugProcess(const char *fmt,...)
//{
//#if 0
//	long *pParam;
//	static char aBuf[256];
//
//	pParam = (long*)&fmt;
//	sprintf(aBuf, fmt, pParam[1], pParam[2], pParam[3], pParam[4],
//									pParam[5], pParam[6], pParam[7], pParam[8],
//									pParam[9], pParam[10], pParam[11], pParam[12]);
//#else
//	va_list list;			// �ψ�������������ׂɎg�p����ϐ�
//	char *pCur;
//	char aBuf[256]={"\0"};
//	char aWk[32];
//
//	// �ψ����ɃA�N�Z�X����O�̏�������
//	va_start(list, fmt);
//
//	pCur = (char*)fmt;
//	for( ; *pCur; ++pCur)
//	{
//		if(*pCur != '%')
//		{
//			sprintf(aWk, "%c", *pCur);
//		}
//		else
//		{
//			pCur++;
//
//			switch(*pCur)
//			{
//			case 'd':
//				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
//				sprintf(aWk, "%d", va_arg(list, int));
//				break;
//
//			case 'x':
//				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
//				sprintf(aWk, "%x", va_arg(list, int));
//				break;
//
//			case 'l':
//				pCur++;
//
//				if (*pCur == 'd')
//				{
//					// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
//					sprintf(aWk, "%ld", va_arg(list, long));
//
//				}
//				else
//				{
//					// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
//					sprintf(aWk, "%.3lf", va_arg(list, double));
//				}
//				break;
//
//			case 'f':
//				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
//				sprintf(aWk, "%.2f", va_arg(list, double));		// double�^�Ŏw��
//				break;
//
//			case 's':
//				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
//				sprintf(aWk, "%s", va_arg(list, char*));
//				break;
//
//			case 'c':
//				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
//				sprintf(aWk, "%c", va_arg(list, char));
//				break;
//
//			case 'v':
//				{// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
//					D3DXVECTOR3 vec = va_arg(list, D3DXVECTOR3);
//					sprintf(aWk, "%.2f, %.2f, %.2f", vec.x, vec.y, vec.z);
//				}
//				break;
//
//			default:
//				sprintf(aWk, "%c", *pCur);
//				break;
//			}
//		}
//		strcat(aBuf, aWk);
//	}
//
//	// �ψ����ɃA�N�Z�X������̏I������
//	va_end(list);
//
//	// �A��
//	if((strlen(DebugString) + strlen(aBuf)) < sizeof DebugString - 1)
//	{
//		strcat(DebugString, aBuf);
//	}
//#endif
//}

