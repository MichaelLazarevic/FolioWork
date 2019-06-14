#pragma once

#include "bot.h"

// This class represents the bot state of
// Capture. Bots under this state will focus on
// capturing their assigned domination points
class captureState :
	public State<Bot>
{
public:
private:
	static captureState* pInstance;
	std::string m_action;

	captureState();


public:
	static captureState* getInstance();

	void Start(Bot* pBot);

	void Update(Bot* pBot);

	void setTarget(Bot* pBot);

	void seekDistance(Bot* pBot);

	void nearbyTargets(Bot* pBot);

	void domOwnership(Bot* pBot);

	std::string getState();

	void Clean(Bot* pBot);

	static void Release();
};

