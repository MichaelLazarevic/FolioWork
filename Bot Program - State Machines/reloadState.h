#pragma once
#include "bot.h"

// This class represents the bot state of
// reload. Bots under this state will focus on
// attempting to reload their ammunition as soon as possible
class reloadState :
	public State<Bot>
{
private:
	static reloadState* pInstance;
	std::string m_action;

	reloadState();

public:

	static reloadState* getInstance();

	void Start(Bot* pBot);

	void Update(Bot* pBot);

	void SetResupplyPoint(Bot* pBot);

	void ArriveOrSeek(Bot* pBot);

	void GetClosestResupply(Bot* pBot);

	void Clean(Bot* pBot);

	std::string getState();

	static void Release();
};