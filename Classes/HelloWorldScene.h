#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);


	MenuItemSprite* pPauseItem;
	static Label* scorelabel;
	static int score;
	Sprite* bg_image1;
	Sprite* bg_image2;
	static Node* player;
	void update(float delta);
	void shootBullet(float alpha);
	void enemyPlane1Blowup(Node* plane);
	void enemyPlane2Blowup(Node* plane);
	void bulletMoveFinished(Node* psender);
	void addEnemyPlane1(float alpha);
	void addEnemyPlane2(float alpha);
	void addEnemyPlane3(float alpha);
	void spriteMoveFinished(Node* pSender);
	void spriteMoveFinished1(Node* pSender);
	void removeEnemyplane1(Node* Target);
	void removeEnemyplane2(Node* Target);
	void playerPlaneBlowup();
	void removePlayerPlane(Node* player);
	void pauseCallback(Ref* pSender);
	
};


#endif // __HELLOWORLD_SCENE_H__
