//=============================================================================
//
// カウント処理 <Counter.h>
//
//=============================================================================
#ifndef __COUNTER_H_INCLUDE__
#define __COUNTER_H_INCLUDE__


#include "ObjectBase2D.h"


class CountDown : public UI2DNumber
{
	UIBackGround Back;		// ブラックバック
	D3DXCOLOR    Color;		// カラー
	float        Curve;		// アニメーション用
	int          Interval;	// 表示間隔
	int          Counter;	// 内部カウンター
	int          Time;		// 表示時間

public:
	CountDown();

	void Set(int inter, int time, float posX, float posY, float sizX, float sizY, const char *texture);
	void Set(int inter, int time, float sizX, float sizY, const char *texture);
	void Set(int inter, int time, float sizX, float sizY);
	int  Count();
	bool ActiveCheck();

	int Animation();

private:

};




#endif
