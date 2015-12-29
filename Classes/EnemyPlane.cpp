#include "EnemyPlane.h"
#include "Bullet.h"
USING_NS_CC;

__Array* EnemyPlane::enemyPlaneArray;

EnemyPlane* EnemyPlane::create(const std::string &filename)
{
	EnemyPlane* plane = new EnemyPlane();
	if (plane&&plane->initWithFile(filename))
	{
		
		enemyPlaneArray->addObject(plane);
		return plane;
	}
	else
	{
		CC_SAFE_DELETE(plane);
		return NULL;
	}
}

int EnemyPlane::getLife()
{
	
	return life;

}
void EnemyPlane::lifedecreas()
{
	life --;
}

void EnemyPlane::setlife(int n)
{

	life = n;

}


