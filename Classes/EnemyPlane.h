#ifndef _ENEMTPLANE_
#define _ENEMYPLANE_
#include "cocos2d.h"
USING_NS_CC;

class EnemyPlane : public Sprite
{
public:
	
	static EnemyPlane* create(const std::string &filename);
	static __Array* enemyPlaneArray;
	int getLife();
	void lifedecreas();
	void setlife(int n);

private:
	int life = 1;
};



#endif //_ENEMYPLANE