#ifndef __TEST_ENVIRONMENT_H__
#define __TEST_ENVIRONMENT_H__

#include "cocos2d.h"

class TestEnvironment : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestEnvironment);
};

#endif // __TestEnvironment_SCENE_H__
