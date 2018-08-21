//=============================================================================
//
// ローディング画面処理 <Loading.h>
//
//=============================================================================
#ifndef __LOADING_INCLUDE_H__
#define __LOADING_INCLUDE_H__


#include "LinkLibrary.h"
#include "ObjectBase2D.h"


class CNowLoading
{
public:
	UIBackGround     Back;
	C2DObject        Text;
	UI2DPercentGauge PercentGage;

	void Init(GAMESCENE scene);
	void Uninit(void);
	void Progress(int per);
};



#endif
