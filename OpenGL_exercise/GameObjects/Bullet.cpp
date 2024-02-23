#include "Bullet.h"
#include "../Tools/GameSettings.h"
#include "../math.h"


Bullet::Bullet(Shape* shape, Camera* camera) : Object(shape, camera) {
	scale = vec3(0.5f);
	damage = 0;
	speed = 0.0f;
	direction = vec3(0.0f);
	camp = OTHER;
	recycleTimer = 0.0f;
	recycleTime = RECYCLE_TIME;
	active = false;

	AddComponent<Collider>(this, this->position, shape->boundRadius);
	collider = GetComponent<Collider>();
}


Bullet::~Bullet() {

}


void Bullet::Update(float deltaTime) {
	if (!active) return;

	position += direction * speed * deltaTime;
	Object::Update(deltaTime);

	recycleTimer += deltaTime;
	// TODO: Change reset determine by using position
	//if (gameMath::abs(position.x) > VIEWPORT_HALF_WIDTH + 1 || gameMath::abs(position.y) > VIEWPORT_HALF_HEIGHT + 1)
	if (recycleTimer >= recycleTime)
		Reset();
}


void Bullet::Fire(int damage, vec3 position, vec3 direction, float speed) {
	this->damage = damage;
	this->position = position;
	this->direction = direction;
	this->speed = speed;
	active = true;
}


void Bullet::Reset() {
	this->damage = 0;
	this->speed = 0.0f;
	this->direction = vec3(0.0f);
	this->camp = OTHER;
	recycleTimer = 0.0f;
	active = false;
}


void Bullet::SetCamp(Camp camp) {
	this->camp = camp;
}


Camp Bullet::GetCamp() {
	return this->camp;
}


void Bullet::SetRecycleTime(float recycleTime) {
	this->recycleTime = recycleTime;
}


int Bullet::GetAttackValue() {
	return damage;
}


bool Bullet::IsActive() {
	return this->active;
}