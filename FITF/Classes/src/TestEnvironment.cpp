#include "TestEnvironment.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* TestEnvironment::createScene()
{
    return TestEnvironment::create();
}

// on "init" you need to initialize your instance
bool TestEnvironment::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	hudLayer = new Layer();

	this->addChild(hudLayer, 0, 0);


    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(TestEnvironment::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
	hudLayer->addChild(menu, 1);


	gameLayer = new Layer();

	this->addChild(gameLayer, 1, 1);
	num_boid_test_units = 70;

	Vec2 screen_mid = Vec2(900 / 2, 720 / 2);

	int rx = 0;
	int ry = 0;
	/*
	I have decided to keep the compass objects as member variables of the scene
	this has the advantage of when a test sprite is destroyed it just has to delete it's pointers
	and not the AIUnit itself, which can all be neatly destroyed when the scene terminates
	also if we think about the update, if the test sprite owns the AIUnit each AIUnit has to be passed
	from test sprite to scene to test sprite, this way it'S just scene to test sprite
	*/


	for (int i = 0; i < num_boid_test_units; i++) 
	{
		rx = CCRANDOM_MINUS1_1() * 200.0f;
		ry = CCRANDOM_MINUS1_1() * 200.0f;
		AIUnits.push_back(AIUnit(Vec2(screen_mid.x + rx, screen_mid.y + ry)));
		boid_test_units.pushBack(TestSprite::create(AIUnits[i], AIUnits));
		gameLayer->addChild(boid_test_units.at(i), 0, i);
	}
	
	this->scheduleUpdate();
    
    return true;
}


void TestEnvironment::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void TestEnvironment::update(float dt)
{
	for (int i = 0; i < num_boid_test_units; i++)
	{
		boid_test_units.at(i)->update(dt);
	}
}
