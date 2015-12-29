#ifndef _ENEMYPLANE2_
#define _ENEMYPLANE2_
#include "cocos2d.h"
USING_NS_CC;

class EnemyPlane2 : public Sprite
{
public:

	static __Array* enemyPlane2Array;
	static EnemyPlane2* create(const std::string &filename);
	int getLife();
	void lifedecreas();

private:
	int life = 2;
};



#endif //_ENEMYPLANE2_