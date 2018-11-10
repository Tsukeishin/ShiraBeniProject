#include "Dx9ScreenShot.h"

#define _CRT_SECURE_NO_WARNINGS

#include "Direct3D.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <direct.h>
#include <Shlwapi.h> 
#pragma comment (lib, "shlwapi.lib")


int DxScreenShot(const char *path)
{
	// バックバファの取得
	LPDIRECT3DSURFACE9 pBuffer;
	Direct3D::GetD3DDevice()->GetRenderTarget(0, &pBuffer);

	// 現日付時刻の取得
	time_t now = time(NULL);
	struct tm *pnow = localtime(&now);

	char destName[256] = "";
	char fileName[64] = "";
	sprintf(fileName, "/Screenshot_%d%d%d_%d%d%d.bmp",
		pnow->tm_year + 1900, pnow->tm_mon + 1, pnow->tm_mday,
		pnow->tm_hour, pnow->tm_min, pnow->tm_sec);
	sprintf(destName, "%s%s", path, fileName);

	if (!PathIsDirectory(path))
		_mkdir(path);

	// スクショ出力
	D3DXSaveSurfaceToFile(destName, D3DXIFF_BMP, pBuffer, NULL, NULL);

	pBuffer->Release();

	return 0;
}
