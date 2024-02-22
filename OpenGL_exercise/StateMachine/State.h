#pragma once
#include "../GameObjects/Character.h"


class State {
protected:
	Character& owner;


public:
	State(Character& owner);
	~State();

	virtual void Enter() = 0;
	virtual void UpdateMove(float deltaTime) = 0;
	virtual void UpdateShoot(float deltaTime) = 0;
	virtual void Exit() = 0;
};