#include "Collider.h"


Collider::Collider(Object* owner, vec3 center, float radius) : owner(owner), center(center), radius(radius) {
	isActive = true;
}


Collider::~Collider() {

}


void Collider::SetRadius(float radius) {
	this->radius = radius;
}


void Collider::Update(float deltaTime) {
	this->center = owner->position;
}


bool Collider::IsCollide(const Collider* other) {
	if (!isActive) return false;

	vec3 diff = other->center - this->center;
	float distance = length(diff);

	return distance <= this->radius + other->radius;
}