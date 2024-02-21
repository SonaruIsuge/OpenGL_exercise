#pragma once
#include "Enemy.h"


class ExpertEnemy : public Enemy {
private:
	float shootReloadTimer;
	int shootBulletThisWave;
	std::vector<ShootingPart*> shootingParts;

	void UpdateShooting(float deltaTime) override;
	void UpdateMove(float deltaTime) override;

public:
	ExpertEnemy(Shape* shape, Camera* camera, Object* fireTarget);
	~ExpertEnemy();

	void Init() override;
};