#include "../Bullet.h"
#include "../../Shapes/GDShape.h"
#include "Enemy.h"

Enemy::Enemy(Shape* shape, Camera* camera) : Character(shape, camera) {
	camp = ENEMY;

	SetInitialData(NORMAL_E_HEALTH, NORMAL_E_DAMAGE);

	AddComponent<ShootingPart>(NORMAL_E_BULLET_COOLDOWN);
	shootingPart = GetComponent<ShootingPart>();
}


Enemy::~Enemy() {

}


void Enemy::Update(float deltaTime) {
	UpdateShooting(deltaTime);
	UpdateMove(deltaTime);
}


void Enemy::UpdateShooting(float deltaTime) {

}


void Enemy::UpdateMove(float deltaTime) {

}