#include "BehaviourStates.h"
#include "rules.h"
#include "staticmap.h"
#include "Renderer.h"


BehaviourStates::BehaviourStates()
{
	// SET DEFAULT VALUES
	// Initialising variables
	isEvading = false;
	isFleeing = false;
	isPursuing = false;
	isArriving = false;
	isSeeking = false;

	isAvoidWalls = false;
	isNavigating = false;

	botTarget = -1;
	domTarget = -1;

	pCurrentState = nullptr;
	pPrevState = nullptr;
}

void BehaviourStates::setBehaviour(e_Behaviours behaviour)
{
	// Alters behaviour based on given Enum
	// Activates / Deactives with switch below

	switch (behaviour)
	{
	case ACTIVATE_ARRIVE:
		isArriving = true;
		break;

	case ACTIVATE_AVOIDWALLS:
		isAvoidWalls = true;
		break;

	case ACTIVATE_EVADE:
		isEvading = true;
		break;

	case ACTIVATE_FLEE:
		isFleeing = true;
		break;

	case ACTIVATE_NAVIGATION:
		isNavigating = true;
		break;

	case ACTIVATE_PURSUE:
		isPursuing = true;
		break;

	case ACTIVATE_SEEK:
		isSeeking = true;
		break;

	case DEACTIVATE_ARRIVE:
		isArriving = false;
		break;

	case DEACTIVATE_AVOIDWALLS:
		isAvoidWalls = false;
		break;

	case DEACTIVATE_EVADE:
		isEvading = false;
		break;

	case DEACTIVATE_FLEE:
		isFleeing = false;
		break;

	case DEACTIVATE_NAVIGATION:
		isNavigating = false;
		break;

	case DEACTIVATE_PURSUE:
		isPursuing = false;
		break;

	case DEACTIVATE_SEEK:
		isSeeking = false;
		break;
	}
}


void BehaviourStates::turnOffAll()
{
	// Turns off all behaviours

	bool isSeeking = false;
	bool isPursuing = false;
	bool isEvading = false;
	bool isFleeing = false;
	bool isAvoidWalls = false;
	bool isNavigating = false;
	bool isArriving = false;
}


void BehaviourStates::setPath(std::vector<Vector2D>* newPath)
{
	m_path = *newPath;
}


std::vector<Vector2D>* BehaviourStates::getPath()
{
	return &m_path;
}

// Returns a Vector2D that sets a velocity towards a target
Vector2D BehaviourStates::Seek(Vector2D target, Vector2D botPos, Vector2D botVelocity)
{
	// Velocity calculation
	Vector2D newVelocity = (target - botPos).unitVector() * MAXIMUMSPEED;

	return (newVelocity - botVelocity).unitVector() * MAXIMUMACCELERATION;
}


// Returns a Vector2D lowers as the bot approaches its destination
Vector2D BehaviourStates::Arrive(Vector2D target, Vector2D botPos, Vector2D botVelocity)
{
	// Get distance from the target
	float distance = (target - botPos).magnitude();
	// Calculate speed from distance
	float speed = distance / 5;

	// Enforce speed
	if (speed > MAXIMUMSPEED)
	{
		speed = MAXIMUMSPEED;
	}

	Vector2D desiredVelocity = (target - botPos).unitVector() * speed;

	return desiredVelocity - botVelocity;
}

// Returns a Vector2D that pursues a moving target using their position and velocity
// to find an intersection.
Vector2D BehaviourStates::Pursue(Vector2D target, Vector2D targetVelocity, 
	Vector2D botPos, Vector2D botVelocity)
{
	float distance = (target - botPos).magnitude();
	float time = distance / MAXIMUMSPEED;
	target += targetVelocity * time;

	return Seek(target, botPos, botVelocity);
}


// Avoid walls
Vector2D BehaviourStates::AvoidWall(Vector2D position, Vector2D velocity)
{
	// Base circle for placement
	Vector2D circle = velocity.unitVector() * 50;

	// Varying radius
	Circle2D bigCircle(position + circle, 50);
	Circle2D littleCircle(position + circle, 30);

	Vector2D newVelocity = Vector2D(0, 0);

	//If there is a block inside the circles give velocity in the oposite direction
	if (StaticMap::GetInstance()->IsInsideBlock(bigCircle))
	{
		newVelocity = StaticMap::GetInstance()->GetNormalToSurface(bigCircle);

		if (StaticMap::GetInstance()->IsInsideBlock(littleCircle))
		{
			newVelocity *= 1150;
		}
		else
		{
			newVelocity *= 5000;
		}
	}

	return newVelocity;
}

// Runs seek on the next Node. Nodes will be skipped if the next one is visible
Vector2D BehaviourStates::Navigate(std::vector<Vector2D>* t_Path, Vector2D position, 
	Vector2D velocity)
{
	// Target node
	Vector2D target;

	// Is there is a path to follow?
	if (!t_Path->empty())
	{
		// Sets target node
		target = t_Path->back();
		// Multiple Nodes require additional checking to speed the process
		if (t_Path->size() > 1)
		{
			// If there are two nodes ahead skip one
			if (StaticMap::GetInstance()->IsLineOfSight(position, (*t_Path)[t_Path->size() - 2]))
			{
				target = (*t_Path)[t_Path->size() - 2];
				t_Path->pop_back();
			}
		}

		// Checks if bot has arrived at target
		Circle2D arrived(position, 40);
		if (arrived.Intersects(Point2D(target)))
		{
			if (t_Path->size() > 0)
			{
				t_Path->pop_back();
				if (t_Path->size() > 0)
				{
					target = t_Path->back();

				}
			}
		}
	}

	return Seek(target, position, velocity);
}

// Accumulates all the velocities
Vector2D BehaviourStates::AccumulateVectors(Vector2D position, Vector2D velocity, 
	Vector2D botPos, Vector2D botVelocity, std::vector<Vector2D>* t_Path)
{
	Vector2D acc;

	if (isSeeking)
	{
		acc += Seek(position, botPos, botVelocity);
	}

	if (isArriving)
	{
		acc += Arrive(position, botPos, botVelocity);
	}

	if (isPursuing)
	{
		acc += Pursue(position, velocity, botPos, botVelocity);
	}

	if (isAvoidWalls)
	{
		acc += AvoidWall(botPos, botVelocity);
	}

	if (isNavigating)
	{
		acc += Navigate(t_Path, botPos, botVelocity);
	}

	return acc;
}