#include "defendState.h"

#include "defendState.h"
#include "attackState.h"
#include "reloadState.h"
#include "retreatState.h"
#include "captureState.h"
#include "dynamicObjects.h"

defendState* defendState::pInstance = nullptr;

defendState::defendState()
{
	m_action = "Defending";
}


defendState* defendState::getInstance()
{
	if (!pInstance)
	{
		pInstance = new defendState;
	}
	return pInstance;
}

//Set the dom point bot defends and sets path to it
void defendState::Start(Bot* pBot)
{
	pBot->turnOffAll();
	pBot->setBehaviour(ACTIVATE_AVOIDWALLS);
	pBot->setBehaviour(ACTIVATE_NAVIGATION);
	setTarget(pBot);
}

//If there is line of sight of domincation point seek to it and if close enough arrive
//Switches to attack state when enemys are around
//Switch to Capture if bots don't own the dom point
//Move bot to dom point
void defendState::Update(Bot* pBot)
{
	checkDistance(pBot);
	nearbyEnemy(pBot);

	//Switch to Capture if bots don't own the dom point
	checkOwner(pBot);

	//
	if (pBot->getRefill() == 1)
	{
		pBot->StateChange(reloadState::getInstance());

	}

	
	if (pBot->getVulnerability() > 0.8)
	{
		pBot->StateChange(retreatState::getInstance());

	}

	Vector2D domLocation = DynamicObjects::GetInstance()->GetDominationPoint(pBot->domTarget).m_Location;
	pBot->setAccel(pBot->AccumulateVectors(domLocation, Vector2D(0, 0), pBot->GetLocation(), pBot->GetVelocity(), pBot->getPath()));

}


void defendState::Clean(Bot* pBot)
{
	pBot->turnOffAll();
}

// Set the dom point going to be defended and generate path to it
void defendState::setTarget(Bot* pBot)
{
	// Sets the target domination point based on bot number
	pBot->domTarget = pBot->getBotNumber() % NUMDOMINATIONPOINTS;

	Vector2D dominationPointLocation = DynamicObjects::GetInstance()->GetDominationPoint(pBot->domTarget).m_Location;

	// Generates the path to the domination point
	pBot->setPath(&Navigation::getInstance()->createPath(pBot->GetLocation(), dominationPointLocation));


}

// Checks distance and Line of Sight to dom Point
void defendState::checkDistance(Bot* pBot)
{
	Vector2D domPointLocation = DynamicObjects::GetInstance()->GetDominationPoint(pBot->domTarget).m_Location;

	if (StaticMap::GetInstance()->IsLineOfSight(pBot->GetLocation(), domPointLocation))
	{
		if ((pBot->GetLocation() - domPointLocation).magnitude() < 100)
		{
			pBot->turnOffAll();
			pBot->setBehaviour(ACTIVATE_ARRIVE);
			pBot->setBehaviour(ACTIVATE_AVOIDWALLS);
		}
		else
		{
			pBot->turnOffAll();
			pBot->setBehaviour(ACTIVATE_SEEK);
			pBot->setBehaviour(ACTIVATE_AVOIDWALLS);
			pBot->getPath()->clear();
		}
	}

}


// Switches to attack state when enemys are around
void defendState::nearbyEnemy(Bot* pBot)
{
	for (int i = 0; i < NUMBOTSPERTEAM; i++)
	{
		Vector2D enemyLocation = DynamicObjects::GetInstance()->GetBot(1, i).GetLocation();
		float distanceToEnemy = (pBot->GetLocation() - enemyLocation).magnitude();
		bool isEnemyAlive = DynamicObjects::GetInstance()->GetBot(1, i).IsAlive();

		if (StaticMap::GetInstance()->IsLineOfSight(pBot->GetLocation(), enemyLocation) && (distanceToEnemy <= 600 && isEnemyAlive))
		{
			pBot->StateChange(attackState::getInstance());
		}
	}

}

// If the team doesn't own it switch to capture
void defendState::checkOwner(Bot* pBot)
{
	int dominationPointTeamNumber = DynamicObjects::GetInstance()->GetDominationPoint(pBot->domTarget).m_OwnerTeamNumber;

	if (dominationPointTeamNumber != pBot->getTeamNumber())
	{
		pBot->StateChange(captureState::getInstance());
	}

}

std::string defendState::getState()
{
	return m_action;
}


void defendState::Release()
{
	if (pInstance)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}