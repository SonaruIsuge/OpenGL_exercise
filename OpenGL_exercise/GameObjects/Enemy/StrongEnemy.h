#pragma once
#include <vector>
#include "Enemy.h"
#include "../../Tools/GameSettings.h"


class StrongEnemy : public Enemy {
private:
	std::vector<ShootingPart*> shootingParts;


protected:
	void UpdateShooting(float deltaTime) override;
	void UpdateMove(float deltaTime) override;

public:
	StrongEnemy(Shape* shape, Camera* camera, Object* fireTarget);
	~StrongEnemy();

	void Init() override;
};