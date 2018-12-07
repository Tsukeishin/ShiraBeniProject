#ifndef _UI_UIFRAME_H_INCLUDE_
#define _UI_UIFRAME_H_INCLUDE_

#include "Library/Common.h"
#include "Library/ObjectBase2D.h"


#define UIFRAME_FIELD_LEFT   (LONG)( (  3.0F / 16.0F ) * SCREEN_WIDTH )
#define UIFRAME_FIELD_TOP    (LONG)( (  1.0F / 36.0F ) * SCREEN_HEIGHT )
#define UIFRAME_FIELD_RIGHT  (LONG)( ( 13.0F / 16.0F ) * SCREEN_WIDTH )
#define UIFRAME_FIELD_BOTTOM (LONG)( ( 34.0F / 36.0F ) * SCREEN_HEIGHT )

constexpr RECT GameFieldRect = { UIFRAME_FIELD_LEFT, UIFRAME_FIELD_TOP, UIFRAME_FIELD_RIGHT, UIFRAME_FIELD_BOTTOM };

class UIFrame
{
	static C2DObject Frame;

public:
	static int  Init();
	static int  Update();
	static void Draw();
	static void Uninit();

};

#endif // !_UI_UIFRAME_H_INCLUDE_
