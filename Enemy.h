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
	// �G�l�~�[�̂RD���W�擾�֐�
	_ObjectBase3D getCapacityEnemy_ObjectBaseEnemy()
	{

		return Capacity_Enemy.ObjectBase_Enemy;

	}

	//�G�l�~�[�̃f�[�^�̈ʒu�擾�֐�
	int getCapacityEnemy_NumberEnemy()
	{

		return Capacity_Enemy.Number_Enemy;

	}

	//�G�l�~�[��HP�擾�֐�
	int getCapacityEnemy_HpEnemy()
	{

		return Capacity_Enemy.HP_Enemy;

	}

	//�G�l�~�[�̈ʒu���W�ݒ�
	_ObjectBase3D setCapacityEnemy_ObjectBaseEnemy(_ObjectBase3D object3D)
	{

		Capacity_Enemy.ObjectBase_Enemy = object3D;
		return ;

	}

	//�G�l�~�[��HP�ݒ�
	int setCapacityEnemy_HpEnemy(int setHp)
	{
		Capacity_Enemy.HP_Enemy = setHp;
		return 0;
	}




};

