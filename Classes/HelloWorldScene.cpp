#include "HelloWorldScene.h"
#include "player.h"
#include "Bullet.h"
#include "EnemyPlane.h"
#include "EndScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;


Node* HelloWorld::player;
Label* HelloWorld::scorelabel;
int HelloWorld::score;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//爆炸效果导入
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation1/Explosion.plist", "animation1/Explosion.png");
	//创建敌机爆炸效果
	auto animation1 = Animation::create();
	animation1->setDelayPerUnit(0.05f);
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("1.png"));
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("2.png"));
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("3.png"));
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("4.png"));
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("5.png"));
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("6.png"));
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("7.png"));
	AnimationCache::getInstance()->addAnimation(animation1, "Explosion1");
	//创建主机爆炸效果
	auto animation2 = Animation::create();
	animation2->setDelayPerUnit(0.05f);
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("a1.png"));
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("a2.png"));
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("a3.png"));
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("a4.png"));
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("a5.png"));
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("a6.png"));
	AnimationCache::getInstance()->addAnimation(animation2, "Explosion2");

	//导入背景图片数据
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot_background.plist", "shoot_background.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist", "shoot.png");

	//提前导入背景音乐
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bg_music.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("bullet.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("enemy1_down.mp3");

	//敌机与子弹数组初始化
	Bullet::m_pAllBullet = __Array::create();
	Bullet::m_pAllBullet->retain();
	EnemyPlane::enemyPlaneArray = __Array::create();
	EnemyPlane::enemyPlaneArray->retain();
	


	/////////////////////////////
     /*2. add a menu item with "X" image, which is clicked to quit the program
        you may modify it.*/

     //add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
	//背景图片
	bg_image1 = Sprite::createWithSpriteFrameName("background.png");
   bg_image1->setScaleY(visibleSize.height / bg_image1->getContentSize().height);
   bg_image1->setScaleX(visibleSize.width / bg_image1->getContentSize().width);
   bg_image1->getTexture()->setAliasTexParameters();
   bg_image1->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2));

   bg_image2 = Sprite::createWithSpriteFrameName("background.png");
   bg_image2->setScaleY(visibleSize.height / bg_image1->getContentSize().height);
   bg_image2->setScaleX(visibleSize.width / bg_image2->getContentSize().width);
   bg_image2->getTexture()->setAliasTexParameters();
   bg_image2->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height *3/2 - 10));
    // add the sprite as a child to this layer
   this->addChild(bg_image1, 0);
   this->addChild(bg_image2, 0);

   //添加暂停按钮
   auto normalPause = Sprite::createWithSpriteFrameName("game_pause_nor.png");
   auto pressedPause = Sprite::createWithSpriteFrameName("game_pause_pressed.png");
   pPauseItem = MenuItemSprite::create(normalPause, pressedPause, CC_CALLBACK_1(HelloWorld::pauseCallback, this));
   pPauseItem->setPosition(Point(normalPause->getContentSize().width / 2 + 10, visibleSize.height - normalPause->getContentSize().height / 2 - 10));
   auto menuPause = Menu::create(pPauseItem, nullptr);
   menuPause->setPosition(Point::ZERO);
   this->addChild(menuPause, 101);

   //增添分数条
   scorelabel = Label::create(" 0", "fonts/arial.ttf", 25);
   scorelabel->setAnchorPoint(Vec2(0,1));
   scorelabel->setPosition(pPauseItem->getPositionX() + pPauseItem->getContentSize().width/2 + 10, visibleSize.height - 10);
   this->addChild(scorelabel);
   //初始分数为0
   score = 0;


   //增添主飞机
   player = Player::create("plane/PaperPlane1.png");
   player->setPosition(100, 100);
   this->addChild(player);
   //增加监听
   auto listener = EventListenerTouchOneByOne::create();
   listener->onTouchBegan = [=](Touch* touch, Event* event){
	   Point touchPoint = touch->getLocationInView();
	   touchPoint = Director::sharedDirector()->convertToGL(touchPoint);
	   //player->runAction(MoveTo::create(0.3,touchPoint));
	   player->setPosition(touchPoint);

	
	   return true;
   };

   listener->onTouchMoved = [=](Touch* touch, Event* event){

	   Point touchPoint = touch->getLocationInView();
	   touchPoint = Director::sharedDirector()->convertToGL(touchPoint);
	   player->setPosition(touchPoint);
   
   };
   _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);




  


   // 主飞机添加并发射子弹
   this->schedule(schedule_selector(HelloWorld::shootBullet),0.3);
  

   //增加敌机
   this->schedule(schedule_selector(HelloWorld::addEnemyPlane1), 1);
   this->schedule(schedule_selector(HelloWorld::addEnemyPlane2), 2);
   this->schedule(schedule_selector(HelloWorld::addEnemyPlane3), 4);
  


   //背景滚动以及碰撞检测
   this->scheduleUpdate();
   //播放背景音乐
   //CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bg_music.mp3", true);

  
   return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::update(float delta)
{
	//背景图片滚动
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto POX = bg_image1->getPositionY();
	POX = POX - 2;
	bg_image1->setPositionY(POX);

	auto POX2 = bg_image2->getPositionY();
	POX2 = POX2 - 2;
	bg_image2->setPositionY(POX2);
	if (POX2 == visibleSize.height/2)
	{
		bg_image1->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height * 3 / 2 -10));
	}
	if (POX == visibleSize.height/2)
	{
		bg_image2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 3 / 2 - 10));
	}
	//敌机1碰撞检测	
	Ref* a, *b;
	auto bulletstoDelete = __Array::create();
	bulletstoDelete->retain();
	CCARRAY_FOREACH(Bullet::m_pAllBullet, a)//子弹与敌机碰撞
	{
		
			auto bullet = (Sprite*) a;
			auto enemy1sToDelete = CCArray::create();
			enemy1sToDelete->retain();
			CCARRAY_FOREACH(EnemyPlane::enemyPlaneArray, b)
			{
				
				auto enemyPlane = (EnemyPlane*)b;
				if (enemyPlane->getBoundingBox().intersectsRect(bullet->getBoundingBox()))
				{
					int HP = enemyPlane->getLife();
					if (HP == 1)
					{
						enemy1sToDelete->addObject(enemyPlane);
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("enemy1_down.mp3");
						bulletstoDelete->addObject(bullet);
						enemyPlane->lifedecreas();
						score += 100;
						char strscore[20];
						sprintf(strscore, " %0d", score);
						scorelabel->setString(strscore);
					}
					else if (HP > 1)
					{
						bulletstoDelete->addObject(bullet);
						enemyPlane->lifedecreas();

					}
					
				
				}
				else;
				
			}
		
			CCARRAY_FOREACH(enemy1sToDelete, b)
			{
				auto enemyPlane = (EnemyPlane*)b;
				enemyPlane1Blowup(enemyPlane);
			}
			enemy1sToDelete->release();
		

	}
	CCARRAY_FOREACH(EnemyPlane::enemyPlaneArray, b)//敌机与主机碰撞
	{
		auto enemyPlane = (EnemyPlane*)b;
		auto enemy1sToDelete = CCArray::create();
		enemy1sToDelete->retain();
		if (enemyPlane->getBoundingBox().intersectsRect(player->getBoundingBox()))
		{
			enemy1sToDelete->addObject(enemyPlane);
			playerPlaneBlowup();
			CCLOG("The collision is happening");
		}
		else;
		CCARRAY_FOREACH(enemy1sToDelete, b)
		{
			auto enemyPlane = (EnemyPlane*)b;
			enemyPlane1Blowup(enemyPlane);
		}
		enemy1sToDelete->release();

	}
	CCARRAY_FOREACH(bulletstoDelete, a)
	{
		auto bullet = (Sprite*)a;
		bullet->stopAllActions();
		Bullet::removeBullet(bullet);

	}
	bulletstoDelete->removeAllObjects();

	
	
}



