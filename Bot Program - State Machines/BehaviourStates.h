#pragma once

#include "vector2D.h"
#include "State.h"
#include <vector>

// Forward Declaration of Classes
class Bot;

// Forward Declaration of Structs
struct DominationPoint;
struct SupplyPoint;

// Enum to sort Behaviours
enum e_Behaviours { ACTIVATE_SEEK, ACTIVATE_ARRIVE, ACTIVATE_PURSUE, 
	ACTIVATE_EVADE, ACTIVATE_FLEE, ACTIVATE_AVOIDWALLS, ACTIVATE_NAVIGATION,
	DEACTIVATE_SEEK, DEACTIVATE_ARRIVE, DEACTIVATE_PURSUE, DEACTIVATE_EVADE, 
	DEACTIVATE_FLEE, DEACTIVATE_AVOIDWALLS, DEACTIVATE_NAVIGATION };


// This class is the parent to the bot class
// It serves to provide various functions 
// that calculate vectors to make certain movements
// before calculating these vectors for a final movement.
// Behaviours can be turnd on and off to determine what ones
// the bot incorporates.
class BehaviourStates
{
private:
	// Booleans to dictate Behaviours
	bool isSeeking; // Seeking target
	bool isPursuing; // Pursuing Target
	bool isEvading; // Avoiding Targets
	bool isFleeing; // Fleeing
	bool isAvoidWalls; // Avoiding Walls
	bool isNavigating; // Navigating Paths
	bool isArriving; // Arriving at Target

public:
	int botTarget;
	int domTarget;

	Vector2D supLocation;

	State<Bot>* pCurrentState;
	State<Bot>* pPrevState;

	std::vector<Vector2D> m_path;

	BehaviourStates();

	void setBehaviour(e_Behaviours behaviour);

	void turnOffAll();

	void setPath(std::vector<Vector2D>* newPath);

	std::vector<Vector2D>* getPath();

	Vector2D Seek(Vector2D target, Vector2D botPos, Vector2D botVelocity);
	Vector2D Arrive(Vector2D target, Vector2D botPos, Vector2D botVelocity);
	Vector2D Pursue(Vector2D target, Vector2D targetVelocity, 
		Vector2D botPos, Vector2D botVelocity);
	Vector2D AvoidWall(Vector2D position, Vector2D velocity);
	Vector2D Navigate(std::vector<Vector2D>* t_Path, Vector2D position, Vector2D velocity);
	Vector2D AccumulateVectors(Vector2D position, Vector2D velocity, Vector2D botPos, 
		Vector2D botVelocity, std::vector<Vector2D>* t_Path);
};

