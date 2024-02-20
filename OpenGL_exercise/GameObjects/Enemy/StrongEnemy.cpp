#include "../../math.h"
#include "StrongEnemy.h"
#include "../../Tools/GameSettings.h"

StrongEnemy::StrongEnemy(Shape* shape, Camera* camera, Object* fireTarget) : Enemy(shape, camera, fireTarget) {
	Init();
}


StrongEnemy::~StrongEnemy() {
	
}


void StrongEnemy::Init() {
	this->SetColor(STRONG_E_COLOR);
	SetInitialData(STRONG_E_HEALTH, STRONG_E_DAMAGE);

	AddComponent<ShootingPart>(ThornBullet, STRONG_E_BULLET_COOLDOWN);
	AddComponent<ShootingPart>(ThornBullet, STRONG_E_BULLET_COOLDOWN);
	AddComponent<ShootingPart>(ThornBullet, STRONG_E_BULLET_COOLDOWN);
	AddComponent<ShootingPart>(ThornBullet, STRONG_E_BULLET_COOLDOWN);
	AddComponent<ShootingPart>(ThornBullet, STRONG_E_BULLET_COOLDOWN);
	shootingParts = GetComponents<ShootingPart>();
}


void StrongEnemy::UpdateMove(float deltaTime) {
	this->position.y += -STRONG_E_MOVESPEED * deltaTime;
	this->position.x = VIEWPORT_HALF_WIDTH / 2 * cos(this->position.y) + recordInitPos.x;

	if (this->position.y < -VIEWPORT_HALF_HEIGHT * 1.2f) {
		active = false;
	}
}


void StrongEnemy::UpdateShooting(float deltaTime) {
	for(int i = 0; i < shootingParts.size(); i++) {
		float angle = gameMath::angleWithSign(vec3(0, 1, 0), target->position - position) + 10 * (i - 2) ;
		vec3 pos = this->shape->position;
		pos.x += 0.2f * cosf(radians(270.0f) + angle);
		pos.y += 0.2f * sinf(radians(270.0f) + angle);

		vec3 direction = pos - this->position;

		shootingParts[i]->SetBulletRecycleTime(15.0f);
		shootingParts[i]->Fire(camp, pos, direction, STRONG_E_BULLET_SPEED, STRONG_E_DAMAGE);
	}
}