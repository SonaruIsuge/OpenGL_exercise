#include "Bullet.h"


Bullet::Bullet(Shape* shape, Camera* camera) : Object(shape, camera) {
	scale = vec3(0.5f);
	damage = 0;
	speed = 0.0f;
	direction = vec3(0.0f);
	camp = OTHER;
	recycleTimer = 0.0f;
	active = false;

	AddComponent<Collider>(this, this->position, 1.0f);
	collider = GetComponent<Collider>();
}


Bullet::~Bullet() {

}


void Bullet::Update(float deltaTime) {
	if (!active) return;

	position += direction * speed * deltaTime;
	Object::Update(deltaTime);

	recycleTimer += deltaTime;
	if (recycleTimer >= RECYCLE_TIME)
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


bool Bullet::IsActive() {
	return this->active;
}