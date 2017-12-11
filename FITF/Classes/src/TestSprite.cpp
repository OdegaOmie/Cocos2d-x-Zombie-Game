#include "TestSprite.h"

using namespace cocos2d;


TestSprite::TestSprite() {

};




TestSprite * TestSprite::create( AIUnit& ai)
{
	TestSprite* pSprite = new TestSprite();
	if (pSprite->initWithFile("boid_test_img.png"))
	{
		pSprite->autorelease();

		pSprite->compass = new AIUnit(ai);

		pSprite->setPosition(ai.getPos());

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void TestSprite::update(std::vector<AIUnit>& AIUnits)
{
	this->setPosition(compass->update(AIUnits));
	
}


