#ifndef _BULLET_
#define _BULLET_
#include "cocos2d.h"
USING_NS_CC;
class Bullet : public Sprite
{
public:
	Bullet();
	~Bullet();
	
	static Sprite* create();
	static __Array* m_pAllBullet;
	static void removeBullet(Sprite* bullet);
};







#endif //_BULLET