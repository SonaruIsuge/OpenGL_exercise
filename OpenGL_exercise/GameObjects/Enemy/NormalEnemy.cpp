#include "NormalEnemy.h"
#include "../../Tools/GameSettings.h"

NormalEnemy::NormalEnemy(Shape* shape, Camera* camera, Object* fireTarget) : Enemy(shape, camera, fireTarget) {
	Init();
}


NormalEnemy::~NormalEnemy() {

}


void NormalEnemy::Init() {
	this->SetColor(NORMAL_E_COLOR);
	SetInitialData(NORMAL_E_HEALTH, NORMAL_E_DAMAGE);

	AddComponent<ShootingPart>(CircleBullet, NORMAL_E_BULLET_COOLDOWN);
	shootingPart = GetComponent<ShootingPart>();
}


void NormalEnemy::UpdateShooting(float deltaTime) {
	shootingPart->Fire(*target, this->camp, position + vec3(0, -0.5f, 0), NORMAL_E_BULLET_SPEED, NORMAL_E_DAMAGE);
}


void NormalEnemy::UpdateMove(float deltaTime) {
	this->position.y += -NORMAL_E_MOVESPEED * deltaTime;

	if (this->position.y < -VIEWPORT_HALF_HEIGHT * 1.2f) {
		active = false;
	}
}