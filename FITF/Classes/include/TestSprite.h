#pragma once

#include "cocos2d.h"
#include <vector>
#include "AIUnit.h"

using namespace cocos2d;

class TestSprite : public cocos2d::Sprite
{
private:
	//Vec2 pos;
	AIUnit* compass;


public:

	TestSprite();

	static TestSprite * create(AIUnit& ai);

	void update(std::vector<AIUnit>&);


};