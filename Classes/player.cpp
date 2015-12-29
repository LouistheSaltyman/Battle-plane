#include "player.h"

USING_NS_CC;


Player* Player::create(const std::string &filename)
{
	Player* player = new Player();
	if (player && player->initWithFile(filename))
	{
		
		return player;
	}
	else
	{
		CC_SAFE_DELETE(player);
		return NULL;
	}
}


