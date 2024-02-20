#pragma once
#include "Enemy.h"


class NormalEnemy : public Enemy {
private:
	ShootingPart* shootingPart;

	void UpdateShooting(float deltaTime) override;
	void UpdateMove(float deltaTime) override;

public:
	NormalEnemy(Shape* shape, Camera* camera, Object* fireTarget);
	~NormalEnemy();

	void Init() override;
};