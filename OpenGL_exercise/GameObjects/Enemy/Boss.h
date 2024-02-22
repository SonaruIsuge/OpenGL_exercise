#pragma once
#include "Enemy.h"
#include "../../StateMachine/State.h"

class Boss : public Enemy {
private:
	State* currentState;
	std::vector<ShootingPart*> allShootingParts;

	void UpdateShooting(float deltaTime) override;
	void UpdateMove(float deltaTime) override;

public:
	Boss(Shape* shape, Camera* camera, Object* fireTarget);
	~Boss();

	void Init() override;
	void ChangeState(State* newState);
};