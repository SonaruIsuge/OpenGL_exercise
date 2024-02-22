#include "BossNormalState.h"
#include "../Tools/GameSettings.h"
#include "BossAdvanceState.h"


BossNormalState::BossNormalState(Character& owner) : State(owner) {
	rotateTimer = 0;
	rotateTime = BOSS_NORMAL_STATE_ROTATE;
	shootingParts = owner.GetComponents<ShootingPart>();
}


BossNormalState::~BossNormalState() {

}


void BossNormalState::Enter() {
	shootPoint[0] = owner.position + vec3(0, 0 - owner.shape->GetBoundRadius(), 0);
	shootPoint[1] = owner.position + vec3(0 - owner.shape->GetBoundRadius(), 0, 0);
	shootPoint[2] = owner.position + vec3(0, 0 + owner.shape->GetBoundRadius(), 0);
	shootPoint[3] = owner.position + vec3(0 + owner.shape->GetBoundRadius(), 0, 0);

	for (auto& part : shootingParts)
		part->ChangeCoolDown(BOSS_NORMAL_STATE_BULLET_COOLDOWN);
}


void BossNormalState::UpdateMove(float deltaTime) {

	if (owner.GetHealth01() < 0.6f) {
		((Boss&)owner).ChangeState(new BossAdvanceState(owner));
		return;
	}

	rotateTimer += deltaTime;
	owner.rotation.z = rotateTimer * (360 / rotateTime);
	if (rotateTimer >= rotateTime) rotateTimer -= rotateTime;

	vec3 dir = vec3(0, -1, 0);
	if (owner.position.y > 0.0f) owner.position += dir * BOSS_MOVESPEED * deltaTime;
}


void BossNormalState::UpdateShoot(float deltaTime) {	
	
	for (int i = 0; i < 4; i++) {
		vec3 pos = UpdatePointAfterRotate(shootPoint[i]);
		shootingParts[i]->SetBulletRecycleTime(15.0f);
		shootingParts[i]->Fire(ENEMY, pos, normalize(pos - owner.position), BOSS_BULLET_SPEED, BOSS_DAMAGE);
	}
	
}


void BossNormalState::Exit() {
	owner.rotation = vec3(0.0f);
}


vec3 BossNormalState::UpdatePointAfterRotate(vec3 originPoint) {
	float rotateAngle = owner.rotation.z;
	
	vec3 result = vec3(0);
	result.x = (originPoint.x - owner.position.x) * cosf(radians(rotateAngle)) - (originPoint.y) * sinf(radians(rotateAngle)) + owner.position.x;
	result.y = (originPoint.x - owner.position.x) * sinf(radians(rotateAngle)) + (originPoint.y) * cosf(radians(rotateAngle)) + owner.position.y;
	result.z = 0;
	return result;
}