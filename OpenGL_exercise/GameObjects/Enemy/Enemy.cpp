#include "../Bullet.h"
#include "../../Shapes/GDShape.h"
#include "Enemy.h"

Enemy::Enemy(Shape* shape, Camera* camera, Object* fireTarget) : Character(shape, camera), target(fireTarget) {
	camp = ENEMY;
	active = false;

	SetInitialData(NORMAL_E_HEALTH, NORMAL_E_DAMAGE);

	AddComponent<ShootingPart>(EnemyBullet, NORMAL_E_BULLET_COOLDOWN);
	shootingPart = GetComponent<ShootingPart>();

	
}


Enemy::~Enemy() {

}


void Enemy::Init(vec3 position) {
	this->position = position;
	active = true;
}


void Enemy::Update(float deltaTime) {
	if (!active) return;

	UpdateShooting(deltaTime);
	UpdateMove(deltaTime);

	Character::Update(deltaTime);
}


void Enemy::Dead() {

	active = false;
}


void Enemy::SetActive(bool active) {
	this->active = active;
}


bool Enemy::IsActive() {
	return active;
}


void Enemy::UpdateShooting(float deltaTime) {
	shootingPart->Fire(*target, this->camp, position + vec3(0, -0.5f, 0), 10, 1);
}


void Enemy::UpdateMove(float deltaTime) {

}