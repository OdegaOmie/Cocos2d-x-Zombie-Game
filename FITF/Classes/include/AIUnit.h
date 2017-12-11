#pragma once

#include "cocos2d.h"

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
	Vec2 Separation(Vector<AIUnit>&);
	Vec2 Alignment(Vector<AIUnit>&);
	Vec2 Cohesion(Vector<AIUnit>&);

	Vec2 location;
	Vec2 velocity;
	Vec2 acceleration;

	float maxSpeed;
	float maxForce;


	Vec2 seek(Vec2 v);

	void flock(Vector<AIUnit>&);

	void swarm(Vector<AIUnit>&);

public:
	AIUnit(Vec2 pos);

	void update(Vector<AIUnit>&);



};