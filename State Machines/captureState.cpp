#include "captureState.h"
#include "dynamicObjects.h"
#include "attackState.h"
#include <string>
#include "defendState.h"

captureState* captureState::pInstance = nullptr;

captureState::captureState()
{
	m_action = "capturing"; // Sets variable for debug purposes
}

captureState* captureState::getInstance()
{
	if (!pInstance)
	{
		pInstance = new captureState;
	}
	return pInstance; // Returns the current instance
}

void captureState::Start(Bot* pBot)
{
	pBot->turnOffAll();
	pBot->setBehaviour(ACTIVATE_NAVIGATION);
	pBot->setBehaviour(ACTIVATE_AVOIDWALLS);

	setTarget(pBot);// Initialises selected behaviours. Sets selected target as target
}

void captureState::Update(Bot* pBot)
{
	seekDistance(pBot);
	nearbyTargets(pBot);
	domOwnership(pBot);

	Vector2D dominationLocation = DynamicObjects::GetInstance()->GetDominationPoint(pBot->domTarget).m_Location;
	pBot->setAccel(pBot->AccumulateVectors(dominationLocation, Vector2D(0, 0), pBot->GetLocation(), pBot->GetVelocity(), pBot->getPath()));
}

void captureState::setTarget(Bot* pBot)
{
	pBot->domTarget = pBot->getBotNumber() % NUMDOMINATIONPOINTS;
	Vector2D domLocation = DynamicObjects::GetInstance()->GetDominationPoint(pBot->domTarget).m_Location;
	pBot->setPath(&Navigation::getInstance()->createPath(pBot->GetLocation(), domLocation));
}

void captureState::seekDistance(Bot* pBot)
{
	Vector2D domLocation = DynamicObjects::GetInstance()->GetDominationPoint(pBot->domTarget).m_Location;

	if (StaticMap::GetInstance()->IsLineOfSight(pBot->GetLocation(), domLocation))
	{
		pBot->turnOffAll();
		pBot->setBehaviour(ACTIVATE_SEEK);
		pBot->setBehaviour(ACTIVATE_AVOIDWALLS);

		pBot->getPath()->clear();
	}
}

void captureState::nearbyTargets(Bot* pBot)
{
	for (int i = 0; i < NUMBOTSPERTEAM; i++)
	{
		Vector2D enemyLocation = DynamicObjects::GetInstance()->GetBot(1, i).GetLocation();
		float distance = (pBot->GetLocation() - enemyLocation).magnitude();

		bool isAlive = DynamicObjects::GetInstance()->GetBot(1, i).IsAlive();

		if (StaticMap::GetInstance()->IsLineOfSight(pBot->GetLocation(), enemyLocation) && (distance <= 400 && isAlive))
		{
			pBot->StateChange(attackState::getInstance());
		}
	}
}

void captureState::domOwnership(Bot* pBot)
{
	int domTeamNum = DynamicObjects::GetInstance()->GetDominationPoint(pBot->domTarget).m_OwnerTeamNumber;

	if (domTeamNum == pBot->getTeamNumber())
	{
		pBot->StateChange(defendState::getInstance());
	}
}

std::string captureState::getState()
{
	return m_action;
}

void captureState::Clean(Bot* pBot)
{
	pBot->turnOffAll();
}

void captureState::Release()
{
	if (pInstance)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}