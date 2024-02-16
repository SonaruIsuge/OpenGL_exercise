#include "Bullet.h"


Bullet::Bullet(Shape* shape, Camera* camera) : Object(shape, camera) {
	damage = 0;
	direction = vec3(0.0f);
	camp = OTHER;

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
}


void Bullet::Fire(int damage, vec3 position, vec3 direction, float speed) {
	this->damage = damage;
	this->position = position;
	this->direction = direction;
	this->speed = speed;
	active = true;
}


void Bullet::Reset() {
	active = false;
	this->damage = 0;
	this->direction = vec3(0.0f);
	this->camp = OTHER;
}


void Bullet::SetCamp(Camp camp) {
	this->camp = camp;
}


Camp Bullet::GetCamp() {
	return this->camp;
}