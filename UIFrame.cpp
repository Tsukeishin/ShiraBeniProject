#include "UIFrame.h"


C2DObject UIFrame::Frame;

int UIFrame::Init()
{
	Frame.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_CENTER_X, SCREEN_CENTER_Y);
	Frame.LoadTexture("data/���/�t���[��.png");

	return 0;
}

int UIFrame::Update()
{

	return 0;
}

void UIFrame::Draw()
{
	Frame.Draw();
}

void UIFrame::Uninit()
{
	Frame.Release();
}