void HelloWorld::shootBullet(float alpha)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bullet.mp3");
	auto distance = Director::getInstance()->getVisibleSize().height - player->getPositionY();
	auto speed = 300;
	auto timeDuration = distance / speed;
	auto bullet = Bullet::create();
	bullet->setPosition(player->getPositionX(), player->getPositionY() + player->getContentSize().height / 2);
	this->addChild(bullet);
	auto MovetoAction = MoveTo::create(timeDuration, Vec2(bullet->getPositionX(), Director::getInstance()->getVisibleSize().height));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(HelloWorld::bulletMoveFinished, this));
	bullet->runAction(Sequence::create(MovetoAction,actionDone,NULL));
}

void HelloWorld::enemyPlane1Blowup(Node* plane)//敌机1爆炸效果，并移除敌机
{
	
	plane->stopAllActions();
	auto animation = AnimationCache::getInstance()->getAnimation("Explosion1");
	auto animate = Animate::create(animation);
	auto removeEnemyplane = CallFunc::create(CC_CALLBACK_0(HelloWorld::removeEnemyplane1, this, plane));
	auto sequence = Sequence::createWithTwoActions(animate, removeEnemyplane);
	plane->runAction(sequence);
	

}




void HelloWorld::bulletMoveFinished(Node* psender)//完成动作后释放子弹
{
	
	auto bullet = (Sprite*)psender;
	Bullet::m_pAllBullet->removeObject(bullet,true);
	bullet->removeFromParent();

}

