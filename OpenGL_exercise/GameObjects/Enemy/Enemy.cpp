#include "../../Tools/GameSettings.h"
#include "Enemy.h"

Enemy::Enemy(Shape* shape, Camera* camera, Object* fireTarget) : Character(shape, camera), target(fireTarget) {
	camp = ENEMY;
	active = false;
	recordInitPos = vec3(0);
}


Enemy::~Enemy() {

}


void Enemy::Instantiate(vec3 position) {
	recordInitPos = position;
	this->position = position;
	active = true;
}


void Enemy::Update(float deltaTime) {
	if (!active) return;

	UpdateMove(deltaTime);
	UpdateShooting(deltaTime);

	Character::Update(deltaTime);
}


void Enemy::SetActive(bool active) {
	this->active = active;
}


bool Enemy::IsActive() {
	return active;
}