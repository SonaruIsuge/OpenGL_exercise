#pragma once
#include "State.h"
#include "../GameObjects/Enemy/Boss.h"


class BossLastState : public State {
private:
	float moveTimer;
	float rotateTimer;
	vec3 randomMoveDes;
	vec3 randomMoveDir;
	vec3 subFirePos;

	std::vector<ShootingPart*> shootingParts;

public:
	BossLastState(Character& owner);
	~BossLastState();

	void Enter() override;
	void UpdateMove(float deltaTime) override;
	void UpdateShoot(float deltaTime) override;
	void Exit() override;
};