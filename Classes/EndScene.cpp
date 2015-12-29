#include "EndScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;

Scene* EndScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = EndScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool EndScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	//添加背景图片
	auto bg_image1 = Sprite::createWithSpriteFrameName("background.png");
	bg_image1->setScaleY(visibleSize.height / bg_image1->getContentSize().height);
	bg_image1->setScaleX(visibleSize.width / bg_image1->getContentSize().width);
	bg_image1->getTexture()->setAliasTexParameters();
	bg_image1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg_image1);

	//添加gameover label
	auto label = Label::create("Game Over","fonts/Marker Felt.ttf",35);
	label->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(label);

	//显示分数
	char scorelabel[20];
	sprintf(scorelabel,"Your Score is %0d", HelloWorld::score);
	auto score = Label::create("","fonts/arial.ttf",30);
	score->setString(scorelabel);
	score->setPosition(label->getPosition().x, label->getPosition().y - label->getContentSize().height * 2);
	this->addChild(score);

	//添加重新开始按钮
	auto restart = MenuItemImage::create("button1.png",
		"button1.png",
		CC_CALLBACK_1(EndScene::menuCloseCallback, this));
	auto menu = Menu::create(restart, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	restart->setPosition(visibleSize.width/2,visibleSize.height/4);
	restart->setScale(2);

	auto restartLabel = Label::create("restart","fonts/Marker Felt.ttf",15);
	restartLabel->setPosition(restart->getPosition());
	restartLabel->setContentSize(restart->getContentSize());
	this->addChild(restartLabel,2);


	return true;


}

void EndScene::menuCloseCallback(Ref* pSender)
{

	Director::sharedDirector()->replaceScene(HelloWorld::createScene());

}