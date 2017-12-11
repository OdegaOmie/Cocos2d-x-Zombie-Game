#include "TestSprite.h"

using namespace cocos2d;


TestSprite::TestSprite( std::vector<AIUnit>& ref) : aiRef(ref)
{

};




TestSprite * TestSprite::create( AIUnit& ai, std::vector<AIUnit>& ref)
{
	TestSprite* pSprite = new TestSprite(ref);
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

void TestSprite::update(float dt)
{
	this->setPosition(compass->update(aiRef));
	
}