void HelloWorld::addEnemyPlane1(float alpha)
{
	int x = rand() % 200 + 100;
	int y = Director::getInstance()->getVisibleSize().height;
	auto enemyPlane = EnemyPlane::create("plane/LiPlane2.png");
	enemyPlane->setPosition(Point(x, y));
	auto destination = Vec2(x, -this->getContentSize().height);
	auto Moveto = MoveTo::create(5, destination);
	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished, this));
	enemyPlane->runAction(Sequence::create(Moveto,actionMoveDone,NULL));
	this->addChild(enemyPlane);

}

void HelloWorld::addEnemyPlane2(float alpha)
{
	int x = rand() % 200 + 100;
	int y = Director::getInstance()->getVisibleSize().height;
	auto enemyPlane = EnemyPlane::create("plane/GodPlane2.png");
	enemyPlane->setPosition(Point(x, y));
	enemyPlane->setlife(2);
	auto destination = Vec2(x, -this->getContentSize().height);
	auto Moveto = MoveTo::create(3, destination);
	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished, this));
	this->addChild(enemyPlane);
	enemyPlane->runAction(Sequence::create(Moveto, actionMoveDone, NULL));
	

}
void HelloWorld::addEnemyPlane3(float alpha)
{
	int x = rand() % 200 + 100;
	int y = Director::getInstance()->getVisibleSize().height;
	auto enemyPlane = EnemyPlane::create("plane/JitPlane2.png");
	enemyPlane->setPosition(Point(x, y));
	enemyPlane->setlife(5);
	auto destination = Vec2(x, -this->getContentSize().height);
	auto Moveto = MoveTo::create(7, destination);
	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished, this));
	this->addChild(enemyPlane);
	enemyPlane->runAction(Sequence::create(Moveto, actionMoveDone, NULL));

}

void HelloWorld::spriteMoveFinished(Node* pSender)
{
	Sprite *Enemyplane = (Sprite *)pSender;
	
	EnemyPlane::enemyPlaneArray->removeObject(Enemyplane);
	Enemyplane->removeFromParent();
	CCLOG("EnemyPlane remove successfully");
}





void HelloWorld::removeEnemyplane1(Node* Target)
{
	
	auto plane = (EnemyPlane*)Target;
	plane->stopAllActions();
	plane->removeFromParent();
	EnemyPlane::enemyPlaneArray->fastRemoveObject(plane);
}



void HelloWorld::playerPlaneBlowup()
{
	auto animation = AnimationCache::getInstance()->getAnimation("Explosion2");
	auto animate = Animate::create(animation);
	auto callFun = CallFunc::create(CC_CALLBACK_0(HelloWorld::removePlayerPlane, this, player));
	auto sequence = Sequence::createWithTwoActions(animate, callFun);
	player->runAction(sequence);
}

void HelloWorld::removePlayerPlane(Node* player)
{
	
	player->removeFromParent();
	Director::sharedDirector()->replaceScene(EndScene::createScene());
}


void HelloWorld::pauseCallback(Ref* pSender)
{

	if (!CCDirector::getInstance()->isPaused())
	{
		pPauseItem->setNormalImage(Sprite::createWithSpriteFrameName("game_resume_nor.png"));
		pPauseItem->setSelectedImage(Sprite::createWithSpriteFrameName("game_resume_pressed.png"));
		Director::getInstance()->pause();
	}
	else
	{
		pPauseItem->setNormalImage(Sprite::createWithSpriteFrameName("game_pause_nor.png"));
		pPauseItem->setSelectedImage(Sprite::createWithSpriteFrameName("game_pause_pressed.png"));
		Director::getInstance()->resume();
		
	}
}


