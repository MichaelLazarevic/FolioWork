#pragma once
#include "rules.h"


// This class makes use of Fuzzy Logic
// By taking in certain variables, it calculates
// a number that determines how vulnerable
// the bot is to death, and how much it needs
// ammunition to be reloaded.
// These numbers can be used to determine
// when the bot switches to the retreat and reload states
class botLogic
{
private:
	float m_botRefill = 0; // Level for Safe Refill
	float m_botVul = 0; // Level of Vulnerability
public:
	botLogic();

	float calcVulnerability(float health, float targetDistance);
	float getVulnerability();

	float calcRefill(int nearbyTeam, int ammoNum, float health, float targetDistance);
	float getRefill();
};

