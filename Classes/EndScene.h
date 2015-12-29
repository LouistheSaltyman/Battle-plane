#ifndef _ENDSCENE_
#define _ENDSCENE_

#include "cocos2d.h"
USING_NS_CC;

class EndScene :public Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback


	// implement the "static create()" method manually
	CREATE_FUNC(EndScene);

	void menuCloseCallback(Ref* pSender);
};



#endif //_ENDSCENE