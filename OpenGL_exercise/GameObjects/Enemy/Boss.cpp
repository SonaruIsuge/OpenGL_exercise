#include "Boss.h"
#include "../../Tools/GameSettings.h"
#include "../../StateMachine/BossNormalState.h"


Boss::Boss(Shape* shape, Camera* camera, Object* fireTarget) : Enemy(shape, camera, fireTarget) {
	Init();
}


Boss::~Boss() {

}


void Boss::Init() {
	this->SetColor(BOSS_COLOR);
	SetInitialData(BOSS_HEALTH, BOSS_DAMAGE);

	for (int i = 0; i < BOSS_SHOOTINGPART; i++)
		AddComponent<ShootingPart>(ShurikenBullet, BOSS_BULLET_COOLDOWN);

	allShootingParts = GetComponents<ShootingPart>();
	ChangeState(new BossNormalState(*this));
}


void Boss::UpdateMove(float deltaTime) {
	currentState->UpdateMove(deltaTime);
}


void Boss::UpdateShooting(float deltaTime) {
	currentState->UpdateShoot(deltaTime);
}


void Boss::ChangeState(State* newState) {
	if (currentState != nullptr) currentState->Exit();
	currentState = newState;
	currentState->Enter();
}