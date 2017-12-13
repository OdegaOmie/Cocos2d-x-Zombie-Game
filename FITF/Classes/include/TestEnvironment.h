#ifndef __TEST_ENVIRONMENT_H__
#define __TEST_ENVIRONMENT_H__

#include "cocos2d.h"
#include <vector>
#include <random>
#include "TestSprite.h"
using namespace cocos2d;

class TestEnvironment : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void update(float dt) override;;




	Layer* gameLayer;
	Layer* hudLayer;

	std::vector<AIUnit> AIUnits;
	Vector<TestSprite*> boid_test_units;
	int num_boid_test_units;







    
    // implement the "static create()" method manually
    CREATE_FUNC(TestEnvironment);
};

#endif // __TestEnvironment_SCENE_H__
