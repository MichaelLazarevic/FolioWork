#include "attackState.h"
#include "dynamicObjects.h"
#include "retreatState.h"
#include "captureState.h"
#include "reloadState.h"

attackState* attackState::pInstance = nullptr;

attackState::attackState()
{
	m_action = "Attacking"; // Sets variable for debug purposes
}

attackState* attackState::getInstance()
{
	if (!pInstance)
	{
		pInstance = new attackState;

	}
	return pInstance; // Returns the current instance
}

void attackState::Start(Bot* pBot)
{
	pBot->turnOffAll();
	pBot->setBehaviour(ACTIVATE_PURSUE);
	pBot->setBehaviour(ACTIVATE_AVOIDWALLS);

	setTarget(pBot); // Initialises selected behaviours. Sets selected enemy as target
}

void attackState::Update(Bot* pBot)
{
	// Checks how weak the bot is
	// If the bot is sufficiently weak enough
	// or in danger, it will begin to flee and cause
	// a retreation
	if (pBot->getVulnerability() > 0.8)
	{
		pBot->StateChange(retreatState::getInstance());

	}

	if (pBot->botTarget != -1)
	{
		// reload if there is no ammo
		if (pBot->getAmmo() < 1)
		{
			pBot->StateChange(reloadState::getInstance());
		}
		else if (!inSight(pBot) || !isAlive(pBot))
		{
			// If there is no target can start capturing
			pBot->StateChange(captureState::getInstance());
		}
		else if (targetDistance(pBot) > 400)
		{
			// Gather variables needed to move to target
			Vector2D targetPos = DynamicObjects::GetInstance()->GetBot(1, pBot->botTarget).GetLocation();
			Vector2D targetVel = DynamicObjects::GetInstance()->GetBot(1, pBot->botTarget).GetVelocity();
			Vector2D botPos = pBot->GetLocation();
			Vector2D botVel = pBot->GetVelocity();
			std::vector<Vector2D>* path = pBot->getPath();

			// Move to target if too far away
			pBot->setAccel(pBot->AccumulateVectors(targetPos, targetVel, botPos, botVel, path));
		}
		else if (pBot->GetTargetTeam() != 1)
		{
			// If the bot isn't aiming
			pBot->SetTarget(1, pBot->botTarget);

		}

		// Shoot the enemy when within distance
		if (targetDistance(pBot) < 500)
		{
			if (pBot->GetAccuracy() >= 0.7)
			{
				pBot->Shoot();
			}
		}
		else
		{
			if (pBot->GetAccuracy() >= 0.6)
			{
				pBot->Shoot();
			}
		}
	}
	else
	{
		pBot->StateChange(captureState::getInstance());
	}

}


// Sets the given Bot as a target to be fired upon
void attackState::setTarget(Bot* pBot)
{
	int closeDist = 999999999;

	for (int i = 0; i < NUMBOTSPERTEAM; i++)
	{
		Vector2D indexedBotLocation = DynamicObjects::GetInstance()->GetBot(1, i).GetLocation();
		float distanceToIndexedBot = (pBot->GetLocation() - indexedBotLocation).magnitude();
		bool isIndexedBotAlive = DynamicObjects::GetInstance()->GetBot(1, i).IsAlive();

		if (StaticMap::GetInstance()->IsLineOfSight(pBot->GetLocation(), indexedBotLocation) &&
			(distanceToIndexedBot <= 600 && isIndexedBotAlive && distanceToIndexedBot < closeDist))
		{
			closeDist = distanceToIndexedBot;
			pBot->botTarget = i;
			pBot->SetTarget(1, i);
		}
	}

}

// Is a target within sight of the bot
bool attackState::inSight(Bot* pBot)
{
	Vector2D targetPosition = DynamicObjects::GetInstance()->GetBot(1, pBot->botTarget).GetLocation();
	return StaticMap::GetInstance()->IsLineOfSight(pBot->GetLocation(), targetPosition);

}

// Is the bot alive
bool attackState::isAlive(Bot* pBot)
{
	return DynamicObjects::GetInstance()->GetBot(1, pBot->botTarget).IsAlive();

}

// Distance to the enemy
float attackState::targetDistance(Bot* pBot)
{
	return (pBot->GetLocation() - DynamicObjects::GetInstance()->GetBot(1, pBot->botTarget).GetLocation()).magnitude();

}

// State Name - String
std::string attackState::getState()
{
	return m_action;

}

// Wipes variables in order to cleanly
// switch to another state
void attackState::Clean(Bot* pBot)
{
	pBot->StopAiming();
	pBot->botTarget = -1;
	pBot->turnOffAll();

}

// Deconstructing
void attackState::Release()
{
	if (pInstance)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}