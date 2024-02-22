#include "ExpertEnemy.h"
#include "../../Tools/GameSettings.h"


ExpertEnemy::ExpertEnemy(Shape* shape, Camera* camera, Object* fireTarget) : Enemy(shape, camera, fireTarget) {
	Init();
}


ExpertEnemy::~ExpertEnemy() {
	
}


void ExpertEnemy::Init() {
	shootReloadTimer = 0.0f;
	shootBulletThisWave = 0;

	this->SetColor(EXPERT_E_COLOR);
	SetInitialData(EXPERT_E_HEALTH, EXPERT_E_DAMAGE);

	for(int i = 0; i < 10; i++)	AddComponent<ShootingPart>(NeedleBullet, EXPERT_E_BULLET_SHORT_COOLDOWN);
	
	shootingParts = GetComponents<ShootingPart>();
}


void ExpertEnemy::UpdateMove(float deltaTime) {
	this->position += vec3(0, -EXPERT_E_MOVESPEED * deltaTime, 0);

	if (this->position.y < -VIEWPORT_HALF_HEIGHT * 1.2f) {
		active = false;
	}
}


void ExpertEnemy::UpdateShooting(float deltaTime) {
	if (shootBulletThisWave < EXPERT_E_BULLET_WAVE_PER_COOLDOWN) {
			
		bool fireSuccess = false;
		if (this->position.x < 0) {
			for (int i = 0; i < 10; i++) {
				float angle = 10.0f * i;
				vec3 dir = normalize(vec3( cosf(radians(270.0f + angle)), sinf(radians(270.0f + angle)), 0.0f) );					
				shootingParts[i]->SetBulletRecycleTime(15.0f);
				fireSuccess = shootingParts[i]->Fire(this->camp, this->position + 0.2f * dir, dir, EXPERT_E_BULLET_SPEED, EXPERT_E_DAMAGE);
			}
		}
		else {
			for (int i = 0; i < 10; i++) {
				float angle = 10.0f * i;
				vec3 dir = normalize(vec3(cosf(radians(180.0f + angle)), sinf(radians(180.0f + angle)), 0.0f));
				shootingParts[i]->SetBulletRecycleTime(15.0f);
				fireSuccess = shootingParts[i]->Fire(this->camp, this->position + 0.2f * dir, dir, EXPERT_E_BULLET_SPEED, EXPERT_E_DAMAGE);
			}
		}
		if(fireSuccess) shootBulletThisWave++;
	}
	else {
		shootReloadTimer += deltaTime;
		if (shootReloadTimer >= EXPERT_E_BULLET_COOLDOWN) {
			shootBulletThisWave = 0;
			shootReloadTimer = 0.0f;
		}
	}
}