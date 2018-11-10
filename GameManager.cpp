#include "GameManager.h"
#include "Library/DirectInput.h"
#include "Library/Camera.h"
#include "Library/Dx9Line.h"
#include "Library/Dx9Font.h"
#include "Library/Math.h"
#include "Library/Matrix.h"
#include "Library/MultiRendering.h"


int  GameManager::Init()
{
	InitCamera();



	return 0;
}

int  GameManager::Update()
{
	UpdateCamera();

	return 0;
}

void GameManager::Draw()
{

}

void GameManager::Uninit()
{

}



