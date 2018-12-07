#include "GameManager.h"
#include "Library/DirectInput.h"
#include "Library/Camera.h"
#include "Library/Dx9Line.h"
#include "Library/Dx9Font.h"
#include "Library/Math.h"
#include "Library/Matrix.h"
#include "Library/MultiRendering.h"
#include "UIFrame.h"

int  GameManager::Init()
{
	InitCamera();

	UIFrame::Init();

	return 0;
}

int  GameManager::Update()
{
	UpdateCamera();

	UIFrame::Update();

	return 0;
}

void GameManager::Draw()
{
	UIFrame::Draw();
}

void GameManager::Uninit()
{
	UIFrame::Uninit();
}



