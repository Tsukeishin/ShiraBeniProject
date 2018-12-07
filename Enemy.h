#pragma once

#include "Library/ObjectBase3D.h"

typedef struct Capacity_Enemy
{
	_ObjectBase3D ObjectBase_Enemy;
	int Number_Enemy;
	int HP_Enemy;


};

class Original_Enemy
{
private:

	Capacity_Enemy Capacity_Enemy;

public:
	// エネミーの３D座標取得関数
	_ObjectBase3D getCapacityEnemy_ObjectBaseEnemy()
	{

		return Capacity_Enemy.ObjectBase_Enemy;

	}

	//エネミーのデータの位置取得関数
	int getCapacityEnemy_NumberEnemy()
	{

		return Capacity_Enemy.Number_Enemy;

	}

	//エネミーのHP取得関数
	int getCapacityEnemy_HpEnemy()
	{

		return Capacity_Enemy.HP_Enemy;

	}

	//エネミーの位置座標設定
	_ObjectBase3D setCapacityEnemy_ObjectBaseEnemy(_ObjectBase3D object3D)
	{

		Capacity_Enemy.ObjectBase_Enemy = object3D;
		return ;

	}

	//エネミーのHP設定
	int setCapacityEnemy_HpEnemy(int setHp)
	{
		Capacity_Enemy.HP_Enemy = setHp;
		return 0;
	}




};

