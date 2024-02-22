#include "BossAdvanceState.h"
#include "../Tools/GameSettings.h"
#include "../Tools/Random.h"
#include "BossLastState.h"

BossAdvanceState::BossAdvanceState(Character& owner) : State(owner) {
	moveTimer = 0;
	rotateTimer = 0;
	reloadTimer = 0;
	shortReloadTimer = 0;
	bulletCount = 0;

	shootingParts = owner.GetComponents<ShootingPart>();
}


BossAdvanceState::~BossAdvanceState() {

}


void BossAdvanceState::Enter() {
	
	for (auto& part : shootingParts)
		part->ChangeCoolDown(BOSS_ADVANCE_STATE_BULLET_SHORT_COOLDOWN);
}


void BossAdvanceState::UpdateMove(float deltaTime) {
	if (owner.GetHealth01() < 0.3f) {
		((Boss&)owner).ChangeState(new BossLastState(owner));
		return;
	}

	moveTimer += deltaTime;
	rotateTimer += deltaTime;
	Random random;
	if (moveTimer >= BOSS_ADVANCE_STATE_MOVE) {
		float randX = random.randFloat(-VIEWPORT_HALF_WIDTH * 0.6f, VIEWPORT_HALF_HEIGHT * 0.6f);
		float randY = random.randFloat(-VIEWPORT_HALF_WIDTH * 0.3f, VIEWPORT_HALF_HEIGHT * 0.3f);
		owner.position = vec3(randX, randY, 0);

		moveTimer -= BOSS_ADVANCE_STATE_MOVE;
	}

	owner.rotation.z = rotateTimer * (360.0f / BOSS_ADVANCE_STATE_ROTATE);
	if (rotateTimer >= BOSS_ADVANCE_STATE_ROTATE) rotateTimer -= BOSS_ADVANCE_STATE_ROTATE;
}


void BossAdvanceState::UpdateShoot(float deltaTime) {
	//shortReloadTimer += deltaTime;
	reloadTimer += deltaTime;

	Random random;
	if (bulletCount < BOSS_ADVANCE_BULLET_COUNT_PER_WAVE && 
		reloadTimer <= BOSS_ADVANCE_STATE_MOVE - BOSS_ADVANCE_STATE_BULLET_COOLDOWN) {
		
		vec3 pos = owner.position + random.randPointInRound(2);
		bool successGenerateBullet = shootingParts[0]->Fire(ENEMY, pos, pos - owner.position, BOSS_ADVANCE_STATE_MOVE, BOSS_DAMAGE);
		if(successGenerateBullet) bulletCount++;
		//shortReloadTimer -= reloadTime;
	}

	if (reloadTimer >= BOSS_ADVANCE_STATE_MOVE) {
		reloadTimer -= BOSS_ADVANCE_STATE_MOVE;
		bulletCount = 0;
	}
}


void BossAdvanceState::Exit() {

}