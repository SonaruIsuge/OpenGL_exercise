#include "BossNormalState.h"
#include "../Tools/GameSettings.h"
#include "BossLastState.h"
#include "../Tools/Random.h"


BossLastState::BossLastState(Character& owner) : State(owner) {
	moveTimer = 0.0f;
	rotateTimer = 0.0f;
	randomMoveDes = vec3(0.0f);
	randomMoveDir = vec3(0.0f);
	subFirePos = vec3(VIEWPORT_HALF_WIDTH, VIEWPORT_HALF_HEIGHT, 0.0f);

	shootingParts = owner.GetComponents<ShootingPart>();
}


BossLastState::~BossLastState() {

}


void BossLastState::Enter() {

	for (auto& part : shootingParts)
		part->ChangeCoolDown(BOSS_LAST_STATE_BULLET_COOLDOWN);

}


void BossLastState::UpdateMove(float deltaTime) {
	moveTimer += deltaTime;
	rotateTimer += deltaTime;

	Random random;
	if (moveTimer >= BOSS_LAST_STATE_MOVE_TIME - 4) {
		
		randomMoveDes = vec3(random.randFloat(-VIEWPORT_HALF_WIDTH, VIEWPORT_HALF_WIDTH), random.randFloat(VIEWPORT_HALF_HEIGHT * 0.9f, VIEWPORT_HALF_HEIGHT * 0.5f), 0);
		randomMoveDir = normalize(randomMoveDes - this->owner.position);
		moveTimer -= BOSS_LAST_STATE_MOVE_TIME;
	}
	else if (length(this->owner.position - randomMoveDes) > 0.05f) {
		this->owner.position += randomMoveDir * BOSS_LAST_STATE_MOVE_SPEED * deltaTime;
	}

	owner.rotation.z = rotateTimer * (360.0f / BOSS_LAST_STATE_ROTATE);
	if (rotateTimer >= BOSS_LAST_STATE_ROTATE) rotateTimer -= BOSS_LAST_STATE_ROTATE;
}


void BossLastState::UpdateShoot(float deltaTime) {
	// Main Bullet
	for (int i = 0; i < BOSS_SHOOTINGPART - 5; i++) {
		vec3 pos = vec3(0.2f * cosf(radians(15.0f * i)), 0.2f * sinf(radians(15.0f * i)), 0.0f);
		shootingParts[i]->Fire(ENEMY, owner.position + pos, normalize(pos / cosf(radians(45.0f))), BOSS_LAST_STATE_BULLET_SPEED, BOSS_DAMAGE);
	}

	// Sub Bullet
	float shootSpeedDt = BOSS_SUB_SHOOT_PART_MOVE_SPEED * deltaTime;
	if (subFirePos.x >= VIEWPORT_HALF_WIDTH && subFirePos.y >= -VIEWPORT_HALF_HEIGHT) subFirePos.y -= shootSpeedDt;
	else if (subFirePos.x >= -VIEWPORT_HALF_WIDTH && subFirePos.y <= -VIEWPORT_HALF_HEIGHT) subFirePos.x -= shootSpeedDt;
	else if (subFirePos.x <= -VIEWPORT_HALF_WIDTH && subFirePos.y <= VIEWPORT_HALF_HEIGHT) subFirePos.y += shootSpeedDt;
	else subFirePos.x += shootSpeedDt;

	for (int i = BOSS_SHOOTINGPART - 1; i > BOSS_SHOOTINGPART - 5; i--) {
		shootingParts[i]->ChangeCoolDown(BOSS_SUB_BULLET_COOLDOWN);
		shootingParts[i]->ChangeBulletType(CircleBullet);
	}

	shootingParts[BOSS_SHOOTINGPART - 4]->Fire(ENEMY, subFirePos, normalize(vec3(-subFirePos.x, -subFirePos.y, 0)), BOSS_SUB_BULLET_SPEED, BOSS_DAMAGE);
	shootingParts[BOSS_SHOOTINGPART - 3]->Fire(ENEMY, -subFirePos, normalize(vec3(subFirePos.x, subFirePos.y, 0)), BOSS_SUB_BULLET_SPEED, BOSS_DAMAGE);
	shootingParts[BOSS_SHOOTINGPART - 2]->Fire(ENEMY, vec3(-subFirePos.x, subFirePos.y, 0), normalize(vec3(subFirePos.x, -subFirePos.y, 0)), BOSS_SUB_BULLET_SPEED, BOSS_DAMAGE);
	shootingParts[BOSS_SHOOTINGPART - 1]->Fire(ENEMY, vec3(subFirePos.x, -subFirePos.y, 0), normalize(vec3(-subFirePos.x, subFirePos.y, 0)), BOSS_SUB_BULLET_SPEED, BOSS_DAMAGE);
}


void BossLastState::Exit() {
	owner.rotation = vec3(0.0f);
}