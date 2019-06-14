#pragma once
#include "bot.h"

// This class represents the bot state of
// retreat. Bots under this state will flee
// from enemies in an attempt to retreat them
// preserve their life as long as possible
class retreatState :
	public State<Bot>
{
private:
	static retreatState* pInstance;
	std::string m_action;
	Vector2D originalPos;
	bool switchDirection = false;

	retreatState();
public:
	static retreatState* getInstance();

	void Start(Bot* pBot);

	void Update(Bot* pBot);

	void Clean(Bot* pBot);

	std::string getState();

	static void Release();
};

