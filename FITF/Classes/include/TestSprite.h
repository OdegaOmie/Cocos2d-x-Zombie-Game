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
	std::vector<AIUnit>& aiRef;

public:

	TestSprite(std::vector<AIUnit>&);

	static TestSprite * create(AIUnit& ai, std::vector<AIUnit>&);

	void update(float dt) override;


};