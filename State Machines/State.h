#pragma once

// Abstract class for States
// Main functions are inherited
template <class Entity>
class State
{
public:
	virtual void Start(Entity* entity) = 0;
	virtual void Update(Entity* entity) = 0;

	virtual void Clean(Entity* entity) = 0;
	//virtual std::string getState() = 0;
};