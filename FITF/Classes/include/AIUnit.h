#pragma once

#include "cocos2d.h"
#include <vector>

using namespace cocos2d;

/*
The AIUnit is a compass class within each AI entity. It provides the core of
the AI logic, the three laws. Any game entity i.e zombie, will have one of these
objects as a class variable this seperates the animation logic and storage from
the AI. By compass class I mean that at all times the owners screen co-ordinates
will be dictated by the return value of the AIUnits update function.
*/
#define PI 3.141592635

class AIUnit
{
private:

	
	void applyForce(Vec2 force);
	float angle(Vec2 v);


	// Three Laws that boids follow
	Vec2 Separation(std::vector<AIUnit>&);
	Vec2 Alignment(std::vector<AIUnit>&);
	Vec2 Cohesion(std::vector<AIUnit>&);

	Vec2 location;
	Vec2 velocity;
	Vec2 acceleration;

	float maxSpeed;
	float maxForce;

	void limit(Vec2& v, float l);


	Vec2 seek(Vec2 v);

	void flock(std::vector<AIUnit>&);

public:
	AIUnit(Vec2 pos);

	Vec2& update(std::vector<AIUnit>&);

	Vec2 getPos() {
		return location;
	};

};