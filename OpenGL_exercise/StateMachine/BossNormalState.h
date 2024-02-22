#pragma once
#include "State.h"
#include "../GameObjects/Enemy/Boss.h"


class BossNormalState : public State {
private :
	float rotateTimer;
	float rotateTime;
	vec3 shootPoint[4];

	std::vector<ShootingPart*> shootingParts;

	vec3 UpdatePointAfterRotate(vec3 originPoint);

public:
	BossNormalState(Character& owner);
	~BossNormalState();

	void Enter() override;
	void UpdateMove(float deltaTime) override;
	void UpdateShoot(float deltaTime) override;
	void Exit() override;
};