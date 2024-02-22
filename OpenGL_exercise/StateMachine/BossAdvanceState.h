#pragma once
#include "State.h"
#include "../GameObjects/Enemy/Boss.h"


class BossAdvanceState : public State {
private:
	float moveTimer;
	float rotateTimer;
	float reloadTimer;
	float shortReloadTimer;
	int bulletCount;

	std::vector<ShootingPart*> shootingParts;


public:
	BossAdvanceState(Character& owner);
	~BossAdvanceState();

	void Enter() override;
	void UpdateMove(float deltaTime) override;
	void UpdateShoot(float deltaTime) override;
	void Exit() override;
};