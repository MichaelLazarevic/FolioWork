#pragma once
#include "bot.h"

// This class represents the bot state of
// Attack. Bots under this state will focus on
// attacking nearby enemies
class attackState :
	public State<Bot>
{
private:
	static attackState* pInstance;
	std::string m_action;
	attackState();

public:
	static attackState* getInstance();

	void Start(Bot* pBot);
	void Update(Bot* pBot);

	void setTarget(Bot* pBot);
	bool inSight(Bot* pBot);
	bool isAlive(Bot* pBot);

	std::string getState();
	float targetDistance(Bot* pBot);
	void Clean(Bot* pBot);

	static void Release();
};

