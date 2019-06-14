#pragma once
#include "bot.h"

// This class represents the bot state of
// Defense. Bots under this state will focus on
// defending a location and attacking nearby enemies
class defendState :
	public State<Bot>
{
private:
	static defendState* pInstance;
	std::string m_action;

	defendState();
public:
	static defendState* getInstance();

	void Start(Bot* pBot);

	void Update(Bot* pBot);

	void setTarget(Bot* pBot);

	void checkDistance(Bot* pBot);

	void nearbyEnemy(Bot* pBot);

	void checkOwner(Bot* pBot);

	std::string getState();

	void Clean(Bot* pBot);

	static void Release();
};

