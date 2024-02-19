#include "Character.h"

Character::Character(Shape* shape, Camera* camera) : Object(shape, camera) {
	camp = OTHER;
	
	health = 0;
	attack = 0;
	remainHealth = 0;
	beHit = false;
	dead = false;

	AddComponent<Collider>(this, this->position, shape->boundRadius);
	collider = GetComponent<Collider>();
}


Character::~Character() {
	
}


void Character::SetInitialData(int health, int attack) {
	this->health = health;
	this->remainHealth = health;
	this->attack = attack;
	dead = false;
}


void Character::Update(float deltaTime) {
	if (dead) return;
	Object::Update(deltaTime);
}


void Character::BeDamaged(int damage) {
	remainHealth = clamp(remainHealth - damage, 0, health);
	
	if (remainHealth == 0) {
		// Dead
		dead = true;
	}
}


int Character::GetAttackValue() {
	return attack;
}


int Character::GetHealth() {
	return remainHealth;
}


bool Character::IsDead() {
	return dead;
}

