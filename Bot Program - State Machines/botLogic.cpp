#include "botLogic.h"



botLogic::botLogic()
{
}

float botLogic::calcVulnerability(float health, float targetDistance)
{
	float damage = (health / 1000.0f);
	float distance = (targetDistance / 1000.0f);

	m_botVul = (1 - damage)*(1 - distance);

	if (m_botVul > 1)
	{
		m_botVul = 1;
	}
	else if (m_botVul < 0)
	{
		m_botVul = 0;
	}
	return m_botVul;
}

float botLogic::calcRefill(int nearbyTeam, int ammoNum, float health, float targetDistance)
{
	float team = (float)nearbyTeam * 0.2f;
	float distance = targetDistance * 0.01f;
	float ammo = (MAXAMMO - (float)ammoNum) * 0.1f;

	m_botRefill = team * ammo * distance;

	if (m_botRefill > 1)
	{
		m_botRefill = 1;
	}
	else if (m_botRefill < 0)
	{
		m_botRefill = 0;
	}

	return m_botRefill;
}

float botLogic::getRefill()
{
	return m_botRefill;
}

float botLogic::getVulnerability()
{
	return m_botVul;
}