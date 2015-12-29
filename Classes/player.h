#ifndef _PLAYER_
#define _PLAYER_

#include "cocos2d.h"
USING_NS_CC;

class Player : public Sprite
{
	
public:

	static Player* create(const std::string &filename);
	int HitPoint;


};



#endif // _PLAYER_