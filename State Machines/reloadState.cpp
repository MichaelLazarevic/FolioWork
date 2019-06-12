#include "reloadState.h"
#include "captureState.h"




reloadState* reloadState::pInstance = nullptr;


reloadState::reloadState()
{
	m_action = "reloading";
}


reloadState* reloadState::getInstance()
{
	if (!pInstance)
	{
		pInstance = new reloadState;
	}

	return pInstance;

}

void reloadState::Start(Bot* pBot)
{
	pBot->turnOffAll();
	pBot->setBehaviour(ACTIVATE_NAVIGATION);
	pBot->setBehaviour(ACTIVATE_AVOIDWALLS);

	SetResupplyPoint(pBot);

}

//Decides when to reload
void reloadState::Update(Bot* pBot)
{
	if (pBot->getAmmo() == MAXAMMO)
	{
		pBot->StateChange(captureState::getInstance());
	}
	ArriveOrSeek(pBot);

	pBot->setAccel(pBot->AccumulateVectors(pBot->supLocation, Vector2D(0, 0), pBot->GetLocation(), pBot->GetVelocity(), pBot->getPath()));

}

// Cleans all the state stuff ready for next state 
void reloadState::Clean(Bot* pBot)
{
	pBot->turnOffAll();
}

void reloadState::SetResupplyPoint(Bot* pBot)
{
	GetClosestResupply(pBot);
	pBot->setPath(&Navigation::getInstance()->createPath(pBot->GetLocation(), pBot->supLocation));
}

void reloadState::ArriveOrSeek(Bot* pBot)
{

	if (StaticMap::GetInstance()->IsLineOfSight(pBot->GetLocation(), pBot->supLocation))
	{
		if ((pBot->GetLocation() - pBot->supLocation).magnitude() < 100)
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
		}
	}

}

void reloadState::GetClosestResupply(Bot* pBot)
{
	float distanceToRessuplyTwo = (StaticMap::GetInstance()->GetResupplyLocation(2) - pBot->GetLocation()).magnitude();
	float distanceToRessuplyThree = (StaticMap::GetInstance()->GetResupplyLocation(3) - pBot->GetLocation()).magnitude();

	if (distanceToRessuplyTwo > distanceToRessuplyThree)
	{
		pBot->supLocation = StaticMap::GetInstance()->GetResupplyLocation(3);
	}
	else
	{
		pBot->supLocation = StaticMap::GetInstance()->GetResupplyLocation(2);
	}

}


std::string reloadState::getState()
{

	return m_action;

}


void reloadState::Release()
{

	if (pInstance)
	{
		delete pInstance;
		pInstance = nullptr;
	}

}