#ifndef _GAME_H_INCLUDE_
#define _GAME_H_INCLUDE_


#include "Library/ObjectBase2D.h"
#include "Library/ObjectBase3D.h"


class GameManager
{

public:
	static int  Init();
	static int  Update();
	static void Draw();
	static void Uninit();
};

#endif // !_GAME_H_INCLUDE_
