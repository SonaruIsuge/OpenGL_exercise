#include "Character.h"

Character::Character(Shape* shape, Camera* camera) : Object(shape, camera) {
	camp = OTHER;
	
	health = 0;
	attack = 0;
	remainHealth = 0;
	beHit = false;

	AddComponent<Collider>(this, this->position, shape->boundRadius);
	collider = GetComponent<Collider>();
}


Character::~Character() {
	
}


void Character::SetInitialData(int health, int attack) {
	this->health = health;
	this->remainHealth = health;
	this->attack = attack;
}


void Character::Update(float deltaTime) {
	Object::Update(deltaTime);
}


void Character::GetDamage(int damage) {
	remainHealth = clamp(remainHealth - damage, 0, health);

	if (remainHealth == 0) {
		// Dead
	}
}


int Character::GetAttackValue() {
	return attack;
}


int Character::GetHealth() {
	return remainHealth;
}

