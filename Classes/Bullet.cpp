#include "Bullet.h"
USING_NS_CC;


__Array* Bullet::m_pAllBullet;

Bullet::Bullet()
{
	

}

Bullet::~Bullet()
{
	

}



Sprite* Bullet::create()
{
	auto bullet = Sprite::create("bullet/nbullet_02.png");
	m_pAllBullet->addObject(bullet);
	return bullet;

}

void Bullet::removeBullet(Sprite* bullet)
{
	if (bullet)
	{
		bullet->removeFromParent();
		m_pAllBullet->fastRemoveObject(bullet);
	}

}

