#include "retreatState.h"
#include "defendState.h"


retreatState* retreatState::pInstance = nullptr;

retreatState::retreatState()
{
	m_action = "retreat";
}

retreatState* retreatState::getInstance()
{
	if (!pInstance)
	{
		pInstance = new retreatState;
	}
	return pInstance;
}

void retreatState::Start(Bot* pBot)
{
	pBot->retreatPoint = pBot->GetLocation();
	pBot->turnOffAll(); // Clears currently active behaviours
	pBot->setBehaviour(ACTIVATE_FLEE); // Activates Flee
}

void retreatState::Update(Bot* pBot)
{

	// Switches the direction to interfere with Bots targetting this one
	if (!switchDirection && pBot->GetLocation().YValue < pBot->retreatPoint.YValue - 4)
	{
		switchDirection = true;
	}

	if (switchDirection && pBot->GetLocation().YValue > pBot->retreatPoint.YValue + 4)
	{
		switchDirection = false;

	}

	// Determines a level of danger based on given variables
	// Checks how dangerous it is and defends if the danger is below 0.5
	if (pBot->getVulnerability() < 0.5)
	{
		pBot->StateChange(defendState::getInstance());

	}
	// Creates a new accceleration based on  other calculations before applying it.
	Vector2D desiredVelocity = (Vector2D(pBot->GetLocation().XValue, 1300) - pBot->GetLocation()).unitVector() * MAXIMUMSPEED;
	Vector2D acc = (desiredVelocity - pBot->GetVelocity());
	if (switchDirection)
	{
		pBot->setAccel(acc);
	}
	else
	{
		pBot->setAccel(-acc);
	}


}

// Cleans all the state stuff ready for next state 
void retreatState::Clean(Bot* pBot)
{
	pBot->turnOffAll();
}


// The states name as a string
std::string retreatState::getState()
{
	return m_action;
}

// Deconstructs pointer reference
void retreatState::Release()
{
	if (pInstance)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}