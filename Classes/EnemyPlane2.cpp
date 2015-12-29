#include "EnemyPlane2.h"
USING_NS_CC;


__Array* EnemyPlane2::enemyPlane2Array;

EnemyPlane2* EnemyPlane2::create(const std::string &filename)
{
	EnemyPlane2* plane = new EnemyPlane2();
	if (plane&&plane->initWithFile(filename))
	{

		enemyPlane2Array->addObject(plane);
		return plane;
	}
	else
	{
		CC_SAFE_DELETE(plane);
		return NULL;
	}
}

int EnemyPlane2::getLife()
{

	return life;

}
void EnemyPlane2::lifedecreas()
{
	life--;
}