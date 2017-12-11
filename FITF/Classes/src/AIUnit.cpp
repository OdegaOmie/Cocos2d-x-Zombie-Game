#include "AIUnit.h"

using namespace cocos2d;


// Adds force Vec2 to current force Vec2
void AIUnit::applyForce(Vec2 force)
{
	acceleration += (force);
}

// Function that checks and modifies the distance
// of a AIUnit if it breaks the law of separation.
Vec2 AIUnit::Separation(Vector<AIUnit>& AIUnits)
{
	// If the AIUnit we're looking at is a predator, do not run the separation
	// algorithm

	// Distance of field of vision for separation between AIUnits
	float desiredseparation = 20;

	Vec2 steer(0, 0);
	int count = 0;
	
	// For every AIUnit in the system, check if it's too close
	for (int i = 0; i < AIUnits.size(); i++)
	{
		float d = location.distance(AIUnits.at(i).location);
		// If this is a fellow AIUnit and it's too close, move away from it
		if ((d > 0) && (d < desiredseparation))
		{
			Vec2 diff(0, 0);
			diff  = location -  AIUnits.at(i).location;
			diff.normalize();
			diff = diff / (d);      // Weight by distance
			steer += (diff);
			count++;
		}

	}
	// Adds average difference of location to acceleration
	if (count > 0)
		steer / ((float)count);
	if (steer.length() > 0)
	{
		// Steering = Desired - Velocity
		steer.normalize();
		steer *= (maxSpeed);
		steer -= (velocity);
		steer.clamp(Vec2::ZERO,Vec2( maxForce, maxForce));
	}
	return steer;
}


Vec2 AIUnit::Alignment(Vector<AIUnit>& AIUnits)
{
	float neighbordist = 50;

	Vec2 sum(0, 0);
	int count = 0;
	for (int i = 0; i < AIUnits.size(); i++)
	{
		float d = location.distance(AIUnits.at(i).location);
		if ((d > 0) && (d < neighbordist)) // 0 < d < 50
		{
			sum += AIUnits.at(i).velocity;
			count++;
		}
	}
	// If there are AIUnits close enough for alignment...
	if (count > 0)
	{
		sum = sum /((float)count);
		sum.normalize();	   		
		sum *= (maxSpeed);    
									
		Vec2 steer;
		steer = sum - velocity; 
		steer.clamp(Vec2::ZERO, Vec2(maxForce, maxForce));
		return steer;
	}
	else
		return Vec2::ZERO;
}

// Cohesion finds the average location of nearby AIUnits and manipulates the 
// steering force to move in that direction.
Vec2 AIUnit::Cohesion(Vector<AIUnit>& AIUnits)
{
	// If the AIUnit we're looking at is a predator, do not run the cohesion
	// algorithm
	//if (predator == true)
	//	return Vec2(0,0);

	float neighbordist = 50;

	Vec2 sum(0, 0);
	int count = 0;
	for (int i = 0; i < AIUnits.size(); i++)
	{
		float d = location.distance(AIUnits.at(i).location);
		if ((d > 0) && (d < neighbordist))
		{
			sum += (AIUnits.at(i).location);
			count++;
		}
	}
	if (count > 0)
	{
		sum = sum / (count);
		return seek(sum);
	}
	else
		return Vec2::ZERO;
}

// Seek function limits the maxSpeed, finds necessary steering force and
// normalizes the vectors.
Vec2 AIUnit::seek(Vec2 v)
{
	Vec2 desired = Vec2(0,0);
	desired -= (v);  // A vector pointing from the location to the target
						   // Normalize desired and scale to maximum speed
	desired.normalize();
	desired *= (maxSpeed);
	// Steering = Desired minus Velocity
	acceleration = desired - velocity;
	acceleration.clamp(Vec2::ZERO, Vec2(maxForce, maxForce));  // Limit to maximum steering force
	return acceleration;
}

//Update modifies velocity, location, and resets acceleration with values that
//are given by the three laws.
void AIUnit::update(Vector<AIUnit>& AIUnits)
{
	flock(AIUnits);
	//To make the slow down not as abrupt
	acceleration *= (0.4f);
	// Update velocity
	velocity += (acceleration);
	// Limit speed
	velocity.clamp(Vec2::ZERO, Vec2(maxForce, maxForce));
	location += (velocity);
	// Reset accelertion to 0 each cycle
	acceleration = Vec2::ZERO;
}



//Applies all three laws for the flock of AIUnits and modifies to keep them from
//breaking the laws.
void AIUnit::flock(Vector<AIUnit>& AIUnits)
{
	Vec2 sep = Separation(AIUnits);
	Vec2 ali = Alignment(AIUnits);
	Vec2 coh = Cohesion(AIUnits);
	// Arbitrarily weight these forces
	sep *= (1.5);
	ali *= (1.0); // Might need to alter weights for different characteristics
	coh *= (1.0);
	// Add the force vectors to acceleration
	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
}


// Calculates the angle for the velocity of a AIUnit which allows the visual 
// image to rotate in the direction that it is going in.
float AIUnit::angle(Vec2 v)
{
	// From the definition of the dot product
	float angle = (float)(atan2(v.x, -v.y) * 180 / PI);
	return angle;
}