//=============================================================================
//
// ƒJƒEƒ“ƒgˆ— <Counter.cpp>
//
//=============================================================================
#include "Counter.h"
#include "Common.h"


CountDown::CountDown()
{
	this->Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	this->Curve = 0.0f;
	this->Interval = 0;
	this->Counter = 0;
	this->Time = 0;
}

void CountDown::Set(int inter, int time, float posX, float posY, float sizX, float sizY, const char *texture)
{
	this->Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	this->Curve = 0.0f;
	this->Interval = inter;
	this->Counter = 0;
	this->Time = time;
	this->Init(posX, posY, sizX, sizY, texture);
	this->SetNumber(time);
}
void CountDown::Set(int inter, int time, float sizX, float sizY, const char *texture)
{
	this->Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	this->Curve = 0.0f;
	this->Interval = inter;
	this->Counter = 0;
	this->Time = time;
	this->Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, sizX, sizY, texture);
	this->SetNumber(time);
}
void CountDown::Set(int inter, int time, float sizX, float sizY)
{
	this->Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	this->Curve = 0.0f;
	this->Interval = inter;
	this->Counter = 0;
	this->Time = time;
	this->SetStatus(SCREEN_CENTER_X, SCREEN_CENTER_Y, sizX, sizY);
	this->SetNumber(time);
}

int CountDown::Count()
{
	this->Counter++;
	if (this->Counter >= this->Interval)
	{
		this->Counter = 0;
		this->Time--;
	}
	return this->Time;
}
bool CountDown::ActiveCheck()
{
	return this->Time ? true : false;
}

int CountDown::Animation()
{
	if (this->Count())
	{
		SetNumber(Time);
		return 0;
	}
	return 1;
}

